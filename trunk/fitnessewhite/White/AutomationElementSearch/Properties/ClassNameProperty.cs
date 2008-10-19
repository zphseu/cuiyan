using System.Windows.Automation;

namespace Core.AutomationElementSearch.Properties
{
    public class ClassNameProperty : AutomationElementProperty
    {
        public virtual bool HasValue(AutomationElement.AutomationElementInformation information, object value)
        {
            return information.ClassName.Equals(value);
        }
    }
}