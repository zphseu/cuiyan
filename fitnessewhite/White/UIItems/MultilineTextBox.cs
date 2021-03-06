using System.Windows.Automation;
using Core.Recording;
using Core.UIItemEvents;
using Core.UIItems.Actions;
using Core.WindowsAPI;

namespace Core.UIItems
{
    public class MultilineTextBox : TextBox, Scrollable
    {
        private AutomationEventHandler handler;
        protected MultilineTextBox() {}
        public MultilineTextBox(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public override string Text
        {
            get
            {
                TextPattern pattern = (TextPattern) Pattern(TextPattern.Pattern);
                return pattern.DocumentRange.GetText(int.MaxValue);
            }
            set
            {
                TextPattern pattern = (TextPattern) Pattern(TextPattern.Pattern);
                pattern.DocumentRange.Select();
                actionListener.ActionPerformed(Action.WindowMessage);
                keyboard.PressSpecialKey(KeyboardInput.SpecialKeys.DELETE, actionListener);
                actionListener.ActionPerformed(Action.WindowMessage);
                EnterData(value);
            }
        }

        public override void HookEvents(UIItemEventListener eventListener)
        {
            handler = delegate { eventListener.EventOccured(new MultilineTextBoxEvent(this)); };
            Automation.AddAutomationEventHandler(TextPattern.TextSelectionChangedEvent, automationElement, TreeScope.Element, handler);
        }

        public override void UnHookEvents()
        {
            Automation.RemoveAutomationEventHandler(TextPattern.TextSelectionChangedEvent, automationElement, handler);
        }
    }
}