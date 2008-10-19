using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.Recording;
using Core.UIItemEvents;
using Core.UIItems.Actions;

namespace Core.UIItems.TabItems
{
    public class Tab : UIItem
    {
        private TabPages pages;
        private AutomationPropertyChangedEventHandler handler;
        protected Tab() {}

        public Tab(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual ITabPage SelectedTab
        {
            get { return Pages.Find(delegate(ITabPage tabPage) { return tabPage.IsSelected; }); }
        }

        public virtual int TabCount
        {
            get { return Pages.Count; }
        }

        public virtual TabPages Pages
        {
            get
            {
                if (pages == null)
                {
                    pages = new TabPages();
                    AutomationElementFinder finder = new AutomationElementFinder(automationElement);
                    AutomationElementCollection collection = finder.Children(AutomationSearchCondition.ByControlType(ControlType.TabItem));
                    foreach (AutomationElement tabItemElement in collection)
                        pages.Add(new TabPage(tabItemElement, actionListener));
                }

                return pages;
            }
        }

        public virtual void SelectTabPage(int index)
        {
            ITabPage tabPage = Pages[index];
            tabPage.Select();
        }

        public virtual void SelectTabPage(string tabTitle)
        {
            ITabPage oldTab = SelectedTab;
            Pages.Find(delegate(ITabPage tabItem) { return tabItem.NameMatches(tabTitle); }).Select();
            if (!oldTab.Equals(SelectedTab)) actionListener.ActionPerformed(new Action(ActionType.NewControls));
        }

        public override void HookEvents(UIItemEventListener eventListener)
        {
            handler = delegate { eventListener.EventOccured(new TabEvent(this)); };
            Automation.AddAutomationPropertyChangedEventHandler(automationElement, TreeScope.Descendants, handler, SelectionItemPattern.IsSelectedProperty);
        }

        public override void UnHookEvents()
        {
            Automation.RemoveAutomationPropertyChangedEventHandler(automationElement, handler);
        }
    }
}