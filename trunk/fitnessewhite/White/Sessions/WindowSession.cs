using System;
using System.Windows;
using System.Windows.Automation;
using Bricks.DynamicProxy;
using Core.Factory;
using Core.Interceptors;
using Core.Logging;
using Core.ScreenMap;
using Core.UIItems;
using Core.UIItems.Actions;
using Core.UIItems.Container;
using Core.UIItems.Finders;
using Window=Core.UIItems.WindowItems.Window;

namespace Core.Sessions
{
    public class WindowSession : IDisposable
    {
        private readonly ApplicationSession applicationSession;
        private readonly WindowItemsMap windowItemsMap;

        public WindowSession(ApplicationSession applicationSession, InitializeOption initializeOption)
        {
            this.applicationSession = applicationSession;
            windowItemsMap = WindowItemsMap.Create(initializeOption, C.UnlikelyWindowPosition);
            if (windowItemsMap.LoadedFromFile) initializeOption.NonCached();
        }

        protected WindowSession() {}

        public virtual WindowSession ModalWindowSession(InitializeOption modalInitializeOption)
        {
            return applicationSession.WindowSession(modalInitializeOption);
        }

        public virtual IUIItem Get(ContainerItemFactory containerItemFactory, SearchCriteria searchCriteria, ActionListener actionListener)
        {
            Point location = windowItemsMap.GetItemLocation(searchCriteria);
            WhiteLogger.Instance.Debug("Finding UIItem based on criteria: " + searchCriteria);
            if (location.Equals(C.UnlikelyWindowPosition))
            {
                WhiteLogger.Instance.Debug("Could not find based on position, finding using search");
                return Create(containerItemFactory, searchCriteria, actionListener);
            }
            
            AutomationElement automationElement = AutomationElement.FromPoint(location);
            WhiteLogger.Instance.Debug("Found UIItem based on position");
            if (searchCriteria.AppliesTo(automationElement))
            {
                IUIItem item = new DictionaryMappedItemFactory().Create(automationElement, actionListener);
                return (IUIItem) DynamicProxyGenerator.Instance.CreateProxy(new CoreInterceptor(item, actionListener), item.GetType());
            }

            WhiteLogger.Instance.Debug("UIItem changed its position, find using search");
            return Create(containerItemFactory, searchCriteria, actionListener);
        }

        private IUIItem Create(ContainerItemFactory containerItemFactory, SearchCriteria searchCriteria, ActionListener actionListener)
        {
            IUIItem item = containerItemFactory.Get(searchCriteria, actionListener);
            if (item == null) return null;
            windowItemsMap.Add(item.Location, searchCriteria);
            return item;
        }

        public virtual void Dispose()
        {
            windowItemsMap.Save();
        }

        public virtual void Register(Window window)
        {
            window.Focus();
            windowItemsMap.CurrentWindowPosition = window.Location;
        }
    }
}