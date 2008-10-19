using System.Windows;
using System.Windows.Automation;
using Bricks.Core;
using Core.AutomationElementSearch;
using Core.Configuration;
using Core.UIItems;
using Core.UIItems.Actions;
using Core.UIItems.Finders;
using Core.UIItems.MenuItems;
using Core.UIItems.WindowItems;

namespace Core.Factory
{
    public class PrimaryUIItemFactory : ChildWindowFactory
    {
        private readonly DictionaryMappedItemFactory dictionaryMappedItemFactory = new DictionaryMappedItemFactory();

        public PrimaryUIItemFactory(AutomationElementFinder finder) : base(finder) {}

        public virtual ToolTip ToolTip
        {
            get
            {
                Clock clock = new Clock(CoreAppXmlConfiguration.Instance.TooltipWaitTime);
                Clock.Do perform = delegate { return finder.Child(AutomationSearchCondition.ByControlType(ControlType.ToolTip)); };
                Clock.Matched matched = delegate(object obj) { return obj != null; };
                Clock.Expired expired = delegate { throw new UIItemSearchException("Could not find ToolTip"); };
                AutomationElement element = (AutomationElement) clock.Perform(perform, matched, expired);
                return new ToolTip(element, null);
            }
        }

        public virtual TitleBar GetTitleBar(ActionListener actionListener)
        {
            AutomationElement titleElement = finder.Child(AutomationSearchCondition.ByControlType(ControlType.TitleBar));
            if (titleElement == null) return null;
            return new TitleBar(titleElement, actionListener);
        }

        public virtual PopUpMenu WPFPopupMenu(ActionListener actionListener)
        {
            try
            {
                AutomationSearchCondition[] searchConditions =
                    new AutomationSearchCondition[]
                        {AutomationSearchCondition.ByControlType(ControlType.Window), AutomationSearchCondition.ByControlType(ControlType.Menu)};
                PopUpMenu popUpMenu;
                TryGetPopupMenu(searchConditions, actionListener, out popUpMenu);
                return popUpMenu;
            }
            catch (AutomationElementSearchException)
            {
                return null;
            }
        }

        public virtual bool TryGetPopupMenu(ActionListener actionListener, out PopUpMenu popUpMenu)
        {
            AutomationSearchCondition[] searchConditions =
                new AutomationSearchCondition[] {AutomationSearchCondition.ByControlType(ControlType.Menu).OfName("DropDown")};
            return TryGetPopupMenu(searchConditions, actionListener, out popUpMenu);
        }

        private bool TryGetPopupMenu(AutomationSearchCondition[] searchConditions, ActionListener actionListener, out PopUpMenu popUpMenu)
        {
            Clock clock = new Clock(CoreAppXmlConfiguration.Instance.PopupTimeout, 100);
            Clock.Do @do = delegate
                               {
                                   try
                                   {
                                       return finder.Child(searchConditions);
                                   }
                                   catch (AutomationElementSearchException)
                                   {
                                       return null;
                                   }
                               };
            Clock.Matched matched = delegate(object obj) { return obj != null; };
            AutomationElement element = (AutomationElement) clock.Perform(@do, matched, delegate { return null; });
            if (element == null)
            {
                popUpMenu = null;
                return false;
            }
            popUpMenu = new PopUpMenu(element, actionListener);
            return true;
        }

        public virtual IUIItem Create(SearchCriteria searchCriteria, ActionListener actionListener)
        {
            if (searchCriteria.IsIndexed)
            {
                UIItemCollection collection = CreateAll(searchCriteria, actionListener);
                return searchCriteria.IndexedItem(collection);
            }
            return dictionaryMappedItemFactory.Create(finder.Descendant(searchCriteria.AutomationCondition), actionListener, searchCriteria.CustomItemType);
        }

        public virtual UIItemCollection CreateAll(SearchCriteria searchCriteria, ActionListener actionListener)
        {
            return new UIItemCollection(finder.Descendants(searchCriteria.AutomationCondition), actionListener, searchCriteria.CustomItemType);
        }

        public virtual Image WinFormImage(string primaryIdentification, ActionListener actionListener)
        {
            AutomationElement element = finder.Descendant(SearchCriteria.ByAutomationId(primaryIdentification).AutomationCondition);
            return new Image(element, actionListener);
        }

        public virtual UIItemCollection ItemsWithin(Rect bounds, ActionListener actionListener)
        {
            UIItemCollection collection = new UIItemCollection();
            AutomationElementCollection descendants = finder.Descendants(AutomationSearchCondition.All);
            foreach (AutomationElement automationElement in descendants)
            {
                if (!bounds.Contains(automationElement.Current.BoundingRectangle)) continue;
                
                DictionaryMappedItemFactory factory = new DictionaryMappedItemFactory();
                collection.Add(factory.Create(automationElement, actionListener));
            }
            return collection;
        }
    }
}