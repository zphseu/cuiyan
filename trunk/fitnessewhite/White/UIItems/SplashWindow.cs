using System.Windows.Automation;
using Core.Factory;
using Core.UIItems.WindowItems;

namespace Core.UIItems
{
    internal class SplashWindow : WinFormWindow
    {
        protected SplashWindow() {}
        public SplashWindow(AutomationElement automationElement, InitializeOption option) : base(automationElement, option) {}

        public override void WaitWhileBusy() {}
    }
}