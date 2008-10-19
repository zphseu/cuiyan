using System.Collections.Generic;
using System.Windows.Automation;
using Bricks.RuntimeFramework;
using Core.AutomationElementSearch;
using Core.UIItems.Actions;

namespace Core.UIItems.TableItems
{
    public class TableHeader : UIItem
    {
        protected TableHeader() {}

        public TableHeader(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual TableColumns Columns
        {
            get
            {
                AutomationElementCollection descendants =
                    new AutomationElementFinder(automationElement).Descendants(AutomationSearchCondition.ByControlType(ControlType.Header));
                List<AutomationElement> columnElements =
                    new BricksCollection<AutomationElement>(descendants).FindAll(
                        delegate(AutomationElement obj) { return !obj.Current.Name.StartsWith("Row "); });
                return new TableColumns(columnElements, actionListener);
            }
        }
    }
}