using System;
using System.Reflection;
using System.Windows.Automation;
using System.Xml;
using Xstream.Core;

namespace Core.ScreenMap
{
    public class ControlTypeConverter : IConverter
    {
        private static readonly Type type = typeof (ControlType);
        private readonly string CONTROL_TYPE_ALIAS = "controlType";

        public virtual void Register(IMarshalContext context)
        {
            context.RegisterConverter(type, this);
            context.Alias(CONTROL_TYPE_ALIAS, type);
        }

        public virtual void ToXml(object value, FieldInfo field, XmlTextWriter xml, IMarshalContext context)
        {
            context.WriteStartTag(type, field, xml);
            xml.WriteString(((ControlType) value).Id.ToString());
            context.WriteEndTag(type, field, xml);
        }

        public virtual object FromXml(object parent, FieldInfo field, Type type, XmlNode xml, IMarshalContext context)
        {
            int lookupId = int.Parse(xml.InnerText);
            return ControlType.LookupById(lookupId);
        }
    }
}