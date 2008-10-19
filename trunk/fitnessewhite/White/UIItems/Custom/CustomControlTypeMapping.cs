using System;
using System.Collections.Generic;
using System.Windows.Automation;
using Bricks.RuntimeFramework;

namespace Core.UIItems.Custom
{
    public class CustomControlTypeMapping
    {
        private static readonly Dictionary<CustomUIItemType, ControlType> mappings = new Dictionary<CustomUIItemType, ControlType>();

        static CustomControlTypeMapping()
        {
            mappings[CustomUIItemType.Pane] = System.Windows.Automation.ControlType.Pane;
            mappings[CustomUIItemType.Custom] = System.Windows.Automation.ControlType.Custom;
            mappings[CustomUIItemType.Group] = System.Windows.Automation.ControlType.Group;
            mappings[CustomUIItemType.Window] = System.Windows.Automation.ControlType.Window;
        }

        public static ControlType ControlType(CustomUIItemType customUIItemType)
        {
            return mappings[customUIItemType];
        }

        public static ControlType ControlType(Type type)
        {
            Class @class = new Class(type);
            if (!@class.HasAttribute(typeof (ControlTypeMappingAttribute)))
                throw new CustomUIItemException("ControlTypeMappingAttribute needs to be defined for this type: " + type.FullName);
            ControlTypeMappingAttribute controlTypeMappingAttribute = @class.Attribute<ControlTypeMappingAttribute>();
            return ControlType(controlTypeMappingAttribute.CustomUIItemType);
        }
    }
}