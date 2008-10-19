using System;
using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.Factory;
using Core.UIItems.Actions;

namespace Core.UIItems.MenuItems
{
    public class Menus : UIItemList<Menu>
    {
        private static readonly DictionaryMappedItemFactory factory = new DictionaryMappedItemFactory();

        public Menus(AutomationElement parent, ActionListener actionListener)
        {
            AutomationSearchCondition condition = AutomationSearchCondition.ByControlType(ControlType.MenuItem);
            AutomationElementFinder finder = new AutomationElementFinder(parent);
            finder = Performance_hack_as_popup_menu_for_Win32_app_comes_on_desktop(finder, parent);
            AutomationElementCollection children = finder.Descendants(condition);
            foreach (AutomationElement child in children)
                Add((Menu) factory.Create(child, actionListener));
        }

        private static AutomationElementFinder Performance_hack_as_popup_menu_for_Win32_app_comes_on_desktop(AutomationElementFinder finder,
                                                                                                             AutomationElement parent)
        {
            if (parent.Equals(AutomationElement.RootElement))
            {
                AutomationElement menuElement = finder.Child(AutomationSearchCondition.ByControlType(ControlType.Menu));
                if (menuElement == null)
                {
                    AutomationElement windowElement = finder.Child(AutomationSearchCondition.ByControlType(ControlType.Window));
                    menuElement = new AutomationElementFinder(windowElement).Child(AutomationSearchCondition.ByControlType(ControlType.Menu));
                }
                finder = new AutomationElementFinder(menuElement);
            }
            return finder;
        }

        public virtual Menu Find(params string[] path)
        {
            if (path.Length == 0) throw new ArgumentException("Menu path not specified");
            Menu item = Find(path[0]);
            if (item == null) throw new UIItemSearchException("Could not find Menu " + path[0]);
            for (int i = 1; i < path.Length; i++)
            {
                item.Click();
                item = item.SubMenu(path[i]);
                if (item == null) throw new UIItemSearchException("Could not find Menu " + path[i]);
            }
            return item;
        }

        public virtual Menu Find(string text)
        {
            return Find(delegate(Menu menuItem) { return menuItem.Name.Equals(text); });
        }
    }
}