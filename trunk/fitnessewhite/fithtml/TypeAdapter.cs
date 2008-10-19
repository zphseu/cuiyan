// Copyright (c) 2002 Cunningham & Cunningham, Inc.
// Released under the terms of the GNU General Public License version 2 or later.

using System;
using System.Reflection;

namespace fit
{
    public class TypeAdapter
    {
        public object target;
        public Fixture fixture;
        public FieldInfo field;
        public MethodInfo method;
        public Type type;

        //cycy for fithtmlwhite to add {{{
        public TypeAdapter()
        {
        }

        public TypeAdapter(Type type)
        {
            this.type = type;
        }

        public virtual object Parse(string s)
        {
            return parse(s, type);
        }

        public static bool AreEqual(object o1, object o2)
        {
            if (o1 is DateTime && o2 is DateTime)
                return o1.ToString().Equals(o2.ToString());
            if (o1 == null)
                return o2 == null;
            if (o1 is Array)
                return new TypeAdapter().compareArrays((object[])o1, o2);
            else
                return (o1.Equals(o2));
        }
        //cycy for fithtmlwhite to add }}}

        //
        //
        //    // Factory //////////////////////////////////
        //

        public static TypeAdapter on(Fixture target, Type type)
        {
            TypeAdapter adapter = new TypeAdapter();
            adapter.fixture = target;
            adapter.target = target;
            adapter.type = type;
            return adapter;
        }

        public static TypeAdapter on(Fixture target, MethodInfo method)
        {
            TypeAdapter adapter = on(target, method.ReturnType);
            adapter.method = method;
            return adapter;
        }

        public static TypeAdapter on(Fixture target, FieldInfo field)
        {
            TypeAdapter adapter = on(target, field.FieldType);
            adapter.field = field;
            return adapter;
        }

        public object get()
        {
            if (field != null) return field.GetValue(target);
            if (method != null) return method.Invoke(target, new object[] { });
            return null;
        }

        public virtual void set(object value)
        {
            field.SetValue(target, value);
        }

        public virtual object parse(string s)
        {
            return parse(s, type);
        }

        private object parse(string s, Type t)
        {
            if (t.IsAssignableFrom(typeof(string))) return s;
            if (t.IsArray) return parseArray(s, t);

            BindingFlags flags = BindingFlags.Static | BindingFlags.FlattenHierarchy | BindingFlags.IgnoreCase | BindingFlags.Public;
            MethodInfo parseMethod = t.GetMethod("Parse", flags, null, new Type[] { typeof(string) }, null);
            if (parseMethod != null && parseMethod.ReturnType == t)
            {
                return parseMethod.Invoke(null, new object[] { s });
            }
            else
            {
                throw new ApplicationException("Can't parse " + t.FullName + " because it doesn't have a static Parse() method");
            }
        }

        private object[] parseArray(string s, Type arrayType)
        {
            string[] strings = s.Split(new char[] { ',' });
            object[] result = new object[strings.Length];
            for (int i = 0; i < strings.Length; i++)
            {
                result[i] = parse(strings[i], arrayType.GetElementType());
            }
            return result;
        }

        public virtual bool equals(object o1, object o2)
        {
            if (o1 is Array) return compareArrays((object[])o1, o2);
            else return (o1.Equals(o2));
        }

        private bool compareArrays(object[] a1, object o2)
        {
            if (!(o2 is Array)) return false;

            object[] a2 = (object[])o2;
            if (a1.Length != a2.Length) return false;
            for (int i = 0; i < a1.Length; i++)
            {
                if (!(a1[i].Equals(a2[i]))) return false;
            }
            return true;
        }

        //    // Subclasses ///////////////////////////////
        //
        //    class ArrayAdapter 
        //    {
        //      Type componentType;
        //      TypeAdapter componentAdapter;
        //
        //      void init(Fixture target, Type type) 
        //      {
        //        super.init(target, type);
        //        componentType = type.getComponentType();
        //        componentAdapter = on(target, componentType);
        //      }
        //
        //    public object parse(string s) 
        //    {
        //      StringTokenizer t = new StringTokenizer(s, ",");
        //      object array = Array.newInstance(componentType, t.countTokens());
        //      for (int i=0; t.hasMoreTokens(); i++) 
        //      {
        //        Array.set(array, i, componentAdapter.parse(t.nextToken()));
        //      }
        //      return array;
        //    }
        //
        //    public string toString(object o) 
        //    {
        //      int length = Array.getLength(o);
        //      StringBuffer b = new StringBuffer(5*length);
        //      for (int i=0; i<length; i++) 
        //      {
        //        b.append(componentAdapter.toString(Array.get(o, i)));
        //        if (i < (length-1)) 
        //        {
        //          b.append(',');
        //        }
        //      }
        //      return b.toString();
        //    }
        //
        //    public bool equals(object a, object b) 
        //    {
        //      int length = Array.getLength(a);
        //      if (length != Array.getLength(b)) return false;
        //      for (int i=0; i<length; i++) 
        //      {
        //        if (!componentAdapter.equals(Array.get(a,i), Array.get(b,i))) return false;
        //      }
        //      return true;
        //    }
        //  }
    }
}