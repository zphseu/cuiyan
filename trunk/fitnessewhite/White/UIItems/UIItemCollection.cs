using System;
using System.Collections;
using System.Windows.Automation;
using Bricks.RuntimeFramework;
using Core.Factory;
using Core.Logging;
using Core.Mappings;
using Core.UIItems.Actions;

namespace Core.UIItems
{
    public class UIItemCollection : BricksCollection<IUIItem>
    {
        private static readonly DictionaryMappedItemFactory dictionaryMappedItemFactory = new DictionaryMappedItemFactory();

        public UIItemCollection(params UIItem[] uiItems)
        {
            AddRange(uiItems);
        }

        public UIItemCollection(IEnumerable entities) : base(entities) {}

        public UIItemCollection(AutomationElement[] automationElements, ActionListener actionListener)
            : this(automationElements, dictionaryMappedItemFactory, actionListener) {}

        public UIItemCollection(IEnumerable automationElements, ActionListener actionListener)
            : this(automationElements, dictionaryMappedItemFactory, actionListener) {}

        public UIItemCollection(IEnumerable automationElements, UIItemFactory uiItemFactory, ActionListener actionListener)
        {
            foreach (AutomationElement automationElement in automationElements)
            {
                IUIItem uiItem = uiItemFactory.Create(automationElement, actionListener);
                if (uiItem != null) Add(uiItem);
            }
        }

        public UIItemCollection(IEnumerable automationElements, ActionListener actionListener, Type customItemType)
        {
            foreach (AutomationElement automationElement in automationElements)
            {
                try
                {
                    if (!ControlDictionary.Instance.IsPrimaryControl(automationElement.Current.ControlType, automationElement.Current.ClassName, null)) continue;
                    IUIItem uiItem = dictionaryMappedItemFactory.Create(automationElement, actionListener, customItemType);
                    if (uiItem != null) Add(uiItem);
                }
                catch (ControlDictionaryException)
                {
                    WhiteLogger.Instance.Warn("Couldn't create UIItem for AutomationElement, "+ UIItem.ToString(automationElement));
                }
            }
        }
    }
}