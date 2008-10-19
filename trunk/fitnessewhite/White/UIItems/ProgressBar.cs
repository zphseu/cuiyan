using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems
{
    public class ProgressBar : UIItem
    {
        protected ProgressBar() {}
        public ProgressBar(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        internal virtual double Minimum
        {
            get { return (double) Property(RangeValuePattern.MinimumProperty); }
        }

        internal virtual double Maximum
        {
            get { return (double) Property(RangeValuePattern.MaximumProperty); }
        }

        public virtual double Value
        {
            get { return (double) Property(RangeValuePattern.ValueProperty); }
        }
    }
}