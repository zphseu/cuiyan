using System.Windows.Automation;
using Bricks.Core;
using Core.AutomationElementSearch;
using Core.Configuration;
using Core.Sessions;
using Core.UIItems;
using Core.UIItems.WindowItems;

namespace Core.Factory
{
    public abstract class ChildWindowFactory
    {
        protected readonly AutomationElementFinder finder;

        protected ChildWindowFactory(AutomationElementFinder finder)
        {
            this.finder = finder;
        }

        public virtual Window ModalWindow(string title, InitializeOption option, WindowSession windowSession)
        {
            Clock.Do find = delegate { return finder.FindWindow(title, 0); };

            Clock clock = new Clock(CoreAppXmlConfiguration.Instance.BusyTimeout);
            Clock.Matched matched = delegate(object obj) { return obj != null; };
            Clock.Expired expired = delegate { return null; };
            AutomationElement automationElement = (AutomationElement) clock.Perform(find, matched, expired);
            return automationElement == null ? null: Create(automationElement, option, windowSession);
        }

        internal static Window Create(AutomationElement element, InitializeOption option, WindowSession windowSession)
        {
            WindowsFramework windowsFramework = new WindowsFramework(element.Current.FrameworkId);
            if (windowsFramework.WinForm) return new WinFormWindow(element, option, windowSession);
            if (windowsFramework.WPF) return new WPFWindow(element, WindowFactory.Desktop, option, windowSession);
            if (windowsFramework.Win32) return new Win32Window(element, WindowFactory.Desktop, option, windowSession);
            if (windowsFramework.UIAutomationBug) return null;
            throw new UIItemSearchException(windowsFramework + " is not supported yet.");
        }

        public virtual AutomationElementFinder Finder
        {
            get { return finder; }
        }
    }
}