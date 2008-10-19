using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;
using System.Windows.Automation;
using Bricks.Core;
using Bricks.RuntimeFramework;
using Core.AutomationElementSearch;
using Core.Configuration;
using Core.Factory;
using Core.InputDevices;
using Core.Logging;
using Core.Recording;
using Core.Sessions;
using Core.UIItems.Actions;
using Core.UIItems.Finders;
using Core.UIItems.MenuItems;
using Core.UIItems.Scrolling;
using Core.UIItems.TabItems;
using Core.UIItems.WindowStripControls;

namespace Core.UIItems.WindowItems
{
    //TODO support for standard dialog windows
    //TODO Read data from console window, Printer, StartMenu, DateTime, UserProfile, ControlPanel, Desktop
    //TODO Get color of controls
    //TODO Number of display monitors
    //TODO move window
    public abstract class Window : UIItemContainer, IDisposable
    {
        private static readonly Dictionary<DisplayState, WindowVisualState> windowStates = new Dictionary<DisplayState, WindowVisualState>();
        private AutomationEventHandler handler;

        public delegate bool WaitTillDelegate();

        static Window()
        {
            windowStates.Add(DisplayState.Maximized, WindowVisualState.Maximized);
            windowStates.Add(DisplayState.Minimized, WindowVisualState.Minimized);
            windowStates.Add(DisplayState.Restored, WindowVisualState.Normal);
        }

        protected Window() {}

        protected Window(AutomationElement automationElement, InitializeOption initializeOption, WindowSession windowSession)
            : base(automationElement, new NullActionListener(), initializeOption, windowSession)
        {
            InitializeWindow();
        }

        private void InitializeWindow()
        {
            WaitWhileBusy();
            Rect bounds = Desktop.Instance.Bounds;
            if (!bounds.Contains(Bounds) && (TitleBar != null && TitleBar.MinimizeButton != null))
            {
                WhiteLogger.Instance.WarnFormat(
                    @"Window with title: {0} whose dimensions are: {1}, is not contained completely on the desktop {2}. 
UI actions on window needing mouse would not work in area not falling under the desktop",
                    Title, Bounds, bounds);
            }
            windowSession.Register(this);
        }

        /// <summary>
        /// Returns a keyboard which is associated to this window. Any operation performed using the mouse would wait till the window is busy after this
        /// operation. Before any operation is performed the window is brought to focus.
        /// </summary>
        public virtual AttachedKeyboard Keyboard
        {
            get { return new AttachedKeyboard(this, keyboard); }
        }

        /// <summary>
        /// Returns a mouse which is associated to this window. Any operation performed using the mouse would wait till the window is busy after this
        /// operation. Before any operation is performed the window is brought to focus.
        /// </summary>
        public virtual AttachedMouse Mouse
        {
            get { return new AttachedMouse(this, mouse); }
        }

        protected override ActionListener ChildrenActionListener
        {
            get { return this; }
        }

        public virtual string Title
        {
            get { return TitleBar == null ? Name : TitleBar.Name; }
        }

        public virtual string ToolTip
        {
            get
            {
                ToolTip toolTip = factory.ToolTip;
                return toolTip.Text;
            }
        }

        private WindowPattern WinPattern
        {
            get { return (WindowPattern) Pattern(WindowPattern.Pattern); }
        }

        public virtual bool IsClosed
        {
            get
            {
                try
                {
                    return automationElement.Current.IsOffscreen;
                }
                catch (ElementNotAvailableException)
                {
                    return true;
                }
                catch (InvalidOperationException)
                {
                    return true;
                }
                catch(COMException)
                {
                    return true;
                }
            }
        }

        public virtual ToolStrip ToolStrip
        {
            get
            {
                Focus();
                return (ToolStrip) Get(SearchCriteria.ByControlType(ControlType.ToolBar));
            }
        }

        public virtual void Close()
        {
            WindowPattern windowPattern = (WindowPattern) Pattern(WindowPattern.Pattern);
            windowPattern.Close();
            try
            {
                WaitWhileBusy();
            }
            catch (ElementNotAvailableException) {}
        }

        public virtual ToolStrip GetToolStrip(string primaryIdentification)
        {
            ToolStrip toolStrip = (ToolStrip) Get(SearchCriteria.ByAutomationId(primaryIdentification));
            if (toolStrip == null) return null;
            toolStrip.Associate(windowSession);
            return toolStrip;
        }

        public virtual StatusStrip StatusBar(InitializeOption initializeOption)
        {
            StatusStrip statusStrip = (StatusStrip) Get(SearchCriteria.ByControlType(ControlType.StatusBar));
            statusStrip.Cached = initializeOption;
            statusStrip.Associate(windowSession);
            return statusStrip;
        }

        public virtual void WaitWhileBusy()
        {
            try
            {
                WindowPattern windowPattern = (WindowPattern) Pattern(WindowPattern.Pattern);
                if (!CoreAppXmlConfiguration.Instance.InProc &&
                    !("ConsoleWindowClass".Equals(automationElement.Current.ClassName) ||
                      windowPattern.WaitForInputIdle(CoreAppXmlConfiguration.Instance.BusyTimeout)))
                    throw new Exception("Timeout occured" + Constants.BusyMessage);

                Clock clock = new Clock(CoreAppXmlConfiguration.Instance.BusyTimeout, 0);
                clock.RunWhile(delegate { Thread.Sleep(50); },
                               delegate { return windowPattern.Current.WindowInteractionState.Equals(WindowInteractionState.NotResponding); },
                               delegate
                                   {
                                       throw new UIActionException("Window didnt come out of WaitState" + Constants.BusyMessage + " last state known was " +
                                                                   windowPattern.Current.WindowInteractionState);
                                   });
            }
            catch (Exception e)
            {
                if (!(e is InvalidOperationException || e is ElementNotAvailableException))
                    throw new UIActionException(string.Format("Window didn't respond" + Constants.BusyMessage), e);
            }
        }

        /// <summary>
        /// This should be used after RightClick on a UIItem (which can be window as well).
        /// </summary>
        /// <param name="path">Path to the menu which need to be retrieved.
        /// e.g. "Root" is one of the menus in the first level, "Level1" is inside "Root" menu and "Level2" is inside "Level1". So on.
        /// "Root", etc are text of the menu visible to user.
        /// </param>
        /// <returns></returns>
        public virtual Menu PopupMenu(params string[] path)
        {
            return Popup.Item(path);
        }

        public virtual bool HasPopup()
        {
            return Popup != null;
        }

        protected abstract PopUpMenu Popup { get; }

        public virtual MenuBar MenuBar
        {
            get { return (MenuBar) Get(SearchCriteria.ForMenuBar(MenuControlType)); }
        }

        public virtual List<MenuBar> MenuBars
        {
            get { return new BricksCollection<MenuBar>(GetMultiple(SearchCriteria.ForMenuBar(MenuControlType))); }
        }

        protected abstract ControlType MenuControlType { get; }

        public override void ActionPerformed(Action action)
        {
            action.Handle(this);
            ActionPerformed();
        }

        /// <summary>
        /// Get the modal window launched by this window.
        /// </summary>
        /// <param name="title">Title of the modal window</param>
        /// <param name="option">Newly created window would be initialized using this option</param>
        /// <returns></returns>
        public abstract Window ModalWindow(string title, InitializeOption option);

        /// <summary>
        /// Get the modal window launched by this window and it uses InitializeOption as NoCache
        /// </summary>
        /// <param name="title">Title of the modal window</param>
        /// <returns></returns>
        public virtual Window ModalWindow(string title)
        {
            return ModalWindow(title, InitializeOption.NoCache);
        }

        public override void Visit(WindowControlVisitor windowControlVisitor)
        {
            windowControlVisitor.Accept(this);
            currentContainerItemFactory.Visit(windowControlVisitor);
        }

        public virtual void WaitTill(WaitTillDelegate waitTillDelegate)
        {
            Clock clock = new Clock(CoreAppXmlConfiguration.Instance.BusyTimeout);
            clock.Perform(delegate { return waitTillDelegate(); }, delegate(object obj) { return obj.Equals(true); },
                          delegate { throw new UIActionException("Time out happened" + Constants.BusyMessage); });
        }

        public virtual void ReloadIfCached()
        {
            currentContainerItemFactory.ReloadIfCached();
        }

        public virtual DisplayState DisplayState
        {
            get
            {
                foreach (KeyValuePair<DisplayState, WindowVisualState> keyValuePair in windowStates)
                    if (keyValuePair.Value.Equals(WinPattern.Current.WindowVisualState)) return keyValuePair.Key;
                throw new Exception("Fatal error");
            }
            set
            {
                if (AlreadyInAskedState(value)) return;

                WinPattern.SetWindowVisualState(windowStates[value]);
                WaitWhileBusy();

                if (AlreadyInAskedState(value) || TitleBar == null) return;

                switch (value)
                {
                    case DisplayState.Maximized:
                        SetDisplayState(TitleBar.MaximizeButton);
                        break;
                    case DisplayState.Minimized:
                        SetDisplayState(TitleBar.MinimizeButton);
                        break;
                    case DisplayState.Restored:
                        SetDisplayState(TitleBar.RestoreButton);
                        break;
                }
            }
        }

        private bool AlreadyInAskedState(DisplayState value)
        {
            return (DisplayState.Maximized == value && !WinPattern.Current.CanMaximize) ||
                   (DisplayState.Minimized == value && !WinPattern.Current.CanMinimize);
        }

        private void SetDisplayState(Button button)
        {
            if (button == null) return;
            button.Click();
        }

        public virtual List<Tab> Tabs
        {
            get { return currentContainerItemFactory.FindAll<Tab>(); }
        }

        public override void HookEvents(UIItemEventListener eventListener)
        {
            handler = delegate { };
            Automation.AddAutomationEventHandler(AutomationElement.MenuOpenedEvent, automationElement, TreeScope.Descendants, handler);
        }

        public override void UnHookEvents()
        {
            Automation.RemoveAutomationEventHandler(AutomationElement.MenuOpenedEvent, automationElement, handler);
        }

        public override string ToString()
        {
            return Title;
        }

        public virtual void Dispose()
        {
            Close();
        }

        /// <summary>
        /// Get the MessageBox window launched by this window
        /// </summary>
        /// <param name="title">Title of the messagebox</param>
        /// <returns></returns>
        public virtual Window MessageBox(string title)
        {
            Window window = factory.ModalWindow(title, InitializeOption.NoCache, windowSession.ModalWindowSession(InitializeOption.NoCache));
            window.actionListener = this;
            return window;
        }

        public override ActionListener ActionListener
        {
            get { return this; }
        }

        public virtual void Focus(DisplayState displayState)
        {
            DisplayState = displayState;
            base.Focus();
        }

        public virtual TitleBar TitleBar
        {
            get { return factory.GetTitleBar(this); }
        }

        public virtual bool IsModal
        {
            get
            {
                return WinPattern.Current.IsModal;
            }
        }

        /// <summary>
        /// Find all the UIItems which belongs to a window and are within (bounds of) another UIItem.
        /// </summary>
        /// <param name="containingItem">Containing item</param>
        /// <returns>List of all the items.</returns>
        public virtual List<UIItem> ItemsWithin(UIItem containingItem)
        {
            UIItemCollection itemsWithin = factory.ItemsWithin(containingItem.Bounds, this);
            List<UIItem> items = new List<UIItem>();
            foreach (IUIItem item in itemsWithin)
                if (!item.Equals(containingItem)) items.Add((UIItem) item);
            return items;
        }

        //TODO: Position based find should understand MdiChild
        /// <summary>
        /// Returns a UIItemContainer using which other sub-ui items can be retrieved.
        /// Since there is no single standard identification for MdiChild windows, hence it is has been left open for user.
        /// </summary>
        /// <param name="searchCriteria"></param>
        /// <returns></returns>
        public virtual UIItemContainer MdiChild(SearchCriteria searchCriteria)
        {
            AutomationElementFinder finder = new AutomationElementFinder(automationElement);
            AutomationElement element = finder.Descendant(searchCriteria.AutomationCondition);
            return element == null ? null : new UIItemContainer(element, this, InitializeOption.NoCache, windowSession);
        }

        public override void ActionPerforming(UIItem uiItem)
        {
            VerticalSpan verticalSpan = new VerticalSpan(Bounds).Minus(ScrollBars.Horizontal.Bounds);
            new ScreenItem(uiItem, ScrollBars).MakeVisible(verticalSpan);
        }

        /// <summary>
        /// Recursively gets all the descendant windows.
        /// </summary>
        /// <returns></returns>
        public virtual List<Window> ModalWindows()
        {
            List<Window> modalWindows = new List<Window>();
            AutomationElementFinder finder = new AutomationElementFinder(automationElement);
            AutomationElementCollection descendants = finder.Descendants(AutomationSearchCondition.ByControlType(ControlType.Window));
            foreach (AutomationElement descendant in descendants)
            {
                modalWindows.Add(ChildWindowFactory.Create(descendant, InitializeOption.NoCache, windowSession.ModalWindowSession(InitializeOption.NoCache)));
            }
            return modalWindows;
        }
    }
}