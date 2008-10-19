using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.MenuItems
{
    public class PopUpMenu : UIItem
    {
        private readonly Menus topLevelMenus;
        protected PopUpMenu() {}

        public PopUpMenu(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            this.actionListener = actionListener;
            topLevelMenus = new Menus(automationElement, actionListener);
        }

        public virtual Menu Item(params string[] text)
        {
            return topLevelMenus.Find(text);
        }
    }
}