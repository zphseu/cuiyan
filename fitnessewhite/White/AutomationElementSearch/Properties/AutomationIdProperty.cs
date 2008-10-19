using System.Windows.Automation;

namespace Core.AutomationElementSearch.Properties
{
    public class AutomationIdProperty : AutomationElementProperty
    {
        public virtual bool HasValue(AutomationElement.AutomationElementInformation information, object value)
        {
            return information.AutomationId.Equals(value);
        }
    }
}