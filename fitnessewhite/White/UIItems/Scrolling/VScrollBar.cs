using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.Scrolling
{
    internal class VScrollBar : ScrollBar, IVScrollBar
    {
        protected VScrollBar() {}
        public VScrollBar(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual void ScrollUp()
        {
            backSmallChangeButton.Click();
        }

        public virtual void ScrollDown()
        {
            forwardSmallChangeButton.Click();
        }

        public virtual void ScrollUpLarge()
        {
            backLargeChangeButton.Click();
        }

        public virtual void ScrollDownLarge()
        {
            forwardLargeChangeButton.Click();
        }

        public virtual bool IsScrollable
        {
            get { return true; }
        }
    }
}