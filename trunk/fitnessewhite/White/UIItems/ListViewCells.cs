using System.Windows.Automation;
using Bricks.Core;
using Core.Factory;
using Core.UIItems.Actions;
using Core.UIItems.ListViewItems;

namespace Core.UIItems
{
    public class ListViewCells : UIItemList<ListViewCell>
    {
        private readonly ListViewHeader header;

        public ListViewCells(AutomationElementCollection collection, ActionListener actionListener, ListViewHeader header)
            : base(collection, new ListViewCellFactory(), actionListener)
        {
            this.header = header;
        }

        public virtual ListViewCell this[string columnName]
        {
            get
            {
                if (header == null && S.IsEmpty(columnName)) return this[0];
                if (header == null) throw new UIActionException("Cannot get cell for " + columnName);
                return this[header.Columns[columnName].Index];
            }
        }
    }
}