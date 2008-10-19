using System.Collections;
using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.Factory;
using Core.UIItems.Actions;
using Core.UIItems.ListViewItems;

namespace Core.UIItems
{
    public class ListViewRows : UIItemList<ListViewRow>
    {
        private ListViewRows(ICollection tees) : base(tees) {}

        public ListViewRows(AutomationElementFinder finder, ActionListener actionListener, ListViewHeader header)
        {
            AutomationElementCollection collection = finder.Descendants(AutomationSearchCondition.ByControlType(ControlType.DataItem));
            foreach (AutomationElement element in collection)
                Add(new ListViewRow(element, actionListener, header));
        }

        public virtual ListViewRow Get(int zeroBasedIndex)
        {
            if (Count <= zeroBasedIndex) throw new UIItemSearchException("No row found with index " + zeroBasedIndex);
            return this[zeroBasedIndex];
        }

        public virtual ListViewRow Get(string column, string value)
        {
            return Find(delegate(ListViewRow obj) { return obj.Cells[column].Text.Equals(value); });
        }

        public virtual ListViewRows SelectedRows
        {
            get { return new ListViewRows(FindAll(delegate(ListViewRow obj) { return obj.IsSelected; })); }
        }
    }
}