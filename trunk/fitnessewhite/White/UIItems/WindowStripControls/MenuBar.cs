using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.UIItems.MenuItems;

namespace Core.UIItems.WindowStripControls
{
    public class MenuBar : UIItem, MenuContainer
    {
        private readonly Menus topLevelMenu;
        protected MenuBar() {}

        public MenuBar(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            topLevelMenu = new Menus(automationElement, actionListener);
        }

        public virtual Menu MenuItem(params string[] path)
        {
            return topLevelMenu.Find(path);
        }

        public virtual Menus TopLevelMenu
        {
            get { return topLevelMenu; }
        }
    }
}