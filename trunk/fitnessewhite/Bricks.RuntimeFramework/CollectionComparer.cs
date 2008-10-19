using System.Collections;

namespace Bricks.RuntimeFramework
{
    public class CollectionComparer : ObjectComparer
    {
        private ICollection originalCollection;
        private ICollection otherCollection;

        public CollectionComparer(object original, object other) : base(original,other){}
        public CollectionComparer(object original, object other, LeafRegistry leafRegister)
            : base(original, other, leafRegister){}

        public override ComparisonStatus Compare()
        {
            if (!(ComparisonStatus.Clean.Equals(status))&& !(ComparisonStatus.Dirty.Equals(status)))
            {
                originalCollection = original.O as ICollection;
                otherCollection = other.O as ICollection;
                if (originalCollection.Count != otherCollection.Count)
                {
                    status = ComparisonStatus.Dirty;
                }
                else
                {
                    IEnumerator originalEnumerator = originalCollection.GetEnumerator();
                    IEnumerator otherEnumerator = otherCollection.GetEnumerator();
                    while(originalEnumerator.MoveNext()&&otherEnumerator.MoveNext())
                    {
                        object currentOriginalItem = originalEnumerator.Current;
                        object currentOtherItem = otherEnumerator.Current;
                        status.And(new ObjectComparer(currentOriginalItem, currentOtherItem, leafRegister).Compare());
                    }
                }
            }
            else status = ComparisonStatus.Dirty;

            return status;
        }
    }
}