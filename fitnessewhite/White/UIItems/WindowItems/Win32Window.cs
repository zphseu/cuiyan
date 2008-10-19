using System.Windows.Automation;
using Core.Factory;
using Core.Sessions;
using Core.UIItems.Finders;
using Core.UIItems.MenuItems;

namespace Core.UIItems.WindowItems
{
    [PlatformSpecificItem]
    internal class Win32Window : Window
    {
        private readonly WindowFactory windowFactory;

        protected Win32Window() {}

        public Win32Window(AutomationElement automationElement, WindowFactory windowFactory, InitializeOption option, WindowSession windowSession)
            : base(automationElement, option, windowSession)
        {
            this.windowFactory = windowFactory;
        }

        public override T Get<T>(string primaryIdentification)
        {
            return Get<T>(SearchCriteria.ByText(primaryIdentification));
        }

        protected override PopUpMenu Popup
        {
            get { return windowFactory.PopUp(this); }
        }

        protected override ControlType MenuControlType
        {
            get { return ControlType.MenuBar; }
        }

        public override Window ModalWindow(string title, InitializeOption option)
        {
            return windowFactory.ModalWindow(title, option, windowSession.ModalWindowSession(option));
        }
    }
}