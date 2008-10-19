using System.Windows;
using Bricks.Core;
using Core.Configuration;

namespace Core.UIItems.Scrolling
{
    public class ScreenItem
    {
        private readonly UIItem uiItem;
        private readonly IVScrollBar verticalScroll;

        public ScreenItem(UIItem uiItem, IScrollBars scrollBars)
        {
            this.uiItem = uiItem;
            if (scrollBars == null || scrollBars.Vertical == null) return;

            verticalScroll = scrollBars.Vertical;
        }

        internal virtual void MakeVisible(VerticalSpan verticalSpan)
        {
            if (verticalScroll == null || !verticalScroll.IsScrollable) return;

            if (verticalScroll.Value > 0 && verticalSpan.IsOutside(uiItem.Bounds)) verticalScroll.SetToMinimum();

            Clock clock = new Clock(CoreAppXmlConfiguration.Instance.BusyTimeout, 0);
            clock.RunWhile(delegate { verticalScroll.ScrollDownLarge(); }, delegate
                                                                               {
                                                                                   Rect bounds = uiItem.Bounds;
                                                                                   return verticalSpan.IsOutside(bounds);
                                                                               },
                           delegate { throw new UIActionException("Could not make the " + uiItem + " visible" + Constants.BusyMessage); });
        }
    }
}