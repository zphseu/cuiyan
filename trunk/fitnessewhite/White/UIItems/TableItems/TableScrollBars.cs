using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.UIItems.Actions;
using Core.UIItems.Scrolling;

namespace Core.UIItems.TableItems
{
    public class TableScrollBars : IScrollBars
    {
        private readonly IVScrollBar verticalScrollBar;
        private readonly IHScrollBar horizontalScrollBar;

        public TableScrollBars(AutomationElementFinder finder, ActionListener actionListener)
        {
            AutomationElement verticalScrollElement = finder.Child(AutomationSearchCondition.ByControlType(ControlType.Pane).OfName("Vertical Scroll Bar"));
            verticalScrollBar = (verticalScrollElement == null)
                                    ? (IVScrollBar) new NullVScrollBar()
                                    : new TableVerticalScrollBar(verticalScrollElement, actionListener);
            AutomationElement horizontalScrollElement = finder.Child(AutomationSearchCondition.ByControlType(ControlType.Pane).OfName("Horizontal Scroll Bar"));
            horizontalScrollBar = (horizontalScrollElement == null)
                                      ? (IHScrollBar) new NullHScrollBar()
                                      : new TableHorizontalScrollBar(horizontalScrollElement, actionListener);
        }

        public virtual IHScrollBar Horizontal
        {
            get { return horizontalScrollBar; }
        }

        public virtual IVScrollBar Vertical
        {
            get { return verticalScrollBar; }
        }
    }
}