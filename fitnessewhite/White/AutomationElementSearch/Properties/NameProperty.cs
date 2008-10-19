using System.Windows.Automation;
using Core.AutomationElementSearch.Properties;

namespace Core.AutomationElementSearch.Properties
{
    public class NameProperty : AutomationElementProperty
    {
        public virtual bool HasValue(AutomationElement.AutomationElementInformation information, object value)
        {
            return information.Name.Equals(value);
        }
    }
}