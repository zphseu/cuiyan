using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.ListBoxItems
{
    public abstract class ListItem : UIItem
    {
        protected ListItem() {}
        protected ListItem(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual bool IsSelected
        {
            get { return (bool) Property(SelectionItemPattern.IsSelectedProperty); }
        }

        public virtual string Text
        {
            get { return Name; }
        }

        public abstract bool Checked { get; }

        public virtual void Select()
        {
            actionListener.ActionPerforming(this);
            mouse.Click(C.ImmediateInteriorEast(Bounds), actionListener);
        }

        public abstract void Check();
        public abstract void UnCheck();
    }
}