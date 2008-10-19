using System.Windows.Automation;
using Core.UIItems;
using Core.UIItems.Actions;

namespace Core.Factory
{
    public class ListViewCellFactory : UIItemFactory
    {
        public virtual IUIItem Create(AutomationElement automationElement, ActionListener actionListener)
        {
            return new ListViewCell(automationElement, actionListener);
        }
    }
}