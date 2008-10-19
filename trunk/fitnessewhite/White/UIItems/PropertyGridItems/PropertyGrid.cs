using System.Collections.Generic;
using System.Windows.Automation;
using Core.UIA;
using Core.UIItems.Actions;

namespace Core.UIItems.PropertyGridItems
{
    public class PropertyGrid : UIItem
    {
        private readonly PropertyGridElementFinder finder;
        protected PropertyGrid() {}

        public PropertyGrid(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            finder = new PropertyGridElementFinder(automationElement);
        }

        public virtual List<PropertyGridCategory> Categories
        {
            get
            {
                List<PropertyGridCategory> categories = new List<PropertyGridCategory>();
                AutomationElementCollection rows = finder.FindRows();
                foreach (AutomationElement element in rows)
                {
                    AutomationPatterns automationPatterns = new AutomationPatterns(element);
                    if (!automationPatterns.HasPattern(ValuePattern.Pattern))
                        categories.Add(new PropertyGridCategory(element, actionListener, finder));
                }

                return categories;
            }
        }
    }
}