using System.Collections.Generic;
using System.Windows.Automation;
using Bricks.RuntimeFramework;
using Core.Factory;
using Core.UIItems.Actions;

namespace Core.UIItems.TableItems
{
    public class TableColumns : UIItemList<TableColumn>
    {
        public TableColumns(IEnumerable<AutomationElement> automationElements, ActionListener actionListener)
        {
            int i = 0;
            foreach (AutomationElement automationElement in automationElements)
            {
                if (HeaderColumn(automationElement)) continue;
                Add(new TableColumn(automationElement, actionListener, i++));
            }
        }

        private static bool HeaderColumn(AutomationElement automationElement)
        {
            return automationElement.GetCurrentPropertyValue(AutomationElement.NameProperty).Equals("Top Left Header Cell");
        }

        public virtual TableColumn this[string text]
        {
            get
            {
                TableColumn column = Find(delegate(TableColumn obj) { return obj.Name.Equals(text); });
                if (column == null)
                {
                    throw new UIItemSearchException(
                        string.Format("Cannot find column with text {0}. Found columns: {1}", text,
                                      string.Join(",", StringCollection.FromToString(this).ToArray())));
                }
                return column;
            }
        }
    }
}