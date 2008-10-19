using System;
using Bricks.DynamicProxy;
using Castle.Core.Interceptor;
using Castle.DynamicProxy;

namespace Bricks
{
    public class CodePath
    {
        private static readonly CodePathInterceptor interceptor;
        private static readonly CachedDynamicProxyGenerator generator;

        protected static bool pathRetrieved = false;
        private static Type t;

        public static T New<T>()
        {
            if (pathRetrieved)
            {
                throw new TraceException(
                    string.Format("Previous call to New with type '{0}' and method '{1}' was not followed by call to Member/MemberPath.", t.Name,
                                  interceptor.Method));
            }
            pathRetrieved = true;
            t = typeof (T);

            object obj = generator.GetProxy(typeof (T), interceptor);
            interceptor.Clear();
            return (T) obj;
        }

        public static void Reset()
        {
            pathRetrieved = false;
        }

        static CodePath()
        {
            generator = new CachedDynamicProxyGenerator();
            interceptor = new CodePathInterceptor(generator);
        }

        public static string Get(object dummy)
        {
            pathRetrieved = false;
            if (interceptor.Method == null || interceptor.Method.EndsWith("."))
                throw new TraceException("Method/Property Not Virtual.");
            return interceptor.Method;
        }

        public static string Last
        {
            get { return Get(null); }
        }

        public static string VoidMember
        {
            get { return Get(null); }
        }

        public static string Complete(object dummy)
        {
            return interceptor.Class + "." + Get(dummy);
        }
    }

    [Serializable]
    public class TraceException : Exception
    {
        public TraceException(string message) : base(message) {}
    }

    internal class BindProxyEnumGenerator
    {
        private readonly ProxyGenerator generator = new ProxyGenerator();

        public virtual object getProxy(Type type, string propertyName)
        {
            return generator.CreateClassProxy(type, new EnumInterceptor(propertyName));
        }
    }

    internal class EnumInterceptor : IInterceptor
    {
        private readonly string propertyName;

        public EnumInterceptor(string propertyName)
        {
            this.propertyName = propertyName;
        }

        public virtual void Intercept(IInvocation invocation)
        {
            invocation.ReturnValue = propertyName;
        }
    }
}