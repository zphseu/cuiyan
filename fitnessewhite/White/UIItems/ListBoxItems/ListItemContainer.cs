namespace Core.UIItems.ListBoxItems
{
    public interface ListItemContainer
    {
        ListItem Item(string itemText);
        void Select(string itemText);
        void Select(int index);
        string SelectedItemText { get; }
        ListItem SelectedItem { get; }
    }
}