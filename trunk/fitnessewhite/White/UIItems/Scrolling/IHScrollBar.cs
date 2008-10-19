namespace Core.UIItems.Scrolling
{
    public interface IHScrollBar : IScrollBar
    {
        void ScrollLeft();
        void ScrollRight();
        void ScrollLeftLarge();
        void ScrollRightLarge();
    }
}