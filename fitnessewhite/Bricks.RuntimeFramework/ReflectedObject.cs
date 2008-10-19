using System;
using System.Collections.Generic;
using System.Reflection;

namespace Bricks.RuntimeFramework
{
    public class ReflectedObject
    {
        private readonly object o;
        private readonly Class @class;
        private static Type ignoredType;
        private readonly Fields fields;

        public ReflectedObject(object o)
        {
            this.o = o;
            if (o != null)
            {
                @class = new Class(o.GetType());
                @class.IgnoreClass(ignoredType);
                fields = new Fields(this.o);
            }
        }

        public virtual List<object> FieldValues
        {
            get
            {
                if (o == null) return null;
                List<object> values = new List<object>();
                @class.EachField(fieldInfo => values.Add(fieldInfo.GetValue(o)));
                return values;
            }
        }

        public virtual object FieldValue(string fieldName)
        {
            FieldInfo field = @class.GetField(fieldName);
            if (field == null) throw new BricksException("Could not find field " + fieldName + " in type");
            return field.GetValue(o);
        }

        public virtual bool HasField(string fieldName)
        {
            return @class.GetField(fieldName) != null;
        }

        public virtual Class Class
        {
            get { return @class; }
        }

        public virtual object Invoke(MethodInfo methodInfo, object[] arguments)
        {
            if (o == null) throw new NullReferenceException("Trying to invoke method on a null object");
            try
            {
                return methodInfo.Invoke(o, arguments);
            }
            catch (TargetInvocationException e)
            {
                throw new BricksException(string.Format("Error invoking {0}.{1}", o.GetType().Name, methodInfo.Name), e.InnerException);
            }
        }

        public virtual void Visit(ObjectVisitor visitor)
        {
            fields.ForEach(field => visitor.Accept(field));
        }

        public virtual ComparisonStatus Compare(ReflectedObject other) {
            return null; 
        }
        
        public static void IgnoreTypeForComparison(Type type)
        {
            ignoredType = type;
        }

        public virtual object O
        {
            get { return o; }
        }

        public virtual Fields Fields
        {
            get { return fields; }
        }

        public void EachField(Class.FieldDelegate operation)
        {
            @class.EachField(operation);
        }

        public void SetValue(string fieldName, object value)
        {
            FieldInfo field = @class.GetField(fieldName);
            field.SetValue(o, value);
        }
    }
}