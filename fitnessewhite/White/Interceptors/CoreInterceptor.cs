using System;
using Bricks.DynamicProxy;
using Castle.Core.Interceptor;
using Core.Configuration;
using Core.Logging;
using Core.UIItems;
using Core.UIItems.Actions;

namespace Core.Interceptors
{
    public class CoreInterceptor : IInterceptor
    {
        private readonly CoreInterceptContext coreInterceptContext;

        public CoreInterceptor(IUIItem uiItem, ActionListener actionListener)
        {
            coreInterceptContext = new CoreInterceptContext(uiItem, actionListener);
        }

        public virtual void Intercept(IInvocation invocation)
        {
            try
            {
                CoreAppXmlConfiguration.Instance.Interceptors.Process(invocation, coreInterceptContext);
            }
            catch (Exception)
            {
                WhiteLogger.Instance.Error(DynamicProxyInterceptors.ToString(invocation));
                throw;
            }
        }

        public virtual CoreInterceptContext Context
        {
            get { return coreInterceptContext; }
        }
    }
}