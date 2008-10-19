using Core.Factory;
using Core.UIItems;
using Core.UIItems.Actions;
using Core.UIItems.Container;
using Core.UIItems.Finders;
using Core.UIItems.WindowItems;

namespace Core.Sessions
{
    public class NullWindowSession : WindowSession
    {
        public override WindowSession ModalWindowSession(InitializeOption modalInitializeOption)
        {
            return new NullWindowSession();
        }

        public override IUIItem Get(ContainerItemFactory containerItemFactory, SearchCriteria searchCriteria, ActionListener actionListener)
        {
            return containerItemFactory.Get(searchCriteria, actionListener);
        }

        public override void Dispose() {}

        public override void Register(Window window) {}
    }
}