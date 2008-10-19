using System.Windows.Automation;
using Core.AutomationElementSearch;

namespace Core.UIItems.PropertyGridItems
{
    public class PropertyGridElementFinder
    {
        private readonly AutomationElementFinder finder;

        public PropertyGridElementFinder(AutomationElement automationElement)
        {
            finder = new AutomationElementFinder(automationElement);
        }

        public virtual AutomationElementCollection FindRows()
        {
            return finder.Children(AutomationSearchCondition.ByControlType(ControlType.Table),
                                                                            AutomationSearchCondition.ByControlType(ControlType.Custom));
        }
    }
}