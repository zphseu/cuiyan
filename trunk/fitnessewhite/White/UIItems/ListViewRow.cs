using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.UIItems.Actions;
using Core.UIItems.ListViewItems;
using Core.WindowsAPI;

namespace Core.UIItems
{
    public class ListViewRow : UIItem
    {
        private readonly ListViewHeader header;
        private readonly AutomationElementFinder finder;
        protected ListViewRow() {}

        public ListViewRow(AutomationElement automationElement, ActionListener actionListener, ListViewHeader header)
            : base(automationElement, actionListener)
        {
            this.header = header;
            finder = new AutomationElementFinder(automationElement);
        }

        public virtual bool IsSelected
        {
            get
            {
                actionListener.ActionPerforming(this);
                return (bool) Property(SelectionItemPattern.IsSelectedProperty);
            }
        }

        public virtual ListViewCells Cells
        {
            get
            {
                actionListener.ActionPerforming(this);
                AutomationElementCollection collection = null;
                try {
                	collection = finder.Children(AutomationSearchCondition.ByControlType(ControlType.Text));
                }catch {
	                collection = finder.Children(AutomationSearchCondition.ByControlType(ControlType.Edit));
                }
                
                return new ListViewCells(collection, actionListener, header);
            }
        }

        /// <summary>
        /// Unselects previously selected row and selects this row. If this row is already selected it doesn't have any effect.
        /// </summary>
        public virtual void Select()
        {
            actionListener.ActionPerforming(this);
            mouse.Click(ClickablePoint, actionListener);
        }

        /// <summary>
        /// Keeps the old row selected and selects this row. If this row is already selected it doesn't have any effect.
        /// </summary>
        public virtual void MultiSelect()
        {
            actionListener.ActionPerforming(this);

            keyboard.HoldKey(KeyboardInput.SpecialKeys.CONTROL, actionListener);
            Select();
            keyboard.LeaveKey(KeyboardInput.SpecialKeys.CONTROL, actionListener);
        }
    }
}