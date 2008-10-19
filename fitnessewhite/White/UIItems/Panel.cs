using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.UIItems.Custom;

namespace Core.UIItems
{
    [ControlTypeMapping(CustomUIItemType.Pane)]
    public class Panel : CustomUIItem
    {
        protected Panel() {}
        public Panel(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual string Text
        {
            get { return Name; }
        }
    }
}