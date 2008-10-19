using Bricks;
using Core.UIItems;

namespace Core.UIItemEvents
{
    public class RadioButtonEvent : UserEvent
    {
        public RadioButtonEvent(IUIItem uiItem) : base(uiItem) {}

        protected override string ActionName(EventOption eventOption)
        {
            CodePath.New<RadioButton>().Select();
            return CodePath.Last;
        }
    }
}