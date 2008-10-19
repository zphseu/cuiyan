using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.Scrolling
{
    [PlatformSpecificItem(ReferAsType = typeof (IHScrollBar))]
    internal class HScrollBar : ScrollBar, IHScrollBar
    {
        protected HScrollBar() {}

        public HScrollBar(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual void ScrollLeft()
        {
            backSmallChangeButton.Click();
        }

        public virtual void ScrollRight()
        {
            forwardSmallChangeButton.Click();
        }

        public virtual void ScrollLeftLarge()
        {
            backLargeChangeButton.Click();
        }

        public virtual void ScrollRightLarge()
        {
            forwardLargeChangeButton.Click();
        }
    }
}