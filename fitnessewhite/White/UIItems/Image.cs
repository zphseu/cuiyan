using System.Windows.Automation;
using Core.Recording;
using Core.UIItems.Actions;

namespace Core.UIItems
{
    public class Image : UIItem
    {
        protected Image() {}
        public Image(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public override void HookEvents(UIItemEventListener eventListener)
        {
            HookClickEvent(eventListener);
        }

        public override void UnHookEvents()
        {
            UnHookClickEvent();
        }
    }
}