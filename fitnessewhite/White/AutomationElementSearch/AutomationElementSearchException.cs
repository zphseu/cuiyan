using System;

namespace Core.AutomationElementSearch
{
    public class AutomationElementSearchException : Exception
    {
        public AutomationElementSearchException(string message) : base(message) {}

        public static AutomationElementSearchException ElementNotFound(AutomationSearchCondition condition, int i)
        {
            string message = string.Format("Could not find element for condition {0}", condition);
            if (i != 0) message += "at level " + i;
            return new AutomationElementSearchException(message);
        }
    }
}