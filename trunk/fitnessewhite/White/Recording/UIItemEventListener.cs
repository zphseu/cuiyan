using Core.UIItemEvents;

namespace Core.Recording
{
    public interface UIItemEventListener
    {
        void EventOccured(UserEvent userEvent);
    }
}