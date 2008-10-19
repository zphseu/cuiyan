using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.UIItems.Actions;

namespace Core.UIItems.Scrolling
{
    public class ScrollBars : IScrollBars
    {
        private readonly ActionListener actionListener;
        protected readonly AutomationElementFinder finder;

        protected delegate AutomationElement FindElement(AutomationSearchCondition condition);

        public ScrollBars(AutomationElement automationElement, ActionListener actionListener)
        {
            this.actionListener = actionListener;
            finder = new AutomationElementFinder(automationElement);
        }

        public virtual IHScrollBar Horizontal
        {
            get { return FindHorizontalBar(finder.Child); }
        }

        protected virtual IHScrollBar FindHorizontalBar(FindElement findElement)
        {
            AutomationElement horizontalScrollElement =
                findElement(AutomationSearchCondition.ByAutomationId("Horizontal ScrollBar").OfControlType(ControlType.ScrollBar));
            if (horizontalScrollElement == null) return new NullHScrollBar();
            return new HScrollBar(horizontalScrollElement, actionListener);
        }

        public virtual IVScrollBar Vertical
        {
            get { return FindVerticalBar(finder.Child); }
        }

        protected virtual IVScrollBar FindVerticalBar(FindElement findElement)
        {
            AutomationElement verticalScrollElement =
                findElement(AutomationSearchCondition.ByAutomationId("Vertical ScrollBar").OfControlType(ControlType.ScrollBar));
            if (verticalScrollElement == null) return new NullVScrollBar();
            else return new VScrollBar(verticalScrollElement, actionListener);
        }
    }
}