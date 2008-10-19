using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.Logging;
using Core.Recording;
using Core.UIItemEvents;
using Core.UIItems.Actions;
using Core.UIItems.Scrolling;

namespace Core.UIItems.ListBoxItems
{
    public class ComboBox : ListControl
    {
        private AutomationPropertyChangedEventHandler handler;
        private ListItem lastSelectedItem;

        protected ComboBox() {}

        public ComboBox(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            this.actionListener = actionListener;
            MakeActionReady();
        }

        protected override VerticalSpan VerticalSpan
        {
            get
            {
                AutomationElement listElement = finder.Child(AutomationSearchCondition.ByControlType(ControlType.List));
                UIItem listContainerItem = new UIItem(listElement, new NullActionListener());
                return new VerticalSpan(listContainerItem.Bounds).Union(listContainerItem.Bounds);
            }
        }

        public override IScrollBars ScrollBars
        {
            get { return new ComboBoxScrollBars(automationElement, actionListener); }
        }

        public override void Select(string itemText)
        {
            if (!Enabled)
            {
                WhiteLogger.Instance.Warn("Could not select " + itemText + "in " + Name + " since it is disabled");
                return;
            }
            ToggleDropDown();
            base.Select(itemText);
            actionListener.ActionPerformed(Action.WindowMessage);
        }

        protected virtual void MakeActionReady()
        {
            ToggleDropDown();
            ToggleDropDown();
        }

        protected virtual void ToggleDropDown()
        {
            Button button = new Button(finder.Child(AutomationSearchCondition.ByControlType(ControlType.Button)), actionListener);
            button.InternalClick();
        }

        public override void HookEvents(UIItemEventListener eventListener)
        {
            lastSelectedItem = SelectedItem;
            handler = delegate(object sender, AutomationPropertyChangedEventArgs e)
                          {
                              if (SelectedItem == null || e.NewValue.Equals(1)) return;
                              if (SameListItem()) return;
                              lastSelectedItem = SelectedItem;
                              eventListener.EventOccured(new ComboBoxEvent(this, SelectedItemText));
                          };
            Automation.AddAutomationPropertyChangedEventHandler(automationElement, TreeScope.Element, handler,
                                                                ExpandCollapsePattern.ExpandCollapseStateProperty);
        }

        public override void UnHookEvents()
        {
            Automation.RemoveAutomationPropertyChangedEventHandler(automationElement, handler);
        }

        private bool SameListItem()
        {
            if (lastSelectedItem == null && SelectedItem != null) return false;
            return SelectedItemText.Equals(lastSelectedItem.Text);
        }
    }
}