using System;
using System.Windows.Automation;
using Bricks.Core;

namespace Core.Mappings
{
    public class ControlDictionaryItem
    {
        private readonly Type testControlType;
        private readonly ControlType controlType;
        private readonly string className;
        private readonly bool identifiedByClassName;
        private readonly bool isPrimary;
        private readonly bool isExcluded;
        private readonly string frameworkId;
        private readonly bool hasPrimaryChildren;
        private bool isIdentifiedByName;

        public ControlDictionaryItem(Type testControlType, ControlType controlType, string className, bool identifiedByClassName, bool isPrimary,
                                     bool isExcluded, string frameworkId, bool hasPrimaryChildren)
        {
            this.testControlType = testControlType;
            this.controlType = controlType;
            this.className = className;
            this.identifiedByClassName = identifiedByClassName;
            this.isPrimary = isPrimary;
            this.isExcluded = isExcluded;
            this.frameworkId = frameworkId;
            this.hasPrimaryChildren = hasPrimaryChildren;
        }

        public static ControlDictionaryItem Primary(Type testControlType, ControlType controlType)
        {
            return new ControlDictionaryItem(testControlType, controlType, string.Empty, false, true, false, null, false);
        }

        public static ControlDictionaryItem Primary(Type testControlType, ControlType controlType, bool hasPrimaryChildren)
        {
            return new ControlDictionaryItem(testControlType, controlType, string.Empty, false, true, false, null, hasPrimaryChildren);
        }

        private static ControlDictionaryItem Primary(Type testControlType, ControlType controlType, string frameworkId)
        {
            return new ControlDictionaryItem(testControlType, controlType, string.Empty, false, true, false, frameworkId, false);
        }

        public static ControlDictionaryItem WinFormPrimary(Type testControlType, ControlType controlType)
        {
            return Primary(testControlType, controlType, Constants.WinFormFrameworkId);
        }

        public static ControlDictionaryItem WPFPrimary(Type testControlType, ControlType controlType)
        {
            return Primary(testControlType, controlType, Constants.WPFFrameworkId);
        }

        public static ControlDictionaryItem Win32Primary(Type testControlType, ControlType controlType)
        {
            return Primary(testControlType, controlType, Constants.Win32FrameworkId);
        }

        private static ControlDictionaryItem Secondary(Type testControlType, ControlType controlType, string frameworkId)
        {
            return new ControlDictionaryItem(testControlType, controlType, string.Empty, false, false, false, frameworkId, false);
        }

        public static ControlDictionaryItem Secondary(Type testControlType, ControlType controlType)
        {
            return new ControlDictionaryItem(testControlType, controlType, string.Empty, false, false, false, null, false);
        }

        public static ControlDictionaryItem Secondary(Type testControlType, ControlType controlType, bool hasPrimaryChildren)
        {
            return new ControlDictionaryItem(testControlType, controlType, string.Empty, false, false, false, null, hasPrimaryChildren);
        }

        public static ControlDictionaryItem WinFormSecondary(Type testControlType, ControlType controlType)
        {
            return Secondary(testControlType, controlType, Constants.WinFormFrameworkId);
        }

        public static ControlDictionaryItem Win32Secondary(Type testControlType, ControlType controlType)
        {
            return Secondary(testControlType, controlType, Constants.Win32FrameworkId);
        }

        public static ControlDictionaryItem WPFSecondary(Type testControlType, ControlType controlType)
        {
            return Secondary(testControlType, controlType, Constants.WPFFrameworkId);
        }

        public virtual bool IsPrimary
        {
            get { return isPrimary; }
        }

        public virtual Type TestControlType
        {
            get { return testControlType; }
        }

        public virtual string FrameworkId
        {
            get { return frameworkId; }
        }

        public virtual ControlType ControlType
        {
            get { return controlType; }
        }

        public virtual string ClassName
        {
            get { return className; }
        }

        public virtual bool IsExcluded
        {
            get { return isExcluded; }
        }

        public virtual bool IsIdentifiedByClassName
        {
            get { return identifiedByClassName; }
        }

        public virtual bool HasPrimaryChildren
        {
            get { return hasPrimaryChildren; }
        }

        public virtual bool OfFramework(string id)
        {
            return S.IsEmpty(id) || id.Equals(id);
        }

        public virtual bool IsIdentifiedByName
        {
            set { isIdentifiedByName = value; }
            get { return isIdentifiedByName; }
        }
    }
}