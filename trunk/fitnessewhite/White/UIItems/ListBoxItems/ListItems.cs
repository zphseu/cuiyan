using System.Windows.Automation;
using Bricks.Core;
using Core.UIItems.Actions;

namespace Core.UIItems.ListBoxItems
{
    public class ListItems : UIItemList<ListItem>, ListItemContainer
    {
        private readonly ActionListener actionListener;

        public ListItems(AutomationElementCollection collection, ActionListener actionListener) : base(collection, actionListener)
        {
            this.actionListener = actionListener;
        }

        public virtual ListItem SelectedItem
        {
            get { return Find(delegate(ListItem obj) { return obj.IsSelected; }); }
        }

        public virtual string SelectedItemText
        {
            get
            {
                ListItem item = SelectedItem;
                return item == null ? string.Empty : item.Text;
            }
        }

        public virtual ListItem Item(string text)
        {
            ListItem foundItem = Find(delegate(ListItem obj) { return obj.Text.Equals(text); });
            if (foundItem == null) throw new UIActionException("Item of text " + text + " not found.");
            return foundItem;
        }

        public virtual void Select(string text)
        {
            S.AssertNotNull(text, "Selected text cannot be null, for empty pass empty string.");
            ListItem formListItem = Item(text);
            if (!formListItem.IsSelected) formListItem.Select();
            actionListener.ActionPerformed(Action.WindowMessage);
        }

        public virtual void Select(int index)
        {
            this[index].Select();
        }
    }
}