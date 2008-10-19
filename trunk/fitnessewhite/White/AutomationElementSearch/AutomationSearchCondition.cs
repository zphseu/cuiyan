using System.Collections.Generic;
using System.Text;
using System.Windows.Automation;
using Core.AutomationElementSearch.Properties;

namespace Core.AutomationElementSearch
{
    public class AutomationSearchCondition
    {
        private readonly List<Condition> conditions = new List<Condition>();
        private static readonly Dictionary<string, AutomationElementProperty> properties = new Dictionary<string, AutomationElementProperty>();

        static AutomationSearchCondition()
        {
            properties[AutomationElement.NameProperty.ProgrammaticName] = new NameProperty();
            properties[AutomationElement.AutomationIdProperty.ProgrammaticName] = new AutomationIdProperty();
            properties[AutomationElement.ClassNameProperty.ProgrammaticName] = new ClassNameProperty();
            properties[AutomationElement.ProcessIdProperty.ProgrammaticName] = new ProcessIdProperty();
            properties[AutomationElement.ControlTypeProperty.ProgrammaticName] = new ControlTypeProperty();
        }

        public static AutomationSearchCondition ByName(string name)
        {
            AutomationSearchCondition automationSearchCondition = new AutomationSearchCondition();
            automationSearchCondition.OfName(name);
            return automationSearchCondition;
        }

        public virtual AutomationSearchCondition OfName(string name)
        {
            conditions.Add(new PropertyCondition(AutomationElement.NameProperty, name));
            return this;
        }

        public static AutomationSearchCondition ByAutomationId(string id)
        {
            AutomationSearchCondition automationSearchCondition = new AutomationSearchCondition();
            automationSearchCondition.WithAutomationId(id);
            return automationSearchCondition;
        }

        public virtual AutomationSearchCondition WithAutomationId(string id)
        {
            conditions.Add(new PropertyCondition(AutomationElement.AutomationIdProperty, id));
            return this;
        }

        public static AutomationSearchCondition ByControlType(ControlType controlType)
        {
            AutomationSearchCondition automationSearchCondition = new AutomationSearchCondition();
            automationSearchCondition.OfControlType(controlType);
            return automationSearchCondition;
        }

        public static AutomationSearchCondition ByAnyOfControlTypes(ControlType[] controlTypes)
        {
            AutomationSearchCondition automationSearchCondition = new AutomationSearchCondition();
            List<PropertyCondition> propertyConditions = new List<PropertyCondition>();
            foreach (ControlType controlType in controlTypes)
                propertyConditions.Add(new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
            Condition controlTypeCondition = propertyConditions.Count == 1
                                                 ? (Condition) propertyConditions[0]
                                                 : new OrCondition(propertyConditions.ToArray());
            automationSearchCondition.conditions.Add(controlTypeCondition);
            return automationSearchCondition;
        }

        public static AutomationSearchCondition All
        {
            get
            {
                AutomationSearchCondition automationSearchCondition = new AutomationSearchCondition();
                automationSearchCondition.conditions.Add(Condition.TrueCondition);
                return automationSearchCondition;
            }
        }

        public virtual AutomationSearchCondition OfControlType(ControlType controlType)
        {
            conditions.Add(new PropertyCondition(AutomationElement.ControlTypeProperty, controlType));
            return this;
        }

        public virtual AutomationSearchCondition WithProcessId(int processId)
        {
            conditions.Add(new PropertyCondition(AutomationElement.ProcessIdProperty, processId));
            return this;
        }

        public virtual Condition Condition
        {
            get
            {
                if (conditions.Count == 1) return conditions[0];
                return new AndCondition(conditions.ToArray());
            }
        }

        public override string ToString()
        {
            StringBuilder stringBuilder = new StringBuilder();
            foreach (PropertyCondition condition in conditions)
                stringBuilder.Append(condition.Property.ProgrammaticName + ":" + condition.Value);
            return stringBuilder.ToString();
        }

        public static AutomationSearchCondition ByClassName(string className)
        {
            AutomationSearchCondition automationSearchCondition = new AutomationSearchCondition();
            automationSearchCondition.conditions.Add(new PropertyCondition(AutomationElement.ClassNameProperty, className));
            return automationSearchCondition;
        }

        public static string ToString(AutomationSearchCondition[] conditions)
        {
            StringBuilder builder = new StringBuilder();
            foreach (AutomationSearchCondition condition in conditions)
                builder.AppendLine(condition.ToString());
            return builder.ToString();
        }

        public virtual bool Satisfies(AutomationElement element)
        {
            foreach (PropertyCondition condition in conditions)
            {
                if (!properties[condition.Property.ProgrammaticName].HasValue(element.Current, condition.Value))
                {
                    return false;
                }
            }
            return true;
        }

        public virtual void Add(Condition condition)
        {
            conditions.Add(condition);
        }
    }
}