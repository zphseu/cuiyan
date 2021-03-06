using System.Windows.Automation;
using Core.UIItems.Finders;

namespace Core.AutomationElementSearch
{
    /// <summary>
    /// Internal to white and should not be used unless a known issue. One should be able to find all items 
    /// </summary>
    public class AutomationElementFinder
    {
        private readonly AutomationElement automationElement;

        public AutomationElementFinder(AutomationElement automationElement)
        {
            this.automationElement = automationElement;
        }

        public virtual AutomationElement AutomationElement
        {
            get { return automationElement; }
        }

        public virtual AutomationElementCollection Children(params AutomationSearchCondition[] automationSearchConditions)
        {
            return new MultiLevelAutomationElementFinder(automationSearchConditions).FindAll(automationElement);
        }

        public virtual AutomationElement Child(params AutomationSearchCondition[] automationSearchConditions)
        {
            return new MultiLevelAutomationElementFinder(automationSearchConditions).Find(automationElement);
        }

        public virtual AutomationElement Child(int returnLevel, AutomationSearchCondition[] automationSearchConditions)
        {
            return new MultiLevelAutomationElementFinder(automationSearchConditions).Find(returnLevel, automationElement);
        }

        public virtual AutomationElementCollection Children(AutomationSearchCondition automationSearchCondition)
        {
            return automationElement.FindAll(TreeScope.Children, automationSearchCondition.Condition);
        }

        public virtual AutomationElement Child(AutomationSearchCondition automationSearchCondition)
        {
            return automationElement.FindFirst(TreeScope.Children, automationSearchCondition.Condition);
        }

        public virtual AutomationElement Descendant(AutomationSearchCondition searchCondition)
        {
            return Descendant(searchCondition.Condition);
        }

        public virtual AutomationElement Descendant(Condition condition)
        {
            return automationElement.FindFirst(TreeScope.Descendants, condition);
        }

        //Should take AutomationSearchCondition
        public virtual AutomationElementCollection Descendants(Condition condition)
        {
            return automationElement.FindAll(TreeScope.Descendants, condition);
        }

        public virtual AutomationElementCollection Descendants(AutomationSearchCondition automationSearchCondition)
        {
            return automationElement.FindAll(TreeScope.Descendants, automationSearchCondition.Condition);
        }

        public virtual AutomationElement FindWindow(string title, int processId)
        {
            AutomationSearchCondition windowSearchCondition = GetWindowSearchCondition(processId);
            AutomationElement windowElement = Child(windowSearchCondition.OfName(title));
            if (windowElement != null) return windowElement;
            try
            {
                windowElement =
                    Child(0,
                          new AutomationSearchCondition[]
                              {GetWindowSearchCondition(processId), AutomationSearchCondition.ByControlType(ControlType.TitleBar).OfName(title)});
            }
            catch (AutomationElementSearchException)
            {
                return null;
            }
            return windowElement;
        }

        public virtual AutomationElement FindChildRaw(AutomationSearchCondition automationSearchCondition)
        {
            return new RawAutomationElementFinder(automationElement).Child(automationSearchCondition);
        }

        /// <summary>
        /// Uses the Raw View provided by UIAutomation to find elements. RawView sometimes contains extra AutomationElements. This is internal to 
        /// white although made public. Should be used only if the standard approaches dont work. Also if you end up using it please raise an issue
        /// so that it can be fixed
        /// Please understand that calling this method on any UIItem which has a lot of child AutomationElements might result in very bad performance.
        /// </summary>
        /// <param name="automationSearchCondition"></param>
        /// <returns>null or found AutomationElement</returns>
        public virtual AutomationElement FindDescendantRaw(AutomationSearchCondition automationSearchCondition)
        {
            return new RawAutomationElementFinder(automationElement).Descendant(automationSearchCondition);
        }

        public virtual AutomationElement FindWindow(SearchCriteria searchCriteria, int processId)
        {
            Condition condition = searchCriteria.AutomationConditionWith(new PropertyCondition(AutomationElement.ProcessIdProperty, processId));
            return automationElement.FindFirst(TreeScope.Children, condition);
        }

        private AutomationSearchCondition GetWindowSearchCondition(int processId)
        {
            AutomationSearchCondition windowSearchCondition = AutomationSearchCondition.ByControlType(ControlType.Window);
            if (processId > 0)
                windowSearchCondition.WithProcessId(processId);
            return windowSearchCondition;
        }
    }
}