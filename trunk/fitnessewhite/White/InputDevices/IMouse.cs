using System.Drawing;
using Core.UIItems;

namespace Core.InputDevices
{
    public interface IMouse
    {
        Point Location { get; set; }
        void RightClick();
        void Click();
        void DoubleClick(Point point);
        void Click(Point point);
        void DragAndDrop(IUIItem draggedItem, IUIItem dropItem);
    }
}