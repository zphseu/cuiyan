using System;
using System.Windows.Automation;
using Bricks.RuntimeFramework;
using Core.Mappings;
using Core.UIItems;
using Core.UIItems.Actions;

namespace Core.Factory
{
    public class DictionaryMappedItemFactory : UIItemFactory
    {
        public virtual IUIItem Create(AutomationElement automationElement, ActionListener actionListener)
        {
            if (automationElement == null) return null;
            return Create(automationElement, ControlDictionary.Instance.GetTestType(automationElement), actionListener);
        }

        public virtual IUIItem Create(AutomationElement automationElement, ActionListener actionListener, Type customItemType)
        {
            if (automationElement == null) return null;
            if (customItemType != null) return Create(automationElement, customItemType, actionListener);
            return Create(automationElement, actionListener);
        }

        private IUIItem Create(AutomationElement automationElement, Type itemType, ActionListener actionListener)
        {
            if (itemType == null) return null;
            return (IUIItem) new Class(itemType).New(automationElement, actionListener);
        }
    }
}