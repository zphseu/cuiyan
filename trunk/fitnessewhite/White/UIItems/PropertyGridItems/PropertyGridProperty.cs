using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.PropertyGridItems
{
    public class PropertyGridProperty : UIItem
    {
        protected PropertyGridProperty() {}
        public PropertyGridProperty(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual string Value
        {
            get { return ValuePatternId().Value; }
            set { ValuePattern().SetValue(value); }
        }

        private ValuePattern.ValuePatternInformation ValuePatternId()
        {
            return ValuePattern().Current;
        }

        private ValuePattern ValuePattern()
        {
            return ((ValuePattern) Pattern(System.Windows.Automation.ValuePattern.Pattern));
        }

        public virtual bool IsReadOnly
        {
            get { return ValuePatternId().IsReadOnly; }
        }
    }
}