using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.UIItems.MenuItems;

namespace Core.UIItems.WindowStripControls
{
    public class StatusStrip : ContainerStrip, MenuContainer
    {
        private readonly Menus topLevelMenu;
        protected StatusStrip() {}

        public StatusStrip(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            topLevelMenu = new Menus(automationElement, actionListener);
        }

        public virtual Menu MenuItem(params string[] path)
        {
            return topLevelMenu.Find(path);
        }
    }
}