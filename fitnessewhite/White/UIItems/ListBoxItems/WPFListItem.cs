using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.Factory;
using Core.UIItems.Actions;
using Core.UIItems.Finders;

namespace Core.UIItems.ListBoxItems
{
    [PlatformSpecificItem]
    public class WPFListItem : ListItem
    {
        protected WPFListItem() {}
        public WPFListItem(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        private CheckBox CheckBox
        {
            get { return (CheckBox) factory.Create(SearchCriteria.ByControlType(ControlType.CheckBox), actionListener); }
        }

        public override bool Checked
        {
            get { return CheckBox.Checked; }
        }

        public override void Check()
        {
            if (!Checked)
                CheckBox.Click();
        }

        public override void UnCheck()
        {
            if (Checked)
                CheckBox.Click();
        }

        public virtual T Get<T>(SearchCriteria searchCriteria)
        {
            return (T) new PrimaryUIItemFactory(new AutomationElementFinder(automationElement)).Create(searchCriteria, actionListener);
        }

        public virtual UIItemCollection GetAll(SearchCriteria searchCriteria)
        {
            return new PrimaryUIItemFactory(new AutomationElementFinder(automationElement)).CreateAll(searchCriteria, actionListener);
        }
    }
}