using System;
using System.Collections;
using System.Reflection;

namespace Bricks.RuntimeFramework
{
    /// <summary>
    /// Represents a Type in .NET. It uses reflection to provide access to Type information.
    /// </summary>
    public class Class : CodeMember
    {
        private const string StartStringOfProxyClass = "CProxyType";
        private const BindingFlags bindingFlag = BindingFlags.Public | BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.DeclaredOnly |
                                                 BindingFlags.IgnoreCase;
        private MethodInfos nonVirtualMethodInfos;

        public delegate void FieldDelegate(FieldInfo fieldInfo);

        public delegate void ConstructorDelegate(ConstructorInfo constructorInfo);

        private Classes classes;
        private Type ignoredType;

        public Class(Type type) : base(type){}

        private Type type
        {
            get { return (Type) memberInfo; }
        }

        private Classes classHierarchy
        {
            get
            {
                if (classes != null) return classes;

                classes = new Classes(this);
                Type currentType = type.BaseType;
                while (typeof (object) != currentType && !currentType.Equals(ignoredType))
                {
                    classes.Add(new Class(currentType));
                    currentType = currentType.BaseType;
                }
                return classes;
            }
        }

        /// <summary>
        /// Providers a list of all the Non-virtual methods and properties. MethodInfos would get created first time they are accessed.
        /// </summary>
        public virtual MethodInfos NonVirtuals
        {
            get
            {
                if (nonVirtualMethodInfos == null)
                {
                    nonVirtualMethodInfos = new MethodInfos();
                    MethodInfo[] methodInfos = type.GetMethods(bindingFlag);
                    foreach (MethodInfo methodInfo in methodInfos)
                    {
                        if (methodInfo.IsPrivate || !methodInfo.DeclaringType.Equals(type) || methodInfo.Name.StartsWith("<")) continue;
                        if (!methodInfo.IsVirtual || methodInfo.IsFinal) nonVirtualMethodInfos.Add(methodInfo);
                    }
                }
                return nonVirtualMethodInfos;
            }
        }

        //Limitation is that every object needs a default constructor.
        public virtual object New(params object[] arguments)
        {
            ArrayList types = new ArrayList();
            ConstructorInfo constructor;
            if (arguments.Length != 0)
            {
                foreach (object o in arguments)
                    types.Add(o.GetType());
                constructor = type.GetConstructor(bindingFlag, null, (Type[]) types.ToArray(typeof (Type)), null);
            }
            else
            {
                constructor = type.GetConstructor(bindingFlag, null, new Type[] {}, null);
            }
            if (constructor == null) throw new BricksException("No constructor found with matching arguments found in type " + type.FullName);
            return constructor.Invoke(arguments);
        }

        public virtual void EachField(FieldDelegate fieldDelegate)
        {
            foreach (Class @class in classHierarchy)
            {
                foreach (FieldInfo field in @class.type.GetFields(bindingFlag))
                    fieldDelegate(field);
            }
        }

        public virtual void EachConstructor(ConstructorDelegate constructorDelegate)
        {
            foreach (ConstructorInfo constructor in type.GetConstructors(bindingFlag))
                constructorDelegate.Invoke(constructor);
        }

        public static bool IsProxy(object o)
        {
            return o.GetType().Name.StartsWith(StartStringOfProxyClass);
        }

        public virtual FieldInfo GetField(string fieldName)
        {
            FieldInfo field = type.GetField(fieldName, bindingFlag);
            if (field != null) return field;
            Class baseClass = BaseClass;
            if (baseClass != null) return baseClass.GetField(fieldName);
            return null;
        }

        private Class BaseClass
        {
            get
            {
                if (type.BaseType.Equals(typeof (object))) return null;
                return new Class(type.BaseType);
            }
        }

        public virtual string Name
        {
            get { return type.Name; }
        }

        public virtual Classes SubClassesInAssembly()
        {
            Types types = new Types(type.Assembly.GetTypes());
            return new Classes(types.FindAll(delegate(Type item)
                                                 {
                                                     if (!item.IsClass || type.Equals(item)) return false;
                                                     return type.IsAssignableFrom(item);
                                                 }));
        }

        public override string ToString()
        {
            return type.FullName;
        }

        public virtual bool IsProperty(string name)
        {
            return type.GetProperty(name) != null;
        }

        public virtual Method GetMethod(string methodName)
        {
            foreach (Class @class in classHierarchy)
            {
                MethodInfo info = @class.type.GetMethod(methodName, bindingFlag);
                if (info != null) return new Method(info);
            }
            return null;
        }

        public virtual Property GetProperty(string propertyName)
        {
            foreach (Class @class in classHierarchy)
            {
                PropertyInfo info = @class.type.GetProperty(propertyName, bindingFlag);
                if (info != null) return new Property(info);
            }
            return null;
        }

        public virtual void IgnoreClass(Type ignoredType)
        {
            this.ignoredType = ignoredType;
        }
    }
}