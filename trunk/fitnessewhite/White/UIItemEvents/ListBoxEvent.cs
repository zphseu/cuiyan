using Core.UIItems;

namespace Core.UIItemEvents
{
    public class ListBoxEvent : ListControlEvent
    {
        public ListBoxEvent(IUIItem uiItem, string selectedItem) : base(uiItem, selectedItem) {}
    }
}