using System.Windows.Automation;
using Core.Factory;
using Core.Sessions;
using Core.UIItems.MenuItems;
using Core.UIItems.Scrolling;

namespace Core.UIItems.WindowItems
{
    [PlatformSpecificItem]
    internal class WinFormWindow : Window
    {
        private WinFormScrollBars winFormScrollBars;
        protected WinFormWindow() {}

        public WinFormWindow(AutomationElement automationElement, InitializeOption initializeOption)
            : this(automationElement, initializeOption, new NullWindowSession()) {}

        internal WinFormWindow(AutomationElement automationElement, InitializeOption initializeOption, WindowSession windowSession)
            : base(automationElement, initializeOption, windowSession) {}

        protected override PopUpMenu Popup
        {
            get
            {
                PopUpMenu popUpMenu;
                factory.TryGetPopupMenu(this, out popUpMenu);
                return popUpMenu;
            }
        }

        protected override ControlType MenuControlType
        {
            get { return ControlType.MenuBar; }
        }

        public override T Get<T>(string primaryIdentification)
        {
            if (typeof (T).Equals(typeof (Image)))
            {
                IUIItem image = factory.WinFormImage(primaryIdentification, this);
                return (T) image;
            }
            return base.Get<T>(primaryIdentification);
        }

        public override bool HasPopup()
        {
            PopUpMenu popUpMenu;
            return factory.TryGetPopupMenu(this, out popUpMenu);
        }

        public override Window ModalWindow(string title, InitializeOption option)
        {
            return factory.ModalWindow(title, option, windowSession.ModalWindowSession(option));
        }

        public override IScrollBars ScrollBars
        {
            get
            {
                if (winFormScrollBars == null) winFormScrollBars = new WinFormScrollBars(automationElement, actionListener);
                return winFormScrollBars;
            }
        }
    }
}