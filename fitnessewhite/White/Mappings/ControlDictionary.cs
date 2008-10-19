using System;
using System.Collections.Generic;
using System.Windows.Automation;
using Bricks.Core;
using Bricks.RuntimeFramework;
using Core.UIItems;
using Core.UIItems.ListBoxItems;
using Core.UIItems.MenuItems;
using Core.UIItems.PropertyGridItems;
using Core.UIItems.Scrolling;
using Core.UIItems.TabItems;
using Core.UIItems.TableItems;
using Core.UIItems.TreeItems;
using Core.UIItems.WindowStripControls;

namespace Core.Mappings
{
    public class ControlDictionary
    {
        public static ControlDictionary Instance = new ControlDictionary();
        private readonly List<ControlDictionaryItem> items = new List<ControlDictionaryItem>();
        private readonly Types editableControls = new Types();

        private ControlDictionary()
        {
            items.Add(ControlDictionaryItem.Win32Primary(typeof (TextBox), ControlType.Edit));
            items.Add(ControlDictionaryItem.WPFPrimary(typeof (TextBox), ControlType.Edit));
            items.Add(ControlDictionaryItem.WinFormPrimary(typeof (WinFormTextBox), ControlType.Edit));

            items.Add(ControlDictionaryItem.WinFormPrimary(typeof (WinFormSlider), ControlType.Slider));
            items.Add(ControlDictionaryItem.WPFPrimary(typeof (WPFSlider), ControlType.Slider));

            items.Add(ControlDictionaryItem.Primary(typeof (Button), ControlType.Button));
            items.Add(ControlDictionaryItem.Primary(typeof (CheckBox), ControlType.CheckBox));
            items.Add(ControlDictionaryItem.Primary(typeof (ListBox), ControlType.List));
            items.Add(ControlDictionaryItem.Primary(typeof (Hyperlink), ControlType.Hyperlink));
            items.Add(ControlDictionaryItem.Primary(typeof (Tree), ControlType.Tree));
            items.Add(ControlDictionaryItem.Primary(typeof (RadioButton), ControlType.RadioButton));
            items.Add(ControlDictionaryItem.Primary(typeof (Table), ControlType.Table));
            items.Add(ControlDictionaryItem.Primary(typeof (MultilineTextBox), ControlType.Document));
            items.Add(ControlDictionaryItem.Primary(typeof (Tab), ControlType.Tab, true));
            items.Add(ControlDictionaryItem.Primary(typeof (ListView), ControlType.DataGrid));
            items.Add(ControlDictionaryItem.Primary(typeof (ToolStrip), ControlType.ToolBar));
            items.Add(ControlDictionaryItem.Primary(typeof (MenuBar), ControlType.MenuBar));
            items.Add(ControlDictionaryItem.Primary(typeof (MenuBar), ControlType.Menu));
            items.Add(ControlDictionaryItem.Primary(typeof (ProgressBar), ControlType.ProgressBar));
            items.Add(ControlDictionaryItem.Primary(typeof (Spinner), ControlType.Spinner));
            ControlDictionaryItem dictionaryItem = ControlDictionaryItem.Primary(typeof (PropertyGrid), ControlType.Pane);
            dictionaryItem.IsIdentifiedByName = true;
            items.Add(dictionaryItem);

            items.Add(ControlDictionaryItem.WinFormPrimary(typeof (Label), ControlType.Text));
            items.Add(ControlDictionaryItem.Win32Primary(typeof (Label), ControlType.Text));
            items.Add(ControlDictionaryItem.WPFPrimary(typeof (WPFLabel), ControlType.Text));

            items.Add(ControlDictionaryItem.WPFPrimary(typeof (WPFComboBox), ControlType.ComboBox));
            items.Add(ControlDictionaryItem.Win32Primary(typeof (Win32ComboBox), ControlType.ComboBox));
            items.Add(ControlDictionaryItem.WinFormPrimary(typeof (WinFormComboBox), ControlType.ComboBox));

            items.Add(ControlDictionaryItem.Win32Primary(typeof (StatusStrip), ControlType.StatusBar));
            items.Add(ControlDictionaryItem.WinFormPrimary(typeof (StatusStrip), ControlType.StatusBar));
            items.Add(ControlDictionaryItem.WPFPrimary(typeof (WPFStatusBar), ControlType.StatusBar));
            items.Add(ControlDictionaryItem.WPFPrimary(typeof (Image), ControlType.Image));
            items.Add(ControlDictionaryItem.Win32Primary(typeof (Image), ControlType.Image));

            items.Add(ControlDictionaryItem.Secondary(typeof (TableRowHeader), ControlType.Header));
            items.Add(ControlDictionaryItem.Secondary(typeof (TabPage), ControlType.TabItem, true));
            items.Add(ControlDictionaryItem.Secondary(typeof (VScrollBar), ControlType.ScrollBar));
            items.Add(ControlDictionaryItem.Secondary(typeof (HScrollBar), ControlType.ScrollBar));
            items.Add(ControlDictionaryItem.Secondary(typeof (TableHeader), ControlType.Custom));
            items.Add(ControlDictionaryItem.Secondary(typeof (TableRow), ControlType.Custom));
            items.Add(ControlDictionaryItem.Secondary(typeof (Menu), ControlType.MenuItem));
            items.Add(ControlDictionaryItem.Secondary(typeof (ListViewRow), ControlType.DataItem));

            items.Add(ControlDictionaryItem.WinFormSecondary(typeof (Win32ListItem), ControlType.ListItem));
            items.Add(ControlDictionaryItem.Win32Secondary(typeof (Win32ListItem), ControlType.ListItem));
            items.Add(ControlDictionaryItem.WPFSecondary(typeof (WPFListItem), ControlType.ListItem));

            items.Add(ControlDictionaryItem.WinFormSecondary(typeof (Win32TreeNode), ControlType.TreeItem));
            items.Add(ControlDictionaryItem.WPFSecondary(typeof (WPFTreeNode), ControlType.TreeItem));
            items.Add(ControlDictionaryItem.Win32Secondary(typeof (Win32TreeNode), ControlType.TreeItem));

            items.Add(new ControlDictionaryItem(typeof (DateTimePicker), ControlType.Pane, "SysDateTimePick32", true, true, false, null, false));
            items.Add(new ControlDictionaryItem(typeof (GroupBox), ControlType.Group, string.Empty, false, true, false, null, true));
            items.Add(new ControlDictionaryItem(null, ControlType.TitleBar, string.Empty, false, false, true, null, false));
            items.Add(new ControlDictionaryItem(null, ControlType.Pane, string.Empty, false, false, false, null, true));

            editableControls.Add(typeof (TextBox));
            editableControls.Add(typeof (CheckBox));
            editableControls.Add(typeof (RadioButton));
            editableControls.Add(typeof (ListControl));
        }

        public virtual ControlType[] TableControls
        {
            get { return new ControlType[] {ControlType.Header, ControlType.Custom}; }
        }

        public virtual bool HasPrimaryChildren(ControlType controlType)
        {
            if (controlType.Equals(ControlType.Custom)) return true;
            ControlDictionaryItem item =
                items.Find(delegate(ControlDictionaryItem obj) { return controlType.Equals(obj.ControlType) && !obj.IsIdentifiedByClassName && !obj.IsIdentifiedByName; });
            if (item == null) throw new ControlDictionaryException("Could not find control of type " + controlType.LocalizedControlType);
            return item.HasPrimaryChildren;
        }

        public virtual ControlType GetControlType(Type type)
        {
            ControlDictionaryItem foundItem =
                items.Find(delegate(ControlDictionaryItem controlDictionaryItem) { return type.IsAssignableFrom(controlDictionaryItem.TestControlType); });
            return foundItem.ControlType;
        }

        public virtual Type GetTestControlType(ControlType controlType, string frameWorkId)
        {
            ControlDictionaryItem dictionaryItem = items.Find(delegate(ControlDictionaryItem controlDictionaryItem)
                                                                  {
                                                                      string itemFrameworkId = controlDictionaryItem.FrameworkId;
                                                                      bool controlTypeMatched = controlDictionaryItem.ControlType.Equals(controlType);

                                                                      if (
                                                                          (!(string.IsNullOrEmpty(frameWorkId) &&
                                                                             Equals(controlDictionaryItem.FrameworkId, Constants.Win32FrameworkId))) &&
                                                                          itemFrameworkId != null)
                                                                          controlTypeMatched &= itemFrameworkId.Equals(frameWorkId);
                                                                      return controlTypeMatched;
                                                                  });
            if (dictionaryItem == null)
            {
                throw new ControlDictionaryException(string.Format("Could not find TestControl for ControlType={0} and FrameworkId:{1}",
                                                                   controlType.LocalizedControlType, frameWorkId));
            }
            return dictionaryItem.TestControlType;
        }

        public virtual Type GetTestControlType(string className)
        {
            if (S.IsEmpty(className)) return null;
            ControlDictionaryItem dictionaryItem =
                items.Find(delegate(ControlDictionaryItem controlDictionaryItem) { return !string.IsNullOrEmpty(controlDictionaryItem.ClassName) && className.Contains(controlDictionaryItem.ClassName); });
            if (dictionaryItem == null) return null;
            return dictionaryItem.TestControlType;
        }

        public virtual bool IsPrimaryControl(ControlType controlType, string className, string name)
        {
            return
                items.Exists(
                    delegate(ControlDictionaryItem controlDictionaryItem)
                        {
                            return (controlDictionaryItem.IsPrimary && controlDictionaryItem.ControlType.Equals(controlType) &&
                                    !controlDictionaryItem.IsIdentifiedByClassName && !controlDictionaryItem.IsIdentifiedByName) ||
                                   (S.IsNotEmpty(className) && className.Contains(controlDictionaryItem.ClassName) &&
                                    controlDictionaryItem.IsIdentifiedByClassName) || (S.IsNotEmpty(name) && name.Equals("PropertyGrid") && controlDictionaryItem.IsIdentifiedByName);
                        });
        }

        public virtual bool IsExcluded(ControlType controlType)
        {
            return
                items.Exists(
                    delegate(ControlDictionaryItem controlDictionaryItem) { return controlDictionaryItem.ControlType.Equals(controlType) && controlDictionaryItem.IsExcluded; });
        }

        public virtual bool IsControlTypeSupported(ControlType controlType)
        {
            foreach (ControlDictionaryItem controlDictionaryItem in items)
                if (controlDictionaryItem.ControlType.Equals(controlType)) return true;
            return false;
        }

        public virtual List<ControlType> PrimaryControlTypes(string frameworkId)
        {
            List<ControlType> controlTypes = new List<ControlType>();
            foreach (ControlDictionaryItem controlDictionaryItem in items)
            {
                if (controlDictionaryItem.OfFramework(frameworkId) && controlDictionaryItem.IsPrimary &&
                    !controlTypes.Contains(controlDictionaryItem.ControlType))
                    controlTypes.Add(controlDictionaryItem.ControlType);
            }
            return controlTypes;
        }

        public virtual bool IsEditable(UIItem uiItem)
        {
            return editableControls.IsAssignableFrom(uiItem.GetType());
        }

        public virtual Type GetTestType(AutomationElement automationElement)
        {
            Type type = GetTestControlType(automationElement.Current.ClassName);
            if (type == null) type = GetTestControlType(automationElement.Current.ControlType, automationElement.Current.FrameworkId);
            if (type == null && "PropertyGrid".Equals(automationElement.Current.Name) && ControlType.Pane.Equals(automationElement.Current.ControlType))
                type = typeof (PropertyGrid);
            return type;
        }
    }
}