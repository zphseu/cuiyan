using System;
using System.Windows.Automation;
using Core.Mappings;
using Core.UIItems.Custom;

namespace Core.UIItems.Finders
{
    public class ControlTypeCondition : SearchCondition
    {
        private readonly ControlType controlType;

        protected ControlTypeCondition() {}

        public ControlTypeCondition(ControlType controlType)
        {
            this.controlType = controlType;
        }

        public ControlTypeCondition(Type testControlType)
        {
            controlType = typeof (CustomUIItem).IsAssignableFrom(testControlType) ? 
                                CustomControlTypeMapping.ControlType(testControlType) : ControlDictionary.Instance.GetControlType(testControlType);
        }

        public override Condition AutomationCondition
        {
            get { return new PropertyCondition(AutomationElement.ControlTypeProperty, controlType); }
        }

        public override bool Satisfies(AutomationElement element)
        {
            return element.Current.ControlType.Equals(controlType);
        }

        internal override string ToString(string operation)
        {
            return "ControlType" + operation + controlType.ProgrammaticName;
        }

        protected internal override object SearchValue
        {
            get { return controlType; }
        }

        public virtual ControlType ControlType
        {
            get { return controlType; }
        }

        public override bool AppliesTo(AutomationElement element)
        {
            return controlType.Equals(element.Current.ControlType);
        }

        public override string ToString()
        {
            return ToString("=");
        }
    }
}