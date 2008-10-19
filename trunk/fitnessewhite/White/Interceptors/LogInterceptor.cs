using System;
using Bricks.DynamicProxy;
using Bricks.RuntimeFramework;
using Castle.Core.Interceptor;
using Core.Logging;

namespace Core.Interceptors
{
    public class LogInterceptor : DynamicProxyInterceptor, IEquatable<LogInterceptor>
    {
        public virtual void PreProcess(IInvocation invocation, object target)
        {
            Log(invocation, "Starting: ");
        }

        public virtual void PostProcess(IInvocation invocation, object target)
        {
            Log(invocation, "Finished: ");
        }

        private static void Log(IInvocation invocation, string prefix)
        {
            MethodInvocation methodInvocation = new MethodInvocation(invocation.Method, invocation.Arguments);
            WhiteLogger.Instance.Debug(prefix + invocation.InvocationTarget + ", " + methodInvocation);
        }

        public virtual bool Equals(LogInterceptor logInterceptor)
        {
            if (logInterceptor == null) return false;
            return GetType().Equals(logInterceptor.GetType());
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(this, obj)) return true;
            return Equals(obj as LogInterceptor);
        }

        public override int GetHashCode()
        {
            return GetType().GetHashCode();
        }
    }
}