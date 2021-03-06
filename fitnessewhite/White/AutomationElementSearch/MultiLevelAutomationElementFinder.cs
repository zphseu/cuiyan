using System.Windows.Automation;

namespace Core.AutomationElementSearch
{
    public class MultiLevelAutomationElementFinder
    {
        private readonly AutomationSearchCondition[] searchConditions;

        public MultiLevelAutomationElementFinder(params AutomationSearchCondition[] searchConditions)
        {
            this.searchConditions = searchConditions;
        }

        public virtual AutomationElement Find(int returnLevel, AutomationElement startElement)
        {
            AutomationElement currentElement = startElement;
            AutomationElement automationElementAtReturnLevel = null;
            for (int i = 0; i < searchConditions.Length; i++)
            {
                AutomationElementFinder currentFinder = new AutomationElementFinder(currentElement);
                AutomationElement childElement = currentFinder.Child(searchConditions[i]);
                if (childElement == null)
                    throw AutomationElementSearchException.ElementNotFound(searchConditions[i], i);
                currentElement = childElement;
                if (i == returnLevel) automationElementAtReturnLevel = childElement;
            }
            return automationElementAtReturnLevel;
        }

        public virtual AutomationElement Find(AutomationElement startElement)
        {
            return Find(searchConditions.Length - 1, startElement);
        }

        public virtual AutomationElementCollection FindAll(int returnLevel, AutomationElement startElement)
        {
            AutomationElement currentElement = startElement;
            for (int i = 0; i < searchConditions.Length; i++)
            {
                AutomationElementFinder currentFinder = new AutomationElementFinder(currentElement);
                if (i == searchConditions.Length - 1) return currentFinder.Children(searchConditions[i]);

                AutomationElement childElement = currentFinder.Child(searchConditions[i]);
                currentElement = childElement;
                if (childElement == null)
                    throw AutomationElementSearchException.ElementNotFound(searchConditions[i], i);
            }
            throw new WhiteAssertionException("Something wrong in logic here");
        }

        public virtual AutomationElementCollection FindAll(AutomationElement startElement)
        {
            return FindAll(searchConditions.Length - 1, startElement);
        }
    }
}