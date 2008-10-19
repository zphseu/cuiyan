using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.UIItems.Actions;
using Core.UIItems.Scrolling;

namespace Core.UIItems.ListBoxItems
{
    //TODO: Find a better way for doing ActionPerforming, instead of putting it every method
    /// <summary>
    /// ListControl is made of up ListItems and scroll bars.
    /// </summary>
    public class ListControl : UIItem, ListItemContainer
    {
        protected AutomationElementFinder finder;
        protected ListControl() {}

        public ListControl(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            finder = new AutomationElementFinder(automationElement);
        }

        /// <summary>
        /// Returns all the items belonging to the ListControl
        /// </summary>
        public virtual ListItems Items
        {
            get { return new ListItems(finder.Descendants(AutomationSearchCondition.ByControlType(ControlType.ListItem)), this); }
        }

        public virtual ListItem Item(string itemText)
        {
            return Items.Item(itemText);
        }

        /// <summary>
        /// Selects list item which matches the text.
        /// (For WPF application the lists of objects might require you to provide a ToString override to be selected by text.
        /// The standard ToString method returns the objects type so all objects of the same type will look alike.)
        /// </summary>
        /// <param name="itemText"></param>
        public virtual void Select(string itemText)
        {
            Item(itemText).Select();
        }

        /// <summary>
        /// Slects list item by its index
        /// </summary>
        /// <param name="index"></param>
        public virtual void Select(int index)
        {
            Items.Select(index);
        }

        public virtual string SelectedItemText
        {
            get { return Items.SelectedItemText; }
        }

        public virtual ListItem SelectedItem
        {
            get { return Items.SelectedItem; }
        }

        public override void SetValue(object value)
        {
            Select(value.ToString());
        }

        public override void ActionPerforming(UIItem uiItem)
        {
            ScreenItem screenItem = new ScreenItem(uiItem, ScrollBars);
            screenItem.MakeVisible(VerticalSpan);
        }

        protected virtual VerticalSpan VerticalSpan
        {
            get { return new VerticalSpan(Bounds); }
        }
    }
}