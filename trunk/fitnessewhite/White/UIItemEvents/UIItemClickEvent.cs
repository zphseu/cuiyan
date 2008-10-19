using Bricks;
using Core.UIItems;

namespace Core.UIItemEvents
{
    public class UIItemClickEvent : UserEvent
    {
        private static readonly string actionName;

        static UIItemClickEvent()
        {
            CodePath.New<UIItem>().Click();
            actionName = CodePath.Last;
        }

        public UIItemClickEvent(IUIItem uiItem) : base(uiItem) {}

        protected override string ActionName(EventOption eventOption)
        {
            return actionName;
        }
    }
}