using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems
{
    public class GroupBox : UIItem
    {
        protected GroupBox() {}
        public GroupBox(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}
    }
}