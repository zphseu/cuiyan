using Bricks;
using Core.UIItems.TabItems;

namespace Core.UIItemEvents
{
    public class TabEvent : UserEvent
    {
        private static string action;
        private object[] parameters;

        static TabEvent()
        {
            CodePath.New<Tab>().SelectTabPage(null);
            action = CodePath.Last;
        }

        public TabEvent(Tab tab) : base(tab)
        {
            parameters = new object[] {tab.SelectedTab.Name};
        }

        protected override string ActionName(EventOption eventOption)
        {
            return action;
        }

        public override object[] ActionParameters
        {
            get { return parameters; }
        }
    }
}