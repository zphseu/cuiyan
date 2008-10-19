using Core.UIItems;

namespace Core.UIItemEvents
{
    public class ComboBoxEvent : ListControlEvent
    {
        public ComboBoxEvent(IUIItem uiItem, string selectedItem) : base(uiItem, selectedItem) {}
    }
}