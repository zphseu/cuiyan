using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;

namespace Bricks.RuntimeFramework
{
    public class Fields : List<Field>
    {
        public Fields(object o)
        {
            if(!Field.IsPrimitive(o.GetType()))
            {
                foreach (FieldInfo fieldInfo in o.GetType().GetFields(BindingFlags.GetField | BindingFlags.NonPublic | BindingFlags.Instance))
                {
                    Add(new Field(fieldInfo, o));
                }    
            }
        }

        public Field this[string fieldName]
        {
            get
            {
                foreach(Field field in this)
                {
                    if(field.Name == fieldName)
                    {
                        return field;
                    }
                    
                }
                return null;
            }
        }
    }

    public class Field
    {
        private readonly Type type;
        private readonly string name;
        private readonly object value;

        public Field(FieldInfo fieldInfo, object o)
        {
            value = fieldInfo.GetValue(o);
            type = value == null ? fieldInfo.FieldType : value.GetType();
            name = fieldInfo.Name;
        }

        public object Value
        {
            get { return value; }
        }

        public string Name
        {
            get { return name; }
        }

        public Type Type
        {
            get { return type; }
        }

        public static bool IsPrimitive(Type type)
        {
            return type.IsPrimitive || type.IsEnum || type.Equals(typeof(string));
        }

        public bool IsPrimitive()
        {
            return IsPrimitive(type);
        }

        public ComparisonStatus Compare(Field otherField, LeafRegistry leafRegister)
        {
            if(type==otherField.Type)
            {
                if(IsPrimitive(type))
                {
                    try
                    {
                        return value.Equals(otherField.Value) ? ComparisonStatus.Clean : ComparisonStatus.Dirty;    
                    }
                    catch(NullReferenceException)
                    {
                        if (value == null && otherField.value == null)
                        {
                            return ComparisonStatus.Clean;
                        }
                        return ComparisonStatus.Dirty;
                    }   
                }
                return Value as ICollection!=null ? 
                    new CollectionComparer(Value, otherField.Value, leafRegister).Compare() 
                    : new ObjectComparer(value, otherField.Value, leafRegister).Compare();
            }
            return ComparisonStatus.Dirty;
        }
    }
}