using Bricks.DynamicProxy;
using Castle.Core.Interceptor;
using Core.UIItems;

namespace Core.Interceptors
{
    //Doc PrimaryUIItems would be scrolled automatically but secondary wont
    public class ScrollInterceptor : DynamicProxyInterceptor
    {
        public virtual void PreProcess(IInvocation invocation, object target)
        {
            CoreInterceptContext coreInterceptContext = (CoreInterceptContext) target;
            coreInterceptContext.ActionListener.ActionPerforming((UIItem) coreInterceptContext.UiItem);
        }

        public virtual void PostProcess(IInvocation invocation, object target) {}
    }
}