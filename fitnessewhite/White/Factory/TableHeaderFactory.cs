using System.Windows.Automation;
using Core.UIItems;
using Core.UIItems.Actions;
using Core.UIItems.TableItems;

namespace Core.Factory
{
    public class TableHeaderFactory : UIItemFactory
    {
        public virtual IUIItem Create(AutomationElement automationElement, ActionListener actionListener)
        {
            return new TableHeader(automationElement, actionListener);
        }
    }
}