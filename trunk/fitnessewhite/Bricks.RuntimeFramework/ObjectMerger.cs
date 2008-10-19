namespace Bricks.RuntimeFramework
{
    public class ObjectMerger
    {
        private readonly LeafRegistry leafRegister;
        private readonly ReflectedObject original;
        private readonly ReflectedObject other;

        private ReflectedObject mergedObject;

        public ObjectMerger(object original, object other) : this(original,other,new LeafRegistry()){}

        public ObjectMerger(object original, object other, LeafRegistry leafRegister)
        {
            this.original = new ReflectedObject(original);
            this.other = new ReflectedObject(other);
            this.leafRegister = leafRegister;
        }

        public virtual object Merge(object myObject, ConflictResolver conflictResolver)
        {
            if (myObject != null && original.O != null && other.O != null)
            {
                if (Equals(myObject.GetType(), original.O.GetType()) && Equals(myObject.GetType(), other.O.GetType()))
                {
                    leafRegister.AddLeaf(original.O.GetType());
                    return DoMerge(myObject, conflictResolver);
                }
                throw new TypeMismatchException("Unable to merge");
            }

            if (myObject == null)
            {
                if (original.O != null && other.O != null)
                {
                    if (Equals(original.O.GetType(), other.O.GetType()))
                    {
                        leafRegister.AddLeaf(original.O.GetType());
                        return DoMerge(myObject, conflictResolver);
                    }
                    throw new TypeMismatchException("Unable to merge");
                }
                if (original.O == null && other.O != null){ return other.O; }
                if (other.O == null && original.O != null){ return null; }
                return null;
            }            
            if (original.O == null)
            {
                if (other.O != null)
                {
                    if (Equals(myObject.GetType(), other.O.GetType()))
                    {
                        leafRegister.AddLeaf(myObject.GetType());
                        return DoMerge(myObject, conflictResolver);
                    }
                    throw new TypeMismatchException("Unable to merge");
                }
                return myObject;
            }
            if (other.O == null)
            {
                if (original.O != null)
                {
                    if(Equals(myObject.GetType(),original.O.GetType()))
                    {
                        leafRegister.AddLeaf(myObject.GetType());
                        return DoMerge(myObject, conflictResolver);
                    }
                    throw new TypeMismatchException("Unable to merge");
                }
                return myObject;
            }
            return null;
        }

        private object DoMerge(object myObject, ConflictResolver conflictResolver) {
            ReflectedObject mine = new ReflectedObject(myObject);
            mergedObject = new ReflectedObject(mine.Class.New());
            mine.Fields.ForEach(myField => mergedObject.SetValue(myField.Name, MergeField(myField, conflictResolver, mine)));
            if(mergedObject.O!=null){ leafRegister.RemoveLeaf(mergedObject.O.GetType()); }
            return mergedObject.O;
        }

        private object MergeField(Field myField, ConflictResolver conflictResolver, ReflectedObject mine)
        {
            Field originalField = original.Fields[myField.Name];
            Field otherField = other.Fields[myField.Name];

            object mergeValue;
            if (myField.IsPrimitive())
            {
                if (Equals(otherField.Value, myField.Value))
                    mergeValue = myField.Value;
                else if (!Equals(originalField.Value, otherField.Value) && !Equals(originalField.Value, myField.Value))
                    mergeValue = conflictResolver.Resolve(original, originalField, other, otherField, mine, myField);
                else
                    mergeValue = Equals(originalField.Value, otherField.Value) ? myField.Value : otherField.Value;
            }
            else
            {
                if(!leafRegister.Contains(myField.Type))
                {
                    ObjectMerger merger = new ObjectMerger(originalField.Value, otherField.Value,leafRegister);
                    mergeValue = merger.Merge(myField.Value, conflictResolver);
                }
                else
                {
                    //Circular Reference detected.
                    mergeValue = null;
                }
            }
            return mergeValue;
        }
    }
}