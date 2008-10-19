using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.TableItems
{
    public class TableColumn : UIItem
    {
        private readonly int index;
        protected TableColumn() {}

        public TableColumn(AutomationElement automationElement, ActionListener actionListener, int index) : base(automationElement, actionListener)
        {
            this.index = index;
        }

        public virtual int Index
        {
            get { return index; }
        }
    }
}