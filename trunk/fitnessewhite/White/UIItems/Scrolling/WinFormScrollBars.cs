using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.Scrolling
{
    public class WinFormScrollBars : ScrollBars
    {
        private IHScrollBar ihScrollBar;
        private IVScrollBar vScrollBar;

        public WinFormScrollBars(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public override IHScrollBar Horizontal
        {
            get
            {
                if (ihScrollBar == null) ihScrollBar = base.Horizontal;
                return ihScrollBar;
            }
        }

        public override IVScrollBar Vertical
        {
            get
            {
                if (vScrollBar == null) vScrollBar = base.Vertical;
                return vScrollBar;
            }
        }
    }
}