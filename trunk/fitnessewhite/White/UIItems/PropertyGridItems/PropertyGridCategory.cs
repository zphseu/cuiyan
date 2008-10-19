using System.Collections.Generic;
using System.Windows.Automation;
using Core.UIA;
using Core.UIItems.Actions;

namespace Core.UIItems.PropertyGridItems
{
    public class PropertyGridCategory : UIItem
    {
        private readonly PropertyGridElementFinder gridElementFinder;
        protected PropertyGridCategory() {}
        internal PropertyGridCategory(AutomationElement automationElement, ActionListener actionListener, PropertyGridElementFinder gridElementFinder) : 
            base(automationElement, actionListener)
        {
            this.gridElementFinder = gridElementFinder;
        }

        public virtual List<PropertyGridProperty> Properties
        {
            get
            {
                bool thisElementFound = false;
                List<PropertyGridProperty> properties = new List<PropertyGridProperty>();
                AutomationElementCollection rows = gridElementFinder.FindRows();
                foreach (AutomationElement rowElement in rows)
                {
                    bool thisElement = rowElement.Equals(automationElement);
                    if (thisElement)
                    {
                        thisElementFound = true;
                        continue;
                    }
                    if (!thisElementFound) continue;

                    AutomationPatterns automationPatterns = new AutomationPatterns(rowElement);
                    if (automationPatterns.HasPattern(ValuePattern.Pattern))
                    {
                        properties.Add(new PropertyGridProperty(rowElement, actionListener));
                    }
                    else
                    {
                        break;                        
                    }
                }
                return properties;
            }
        }
    }
}