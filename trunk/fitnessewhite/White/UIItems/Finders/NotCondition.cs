using System;
using System.Windows.Automation;

namespace Core.UIItems.Finders
{
    public class NotCondition : SearchCondition
    {
        private readonly SearchCondition condition;

        protected NotCondition() {}

        public NotCondition(SearchCondition condition)
        {
            this.condition = condition;
        }

        public override Condition AutomationCondition
        {
            get { return new System.Windows.Automation.NotCondition(condition.AutomationCondition); }
        }

        public override bool Satisfies(AutomationElement element)
        {
            return !condition.Satisfies(element);
        }

        public override string ToString()
        {
            return condition.ToString("!=");
        }

        internal override string ToString(string operation)
        {
            throw new NotImplementedException();
        }

        protected internal override object SearchValue
        {
            get { return condition.SearchValue; }
        }

        public override bool AppliesTo(AutomationElement element)
        {
            return !condition.AppliesTo(element);
        }
    }
}