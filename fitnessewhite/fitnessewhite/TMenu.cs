/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 9:45
 * 
 */

using System;
using Core.UIItems.MenuItems;
using Core.UIItems.WindowStripControls;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.Menu.
	/// </summary>
    public sealed class TMenu : FitUItem<Menu>
	{
        [MethodAttribute("从PopMenu中选中菜单，格式为\"PopMenuName;Menu1;Menu2;Menu3;...\"")]	
        public void PopupMenu(string value)
        {
            string[] items = SplitString(value);
			
	        	if (items.Length > 0)
                    Item = mainwin.PopupMenu(items);
	        	else
                    throw new ArgumentException("param format: PopMenuName;Menu1;Menu2;Menu3;...");
        }

        [MethodAttribute("从MenuBar中选中菜单，格式为\"MenuBarName;Menu1;Menu2;Menu3;...\"")]	
        public void MenuBarMenu(string value)
        {
            string[] items = SplitString(value);
            if (items.Length < 3) 
                throw new ArgumentException("param format: MenuBarName;Menu1;Menu2;Menu3;...");
            
            foreach (MenuBar w in mainwin.MenuBars)
            {
                if (!w.Name.Equals(items[0])) continue;
                string s = value.Substring(items[0].Length + 1);
                Item = w.MenuItem(SplitString(s));
            }        	
        }
	}
}
