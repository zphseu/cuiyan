using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.TableItems
{
    public class TableRowHeader : UIItem
    {
        protected TableRowHeader() {}
        public TableRowHeader(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}
    }
}