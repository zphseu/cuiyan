using System.Windows.Automation;

namespace Core.AutomationElementSearch.Properties
{
    public class ProcessIdProperty : AutomationElementProperty
    {
        public virtual bool HasValue(AutomationElement.AutomationElementInformation information, object value)
        {
            return information.ProcessId.ToString().Equals(value.ToString());
        }
    }
}