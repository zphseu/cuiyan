using Bricks.DynamicProxy;
using Core.UIItems;
using Core.UIItems.Actions;

namespace Core.Interceptors
{
    public class CoreInterceptContext : InterceptContext
    {
        private readonly IUIItem uiItem;
        private readonly ActionListener actionListener;

        public CoreInterceptContext(IUIItem uiItem, ActionListener actionListener)
        {
            this.uiItem = uiItem;
            this.actionListener = actionListener;
        }

        public virtual IUIItem UiItem
        {
            get { return uiItem; }
        }

        public virtual ActionListener ActionListener
        {
            get { return actionListener; }
        }

        public virtual object Target
        {
            get { return uiItem; }
        }
    }
}