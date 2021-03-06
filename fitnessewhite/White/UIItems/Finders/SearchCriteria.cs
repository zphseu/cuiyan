using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.UIItems.Custom;

namespace Core.UIItems.Finders
{
    /// <summary>
    /// SearchCritera can be used when UIItem identification is not satisfied by standard Get methods on UIItemContainer (Window is subclass of 
    /// UIItemContainer). Multiple criterias can be supplied together based on which the UIItem would be searched. All the conditions would put together as
    /// AND condition
    /// e.g. SearchCriteria.ByAutomationId("foo").ByControlType(typeof(TextBox)).Indexed(1)
    /// </summary>
    public class SearchCriteria
    {
        private readonly SearchConditions conditions = new SearchConditions();
        private IndexCondition indexCondition = IndexCondition.NotSpecified;
        private Type customItemType;

        private SearchCriteria(SearchCondition searchCondition)
        {
            conditions.Add(searchCondition);
        }

        internal SearchCriteria() {}

        public static SearchCriteria All
        {
            get { return new SearchCriteria(); }
        }

        /// <summary>
        /// Create a SearchCriteria with text
        /// </summary>
        /// <param name="text">For managed applications this is name given to controls in the application code. 
        /// For unmanaged applications this is text of the control or label next to it if it doesn't have well defined text.</param>
        /// <returns></returns>
        public static SearchCriteria ByText(string text)
        {
            return new SearchCriteria(new NameCondition(text));
        }

        /// <summary>
        /// Create criteria with specified index
        /// </summary>
        /// <param name="zeroBasedIndex"></param>
        /// <returns></returns>
        public static SearchCriteria Indexed(int zeroBasedIndex)
        {
            IndexCondition indexCondition = new IndexCondition(zeroBasedIndex);
            SearchCriteria criteria = new SearchCriteria(indexCondition);
            criteria.indexCondition = indexCondition;
            return criteria;
        }

        public static SearchCriteria ByAutomationId(string identification)
        {
            return new SearchCriteria(new AutomationIdCondition(identification));
        }

        public static SearchCriteria ByFramework(string framework)
        {
            return new SearchCriteria(new FrameworkIdCondition(framework));
        }

        public static SearchCriteria ByControlType(ControlType controlType)
        {
            return new SearchCriteria(new ControlTypeCondition(controlType));
        }

        public static SearchCriteria ByControlType(Type testControlType)
        {
            SearchCriteria searchCriteria = new SearchCriteria(new ControlTypeCondition(testControlType));
            searchCriteria.InferCustomItemType(testControlType);
            return searchCriteria;
        }

        internal virtual Condition AutomationCondition
        {
            get { return conditions.AutomationCondition; }
        }

        internal virtual Condition AutomationConditionWith(PropertyCondition propertyCondition)
        {
            Condition condition = conditions.AutomationCondition;
            return new AndCondition(condition, propertyCondition);
        }

        internal virtual bool IsIndexed
        {
            get { return indexCondition != IndexCondition.NotSpecified; }
        }

        public virtual Type CustomItemType
        {
            get { return customItemType; }
            set { customItemType = value; }
        }

        internal virtual AutomationSearchCondition AutomationSearchCondition
        {
            get
            {
                AutomationSearchCondition automationSearchCondition = new AutomationSearchCondition();
                foreach (SearchCondition searchCondition in conditions)
                {
                    automationSearchCondition.Add(searchCondition.AutomationCondition);
                }
                return automationSearchCondition;
            }
        }

        public virtual SearchCriteria AndIndex(int zeroBasedIndex)
        {
            indexCondition = new IndexCondition(zeroBasedIndex);
            conditions.Add(indexCondition);
            return this;
        }

        public virtual SearchCriteria AndByText(string text)
        {
            conditions.Insert(0, new NameCondition(text));
            return this;
        }

        public virtual SearchCriteria AndOfFramework(string frameworkId)
        {
            conditions.Insert(0, new FrameworkIdCondition(frameworkId));
            return this;
        }

        public virtual SearchCriteria NotIdentifiedByText(string name)
        {
            conditions.Insert(0, new NotCondition(new NameCondition(name)));
            return this;
        }

        public virtual SearchCriteria AndControlType(Type testControlType)
        {
            InferCustomItemType(testControlType);
            conditions.Insert(0, new ControlTypeCondition(testControlType));
            return this;
        }

        public virtual SearchCriteria AndAutomationId(string id)
        {
            conditions.Insert(0, new AutomationIdCondition(id));
            return this;
        }

        public virtual List<AutomationElement> Filter(List<AutomationElement> automationElements)
        {
            return conditions.Filter(automationElements);
        }

        public virtual SearchCriteria TextAsPrimaryIdentification()
        {
            AutomationIdCondition condition = (AutomationIdCondition) conditions.Find(delegate(SearchCondition obj) { return obj is AutomationIdCondition; });
            if (condition == null) return this;

            conditions.Remove(condition);
            conditions.Insert(0, new NameCondition(condition.AutomationId));
            return this;
        }

        public virtual IUIItem IndexedItem(UIItemCollection collection)
        {
            return indexCondition.Filter(collection);
        }

        public override string ToString()
        {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append(conditions.ToString());
            if (IsIndexed) stringBuilder.Append(",").Append(indexCondition.ToString());
            return stringBuilder.ToString();
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;
            SearchCriteria other = obj as SearchCriteria;
            if (other == null) return false;

            foreach (SearchCondition searchCondition in conditions)
                if (!other.conditions.Contains(searchCondition)) return false;

            return indexCondition.Equals(other.indexCondition);
        }

        public override int GetHashCode()
        {
            int hashCode = 0;
            foreach (SearchCondition condition in conditions)
                hashCode += condition.GetHashCode();
            return indexCondition.GetHashCode() + hashCode;
        }

        internal virtual bool AppliesTo(AutomationElement automationElement)
        {
            foreach (SearchCondition condition in conditions)
            {
                if (!condition.AppliesTo(automationElement))
                    return false;
            }
            return true;
        }

        internal virtual bool HasCondition(ControlType controlType)
        {
            ControlTypeCondition controlTypeCondition =
                conditions.Find(delegate(SearchCondition obj) { return obj is ControlTypeCondition; }) as ControlTypeCondition;
            return controlTypeCondition == null ? false : controlTypeCondition.ControlType.Equals(controlType);
        }

        private void InferCustomItemType(Type testControlType)
        {
            customItemType = typeof (CustomUIItem).IsAssignableFrom(testControlType) ? testControlType : null;
        }

        internal static SearchCriteria ForMenuBar(ControlType controlType)
        {
            return ByControlType(controlType).NotIdentifiedByText("System Menu Bar");
        }
    }
}