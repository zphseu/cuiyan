using System;
using System.ComponentModel;
using System.Globalization;
using System.Text;

namespace FepManager.PropGridHelper
{
    class StringListAttribute : Attribute
    {
        public String[] lists;
        public StringListAttribute(String[] lists)
        {
            this.lists = lists;   
        }

        public String[] Lists
        {
            get { return lists; }
            set { lists = value; }
        }
    }

    class StringListConverter : TypeConverter
    {
        public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
        {
            return true;
        }

        public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
        {
            return true;
        }

        public override StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
        {
            StringListAttribute lst = (StringListAttribute)context.PropertyDescriptor.Attributes[typeof(StringListAttribute)];
            StandardValuesCollection vals = new TypeConverter.StandardValuesCollection(lst.lists);
            return vals;
        }

        public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
        {
            return true;
        }
    }

    class LongListAttribute : Attribute
    {
        public Int64[] lists;
        public LongListAttribute(Int64[] lists)
        {
            this.lists = lists;
        }

        public Int64[] Lists
        {
            get { return lists; }
            set { lists = value; }
        }

    }

    class LongListConverter : TypeConverter
    {
        public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
        {
            return true;
        }

        public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
        {
            return true;
        }

        public override StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
        {
            LongListAttribute lst = (LongListAttribute)context.PropertyDescriptor.Attributes[typeof(LongListAttribute)];
            StandardValuesCollection vals = new TypeConverter.StandardValuesCollection(lst.lists);
            return vals;
        }

        public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
        {
            return true;
        }
        
        public override bool CanConvertFrom(ITypeDescriptorContext context,System.Type sourceType)
        {
            if (sourceType == typeof(string))
                return true;

            return base.CanConvertFrom(context, sourceType);
        }

        public override object ConvertFrom(ITypeDescriptorContext context, CultureInfo culture, object value)
        {
            if (value is string)
                return Convert.ToInt64(value);
            return base.ConvertFrom(context, culture, value);
        }
    }
}
