using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.UIItems.Actions;

namespace Core.UIItems.ListBoxItems
{
    [PlatformSpecificItem]
    public class WinFormComboBox : ComboBox
    {
        protected WinFormComboBox() {}

        public WinFormComboBox(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual string Text
        {
            get { return GetTextBox().Text; }
            set { GetTextBox().Text = value; }
        }

        private TextBox GetTextBox()
        {
            return new TextBox(finder.Child(AutomationSearchCondition.ByControlType(ControlType.Edit)), actionListener);
        }
    }
}