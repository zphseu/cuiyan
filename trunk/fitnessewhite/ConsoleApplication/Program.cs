using System;
using Core;
using Core.Factory;
using Core.UIItems;
using Core.UIItems.WindowItems;
using Core.UIItems.MenuItems;
using Core.UIItems.WindowStripControls;

namespace ConsoleApplication
{
    class Program
    {
        static protected string[] SplitString(string value)
        {
            return value.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
        }

        static Menu MenuBarMenu(Window win, string value)
        {
            string[] items = SplitString(value);
            if (items.Length < 2)
                throw new ArgumentException("param format: MenuBarName;Menu1;Menu2;Menu3;...");

            foreach (MenuBar w in win.MenuBars)
            {
                if (!w.Name.Equals(items[0])) continue;
                string s = value.Substring(items[0].Length + 1);
                return w.MenuItem(SplitString(s));
            }

            throw new ArgumentException("param format: MenuBarName;Menu1;Menu2;Menu3;...");
        }

        static void Main(string[] args)
        {
            Application app = Application.Attach("calc");
            app.WaitWhileBusy();
            Window win = app.GetWindow("计算器", InitializeOption.NoCache);
            win.Focus();
            Menu m = MenuBarMenu(win, "应用程序;帮助(H);关于计算器(A)");
            m.Click();
        }
    }
}
