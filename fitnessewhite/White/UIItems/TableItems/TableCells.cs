using System.Collections;
using System.Windows.Automation;
using Bricks.Core;
using Core.UIItems.Actions;

namespace Core.UIItems.TableItems
{
    public class TableCells : UIItemList<TableCell>
    {
        private readonly TableHeader tableHeader;

        public TableCells(ICollection tableCellElements, TableHeader tableHeader, ActionListener actionListener)
        {
            this.tableHeader = tableHeader;
            foreach (AutomationElement tableCellElement in tableCellElements)
                Add(new TableCell(tableCellElement, actionListener));
        }

        public virtual TableCell this[string column]
        {
            get
            {
                if (tableHeader == null && S.IsEmpty(column)) return this[0];
                if (tableHeader == null) throw new UIActionException("Cannot get cell for " + column);
                return this[tableHeader.Columns[column].Index];
            }
        }
    }
}