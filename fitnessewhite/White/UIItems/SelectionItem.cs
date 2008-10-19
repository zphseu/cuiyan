using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems
{
    public class SelectionItem : UIItem
    {
        protected SelectionItem() {}
        public SelectionItem(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual bool IsSelected
        {
            get { return (bool) Property(SelectionItemPattern.IsSelectedProperty); }
            set
            {
                if (IsSelected == value) return;
                if (value && !IsSelected)
                {
                    Select();
                }
            }
        }

        public virtual void Select()
        {
            Click();
        }
    }
}