using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.Custom
{
    public class CustomUIItem : UIItem
    {
        private UIItemContainer container;

        protected CustomUIItem(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        protected CustomUIItem() {}

        /// <summary>
        /// Container which can used to find the UIItems inside this item.
        /// e.g. Container.Get<TextBox>("day") to find a TextBox with AutomationId "day" inside this item.
        /// You can also use any SearchCriteria for performing the find
        /// </summary>
        protected virtual UIItemContainer Container
        {
            get { return container; }
        }

        internal virtual void SetContainer(UIItemContainer uiItemContainer)
        {
            container = uiItemContainer;
        }
    }
}