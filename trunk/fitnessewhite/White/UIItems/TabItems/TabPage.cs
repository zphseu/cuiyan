using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.TabItems
{
    public class TabPage : UIItem, ITabPage
    {
        private readonly SelectionItem selectionItem;

        protected TabPage() {}

        public TabPage(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            selectionItem = new SelectionItem(automationElement, actionListener);
        }

        public virtual bool IsSelected
        {
            get { return selectionItem.IsSelected; }
        }

        public virtual void Select()
        {
            selectionItem.Select();
        }

        public override string ToString()
        {
            return Name;
        }
    }

    public class TabPages : UIItemList<ITabPage> {}
}