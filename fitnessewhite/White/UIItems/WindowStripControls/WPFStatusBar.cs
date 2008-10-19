using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.UIItems.Finders;

namespace Core.UIItems.WindowStripControls
{
    public class WPFStatusBar : UIItem
    {
        protected WPFStatusBar() {}
        public WPFStatusBar(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual UIItemCollection Items
        {
            get { return factory.CreateAll(SearchCriteria.ByControlType(ControlType.Text), actionListener); }
        }
    }
}