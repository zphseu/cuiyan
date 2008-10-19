using System.Windows;
using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.Scrolling
{
    [PlatformSpecificItem(ReferAsType = typeof (IHScrollBar))]
    public class WPFHScrollBar : WPFScrollBar, IHScrollBar
    {
        private readonly ActionListener actionListener;

        public WPFHScrollBar(AutomationElement parent, ActionListener actionListener) : base(parent)
        {
            this.actionListener = actionListener;
        }

        public override double Value
        {
            get { return scrollPattern.Current.HorizontalScrollPercent; }
        }

        protected override double ScrollPercentage
        {
            get { return scrollPattern.Current.HorizontalViewSize; }
        }

        public override Rect Bounds
        {
            get { return Rect.Empty; }
        }

        protected virtual void Scroll(ScrollAmount amount)
        {
            if (!scrollPattern.Current.HorizontallyScrollable) return;

            scrollPattern.ScrollHorizontal(amount);
            actionListener.ActionPerformed(Action.WindowMessage);
        }

        public virtual void ScrollLeft()
        {
            Scroll(ScrollAmount.SmallDecrement);
        }

        public virtual void ScrollRight()
        {
            Scroll(ScrollAmount.SmallIncrement);
        }

        public virtual void ScrollLeftLarge()
        {
            Scroll(ScrollAmount.LargeDecrement);
        }

        public virtual void ScrollRightLarge()
        {
            Scroll(ScrollAmount.LargeIncrement);
        }

        public override void SetToMinimum()
        {
            SetToMinimum(ScrollLeftLarge);
        }

        public override void SetToMaximum()
        {
            SetToMaximum(ScrollRightLarge);
        }
    }
}