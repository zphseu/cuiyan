using System;
using System.Diagnostics;
using System.Reflection;

namespace Bricks.RuntimeFramework
{
    public class Method : CodeMember
    {
        public Method(MethodInfo methodInfo) : base(methodInfo) {}

        public override string ToString()
        {
            return memberInfo.Name;
        }

        public static Method CallingMethod(Predicate<MethodBase> predicate)
        {
            StackTrace stackTrace = new StackTrace();
            StackFrame[] frames = stackTrace.GetFrames();
            foreach (StackFrame stackFrame in frames)
            {
                MethodBase method = stackFrame.GetMethod();
                if (predicate.Invoke(method)) return new Method((MethodInfo) method);
            }
            return null;
        }

        public virtual MethodInfo MethodInfo
        {
            get { return (MethodInfo) memberInfo; }
        }
    }

    public class Property : CodeMember
    {
        public Property(PropertyInfo propertyInfo) : base(propertyInfo) {}

        public override string ToString()
        {
            return memberInfo.Name;
        }
    }
}