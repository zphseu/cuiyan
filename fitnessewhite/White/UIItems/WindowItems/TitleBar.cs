using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.UIItems.Actions;

namespace Core.UIItems.WindowItems
{
    public class TitleBar : UIItem
    {
        private readonly AutomationElementFinder automationElementFinder;

        public TitleBar(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            automationElementFinder = new AutomationElementFinder(automationElement);
        }

        protected TitleBar() {}

        public virtual Button MinimizeButton
        {
            get { return FindButton("Minimize"); }
        }

        public virtual Button MaximizeButton
        {
            get { return FindButton("Maximize"); }
        }

        public virtual Button RestoreButton
        {
            get { return FindButton("Restore"); }
        }

        public virtual Button CloseButton
        {
            get { return FindButton("Close"); }
        }

        private Button FindButton(string automationId)
        {
            AutomationElement element =
                automationElementFinder.Child(AutomationSearchCondition.ByControlType(ControlType.Button).WithAutomationId(automationId));
            if (element == null) return null;
            return new Button(element, actionListener);
        }
    }
}