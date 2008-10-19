using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.UIItems.Actions;

namespace Core.UIItems.ListViewItems
{
    public class ListViewHeader : UIItem
    {
        private readonly AutomationElementFinder automationElementFinder;

        protected ListViewHeader() {}

        public ListViewHeader(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            automationElementFinder = new AutomationElementFinder(automationElement);
        }

        public virtual ListViewColumns Columns
        {
            get
            {
                AutomationElementCollection collection = automationElementFinder.Children(AutomationSearchCondition.ByControlType(ControlType.HeaderItem));
                return new ListViewColumns(collection, actionListener);
            }
        }
    }
}