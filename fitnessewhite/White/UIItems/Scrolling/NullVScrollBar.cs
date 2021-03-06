using System.Windows;

namespace Core.UIItems.Scrolling
{
    //BUG: Add LogStatements to make sure that the logging is not happening in NullScrollBar
    public class NullVScrollBar : NullScrollBar, IVScrollBar
    {
        public virtual void ScrollUp()
        {
            throw new WhiteAssertionException();
        }

        public virtual void ScrollDown() {}

        public virtual void ScrollUpLarge() {}

        public virtual void ScrollDownLarge() {}
        
        public virtual bool IsScrollable
        {
            get { return false; }
        }

        public virtual Rect Bounds
        {
            get { return Rect.Empty; }
        }
    }
}