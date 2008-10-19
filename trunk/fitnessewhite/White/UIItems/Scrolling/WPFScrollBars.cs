using System.Windows.Automation;
using Bricks.RuntimeFramework;
using Core.UIItems.Actions;

namespace Core.UIItems.Scrolling
{
    public class WPFScrollBars : IScrollBars
    {
        private readonly AutomationElement parentElement;
        private readonly ActionListener actionListener;

        public WPFScrollBars(AutomationElement parentElement, ActionListener actionListener)
        {
            this.parentElement = parentElement;
            this.actionListener = actionListener;
        }

        public virtual IHScrollBar Horizontal
        {
            get
            {
                BricksCollection<AutomationPattern> patterns = new BricksCollection<AutomationPattern>(parentElement.GetSupportedPatterns());
                return patterns.Contains(ScrollPattern.Pattern) ? (IHScrollBar) new WPFHScrollBar(parentElement, actionListener) : new NullHScrollBar();
            }
        }
        public virtual IVScrollBar Vertical
        {
            get
            {
                BricksCollection<AutomationPattern> patterns = new BricksCollection<AutomationPattern>(parentElement.GetSupportedPatterns());
                return patterns.Contains(ScrollPattern.Pattern) ? (IVScrollBar) new WPFVScrollBar(parentElement, actionListener) : new NullVScrollBar();
            }
        }
    }
}