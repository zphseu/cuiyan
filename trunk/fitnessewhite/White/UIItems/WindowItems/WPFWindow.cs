using System.Diagnostics;
using System.Windows.Automation;
using Core.Factory;
using Core.Sessions;
using Core.UIItems.MenuItems;

namespace Core.UIItems.WindowItems
{
    [PlatformSpecificItem]
    internal class WPFWindow : Window
    {
        private readonly WindowFactory windowFactory;
        protected WPFWindow() {}

        public WPFWindow(AutomationElement automationElement, WindowFactory windowFactory, InitializeOption initializeOption, WindowSession windowSession)
            : base(automationElement, initializeOption, windowSession)
        {
            this.windowFactory = windowFactory;
        }

        protected override PopUpMenu Popup
        {
            get
            {
                PopUpMenu popupMenu = factory.WPFPopupMenu(this);
                if (popupMenu == null) popupMenu = windowFactory.PopUp(this);
                return popupMenu;
            }
        }

        protected override ControlType MenuControlType
        {
            get { return ControlType.Menu; }
        }

        public override Window ModalWindow(string title, InitializeOption option)
        {
            WindowFactory desktopWindowsFactory = WindowFactory.Desktop;
            return
                desktopWindowsFactory.FindModalWindow(title, Process.GetProcessById(automationElement.Current.ProcessId), option, automationElement,
                                                      windowSession.ModalWindowSession(option));
        }
    }
}