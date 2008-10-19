using System.Windows.Automation;

namespace Core.AutomationElementSearch.Properties
{
    public interface AutomationElementProperty
    {
        bool HasValue(AutomationElement.AutomationElementInformation information, object value);
    }
}