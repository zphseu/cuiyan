using Bricks.DynamicProxy;
using Core.Interceptors;
using Core.UIItems.Actions;
using Core.UIItems.Finders;

namespace Core.UIItems.Container
{
    public abstract class ContainerItemFactory
    {
        protected ActionListener actionListener;

        public virtual IUIItem Get(SearchCriteria searchCriteria, ActionListener uiItemActionListener)
        {
            IUIItem item = Find(searchCriteria);
            if (item == null || item is UIItemContainer)
            {
                //Cannot create dynamic proxy for class which has methods using generics. Also its not required to intercept methods on UIItem containers
                return item;
            }
            return (IUIItem) DynamicProxyGenerator.Instance.CreateProxy(new CoreInterceptor(item, actionListener), item.GetType());
        }

        protected abstract IUIItem Find(SearchCriteria searchCriteria);
        public abstract void Visit(WindowControlVisitor windowControlVisitor);
        public abstract UIItemCollection GetAll(SearchCriteria searchCriteria);
    }
}