using System;
using System.Reflection;
using System.Windows.Automation;
using Castle.Core.Interceptor;
using Core.Factory;
using Core.Interceptors;
using Core.Sessions;
using Core.UIItems.Actions;
using Core.UIItems.Container;
using Core.UIItems.Custom;
using Core.UIItems.Finders;

namespace Core.UIItems
{
    //BUG: Allow finding more than one item, also ability to do this within a container
    //TODO: Dont let people compile code is they are trying to find UIItem which are secondary or window
    public class UIItemContainer : UIItem, IUIItemContainer
    {
        protected readonly CurrentContainerItemFactory currentContainerItemFactory;
        protected WindowSession windowSession;

        protected UIItemContainer() {}

        public UIItemContainer(AutomationElement automationElement, ActionListener actionListener, InitializeOption initializeOption,
                               WindowSession windowSession) : base(automationElement, actionListener)
        {
            this.windowSession = windowSession;
            currentContainerItemFactory = new CurrentContainerItemFactory(factory, initializeOption, automationElement, ChildrenActionListener);
        }

        /// <summary>
        /// Finds UIItem which matches specified type. Useful for non managed applications where controls are not identified by AutomationId, like in 
        /// Managed applications. In case of multiple items of this type the first one found would be returned which cannot be guaranteed to be the same 
        /// across multiple invocations.
        /// </summary>
        /// <typeparam name="T">UIItem type e.g. Button, TextBox</typeparam>
        /// <returns>First item of supplied type</returns>
        public virtual T Get<T>() where T : UIItem
        {
            return Get<T>(SearchCriteria.All);
        }

        /// <summary>
        /// Finds UIItem which matches specified type and identification. 
        /// In case of multiple items of this type the first one found would be returned which cannot be guaranteed to be the same across multiple 
        /// invocations. For managed applications this is name given to controls in the application code.
        /// For unmanaged applications this is text of the control or label next to it if it doesn't have well defined text.
        /// e.g. TextBox doesn't have any predefined text of its own as it can be changed at runtime by user, hence is identified by the label next to it.
        /// If there is no label then Get<T> or Get<T>(SearchCriteria) method can be used.
        /// </summary>
        /// <typeparam name="T">UIItem type</typeparam>
        /// <param name="primaryIdentification">For managed application this is the name provided in application code and unmanaged application this is 
        /// the text or label next to it based identification</param>
        /// <returns>First item of supplied type and identification</returns>
        public virtual T Get<T>(string primaryIdentification) where T : UIItem
        {
            return Get<T>(SearchCriteria.ByAutomationId(primaryIdentification));
        }

        /// <summary>
        /// Finds UIItem which matches specified type and searchCriteria. Type supplied need not be supplied again in SearchCondition.
        /// e.g. in Get<Button>(SearchCriteria.ByAutomationId("OK").ByControlType(typeof(Button)).Indexed(1) the ByControlType(typeof(Button)) part 
        /// is redundant. Look at documentation of SearchCriteria for details on it.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="searchCriteria">Criteria provided to search UIItem</param>
        /// <returns>First items matching the type and criteria</returns>
        public virtual T Get<T>(SearchCriteria searchCriteria) where T : UIItem
        {
            return (T) Get(searchCriteria.AndControlType(typeof (T)));
        }

        /// <summary>
        /// Finds UIItem which matches specified type and searchCriteria. Look at documentation of SearchCriteria for details on it.
        /// </summary>
        /// <param name="searchCriteria">Criteria provided to search UIItem</param>
        /// <returns>First items matching the criteria</returns>
        public virtual IUIItem Get(SearchCriteria searchCriteria)
        {
            try
            {
                IUIItem uiItem = currentContainerItemFactory.Find(searchCriteria, windowSession);
                CustomUIItem customUIItem = uiItem as CustomUIItem;
                if (customUIItem != null) SetContainer(customUIItem);
                return uiItem;
            }
            catch (Exception e)
            {
                throw new WhiteException(Debug.Details(automationElement), e);
            }
        }

        private void SetContainer(CustomUIItem customUIItemProxy)
        {
            FieldInfo interceptorField = customUIItemProxy.GetType().GetField("__interceptors",
                                                                              BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance);
            IInterceptor[] interceptors = (IInterceptor[]) interceptorField.GetValue(customUIItemProxy);
            CustomUIItem realCustomUIItem = (CustomUIItem) ((CoreInterceptor) interceptors[0]).Context.UiItem;
            realCustomUIItem.SetContainer(new UIItemContainer(customUIItemProxy.AutomationElement, ActionListener, InitializeOption.NoCache, windowSession));
        }

        /// <summary>
        /// Applicable only if CacheMode is used. This is for internal purpose of white and should not be used, as caching by itself is not supported
        /// </summary>
        /// <param name="option"></param>
        public virtual void ReInitialize(InitializeOption option)
        {
            currentContainerItemFactory.ReInitialize(option);
        }

        protected virtual ActionListener ChildrenActionListener
        {
            get { return actionListener; }
        }

        //BUG: Try this method out with all windows on the desktop and see if it works
        public virtual UIItemCollection Items
        {
            get { return currentContainerItemFactory.FindAll(); }
        }

        public virtual IUIItem[] GetMultiple(SearchCriteria criteria)
        {
            return currentContainerItemFactory.FindAll(criteria).ToArray();
        }
    }
}