using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems
{
    public class ListViewCell : Label
    {
        protected ListViewCell() {}
        public ListViewCell(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}
    }
}