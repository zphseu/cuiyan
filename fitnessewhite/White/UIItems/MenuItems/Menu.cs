using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.MenuItems
{
    public class Menu : UIItem
    {
        private Menus childMenus;
        protected Menu() {}
        public Menu(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual Menu SubMenu(string text)
        {
            return ChildMenus.Find(text);
        }

        public virtual Menus ChildMenus
        {
            get
            {
                if (childMenus != null) return childMenus;
                childMenus = new Menus(automationElement, actionListener);
                return childMenus;
            }
        }
    }
}