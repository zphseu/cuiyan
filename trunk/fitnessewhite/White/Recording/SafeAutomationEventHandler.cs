using System;
using System.Windows.Automation;
using Core.Logging;
using Core.UIItemEvents;
using Core.UIItems;

namespace Core.Recording
{
    public class SafeAutomationEventHandler
    {
        private readonly IUIItem uiItem;
        private readonly Create createUserEvent;
        private UIItemEventListener eventListener;

        public delegate UserEvent Create(object[] parameters);

        public SafeAutomationEventHandler(IUIItem uiItem, UIItemEventListener eventListener, Create createUserEvent)
        {
            this.uiItem = uiItem;
            this.eventListener = eventListener;
            this.createUserEvent = createUserEvent;
        }

        public virtual void PropertyChange(object sender, AutomationPropertyChangedEventArgs e)
        {
            UserEvent userEvent = UserEvent(e);
            if (null == userEvent) return;
            try
            {
                eventListener.EventOccured(userEvent);
            }
            catch (Exception exception)
            {
                WhiteLogger.Instance.Error("", exception);
            }
        }

        private UserEvent UserEvent(AutomationPropertyChangedEventArgs e)
        {
            UserEvent userEvent;
            try
            {
                userEvent = createUserEvent.Invoke(new object[] {e});
            }
            catch (Exception exception)
            {
                userEvent = new ExceptionEvent(uiItem, exception);
            }
            return userEvent;
        }
    }
}