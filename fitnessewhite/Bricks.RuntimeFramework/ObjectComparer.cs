namespace Bricks.RuntimeFramework
{
    public class ObjectComparer
    {
        protected readonly LeafRegistry leafRegister;
        protected ComparisonStatus status;
        protected readonly ReflectedObject original;
        protected readonly ReflectedObject other;

        public ObjectComparer(object original, object other): this(original, other, new LeafRegistry()){}

        public ObjectComparer(object original, object other, LeafRegistry leafRegister)
        {
            this.original = new ReflectedObject(original);
            this.other = new ReflectedObject(other);
            this.leafRegister = leafRegister;
            status = ComparisonStatus.DontKnow;
            try
            {
                CompareBasics(this.original,this.other);
            }
            catch (NullComparisonException)
            {
                status = ComparisonStatus.Clean;
            }
            catch (BasicComparisonException)
            {
                status = ComparisonStatus.Dirty;
            }
        }


        public static void CompareBasics(ReflectedObject @this,  ReflectedObject other)
        {
            if (@this.O == null && other.O == null)
                throw new NullComparisonException("Comparison objects are null");
            if (@this.O != null && other.O == null)
                throw new BasicComparisonException("One of the comparison objects is null");
            if (@this.O == null && other.O != null)
                throw new BasicComparisonException("One of the comparison objects is null");
            if (other.O.GetType() != @this.O.GetType())
                throw new BasicComparisonException("Cannot compare objects of two different types");
            if (other.Fields.Count != @this.Fields.Count)
                throw new BasicComparisonException("Two objects have dissimilar number of fields.");
        }

        public virtual ComparisonStatus Compare()
        {
            if((!ComparisonStatus.Dirty.Equals(status))&&(!ComparisonStatus.Clean.Equals(status)))
            {
                if (!Field.IsPrimitive(original.O.GetType()))
                {
                    if (original.Fields.Count != 0)
                    {
                        foreach (Field field in original.Fields)
                        {
                            if (other.HasField(field.Name))
                            {
                                if(!leafRegister.Contains(field.Type))
                                {
                                    leafRegister.AddLeaf(field.Type);
                                    Field otherField = other.Fields[field.Name];
                                    status.And(field.Compare(otherField, leafRegister));    
                                }else
                                {
                                    status = ComparisonStatus.Clean;
                                }
                            }else
                            {
                                status = ComparisonStatus.Dirty;
                            }
                            leafRegister.RemoveLeaf(field.Type);
                        }
                    }else
                    {
                        status = ComparisonStatus.Clean;
                    }
                }else
                {
                    status = original.O.Equals(other.O) ? ComparisonStatus.Clean : ComparisonStatus.Dirty;    
                }
            }
            return status;
        }
    }
}