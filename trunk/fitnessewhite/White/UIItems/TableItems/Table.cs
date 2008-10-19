using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.Factory;
using Core.UIItems.Actions;
using Core.UIItems.Finders;
using Core.UIItems.Scrolling;

namespace Core.UIItems.TableItems
{
    public class Table : UIItem
    {
        private TableRows rows;
        private TableHeader header;
        private readonly AutomationElementFinder finder;
        private readonly TableRowFactory tableRowFactory;
        protected Table() {}

        public Table(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            finder = new AutomationElementFinder(automationElement);
            tableRowFactory = new TableRowFactory(finder);
        }

        public virtual TableRows Rows
        {
            get
            {
                if (rows == null)
                    rows = tableRowFactory.CreateRows(this, Header);
                return rows;
            }
        }

        public virtual TableHeader Header
        {
            get
            {
                if (header == null)
                    header = (TableHeader) new TableHeaderFactory().Create(finder.Descendant(SearchCriteria.ByText("Top Row").AutomationCondition), actionListener);
                return header;
            }
        }

        public virtual TableRow Row(string column, string value)
        {
            return Rows.Get(column, value);
        }

        public virtual TableRows FindAll(string column, string value)
        {
            return Rows.GetMultipleRows(column, value);
        }

        public virtual void Refresh()
        {
            rows = null;
        }

        public override void ActionPerforming(UIItem uiItem)
        {
            if (uiItem is Table) return;
            new ScreenItem(uiItem, ScrollBars).MakeVisible(new VerticalSpan(Bounds));
        }

        public override IScrollBars ScrollBars
        {
            get
            {
                if (scrollBars == null) scrollBars = new TableScrollBars(finder, actionListener);
                return scrollBars;
            }
        }

        public override void RightClick()
        {
            new TooltipSafeMouse(mouse).RightClickOutsideToolTip(this, actionListener);
        }
    }
}