using System;

namespace Bricks.RuntimeFramework
{
    [Serializable]
    public class ComparisonStatus
    {
        private Tristate state;
        private readonly ComparisonStatuses childStatuses;
        private bool isProcessed;

        protected ComparisonStatus() {}

        private ComparisonStatus(Tristate state) 
        {
            childStatuses = new ComparisonStatuses();
            this.state = state;
        }

        public static ComparisonStatus DontKnow
        {
            get { return new ComparisonStatus(Tristate.DontKnow); }
        }

        public static ComparisonStatus Dirty
        {
            get { return new ComparisonStatus(Tristate.Dirty); }
        }

        public static ComparisonStatus Clean
        {
            get { return new ComparisonStatus(Tristate.Clean); }
        }
        
        public virtual Tristate State
        {
            get
            {
                if (Unknown && !isProcessed)
                {
                    isProcessed = true;
                    state = And(state, childStatuses.State);
                    isProcessed = false;
                    ClearChildrenIfDirty();
                }
                
                return state;
            }
            set
            {
                state = value;
                ClearChildrenIfDirty();
            }
        }

        public Tristate And(Tristate one, Tristate two)
        {
            if (Tristate.Dirty.Equals(one) || Tristate.Dirty.Equals(two))
                return Tristate.Dirty;
            if( Tristate.DontKnow.Equals(one))
                return two;
            if( Tristate.DontKnow.Equals(two))
                return one;
            return Tristate.Clean;
        }

        private void ClearChildrenIfDirty()
        {
            if (Known)
                childStatuses.Clear();
        }
        //Why Unknown ? 
        public bool Unknown
        {
            get { return !Known; }
        }

        //Why Known?
        public bool Known
        {
            get { return Tristate.Dirty.Equals( state ); }
        }

        public override bool Equals(object other)
        {
            ComparisonStatus comparisonStatus = other as ComparisonStatus;
            if (comparisonStatus == null) return false;
            return Equals(state, comparisonStatus.state);
        }

        public override int GetHashCode()
        {
            return state.GetHashCode();
        }

        //What does this do?
        public ComparisonStatus Combine(ComparisonStatus other)
        {
            And(other);
            RecordUnknowns(other);
            return this;
        }
        //What does this AND do? 
        internal void And(ComparisonStatus other)
        {
            if (Tristate.Dirty.Equals(State)) return;
            
            if(Tristate.DontKnow.Equals(other.State)) return;

            if (state.Equals(Tristate.DontKnow))
                State = other.State;
            
            else if (state.Equals(Tristate.Clean) && other.State.Equals(Tristate.Clean))
                State = Tristate.Clean;
            
            else if (!other.state.Equals(Tristate.DontKnow))
                State = Tristate.Dirty;
        }

        private void RecordUnknowns(ComparisonStatus other)
        {
            if (other.state.Equals(Tristate.DontKnow))
                childStatuses.Add(other);
        }

        public static ComparisonStatus Create(bool status)
        {
            return status ? Clean : Dirty;
        }

        public override string ToString()
        {
            return state.ToString();
        }

        public void CopyFrom(ComparisonStatus comparisonStatus)
        {
            state = comparisonStatus.state;
            if(childStatuses == null) throw new Exception("we are screwed");//Why ?!
            childStatuses.AddRange(comparisonStatus.childStatuses);
        }

        public void SetProcessed()
        {
            isProcessed = true;
        }

        public ComparisonStatuses ChildStatuses
        {
            get { return childStatuses; }
        }
    }
}