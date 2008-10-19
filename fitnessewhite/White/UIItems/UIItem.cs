using System;
using System.Windows;
using System.Windows.Automation;
using Bricks.Core;
using Core.AutomationElementSearch;
using Core.Factory;
using Core.InputDevices;
using Core.Logging;
using Core.Recording;
using Core.UIItemEvents;
using Core.UIItems.Actions;
using Core.UIItems.Finders;
using Core.UIItems.Scrolling;
using Core.WindowsAPI;
using Window=Core.UIItems.WindowItems.Window;

namespace Core.UIItems
{
    //TODO Make this class smaller
    //TODO ToolStrip and Similar kind of support
    public class UIItem : IUIItem
    {
        protected AutomationElement automationElement;
        protected ActionListener actionListener;
        internal static Mouse mouse = Mouse.Instance;
        protected PrimaryUIItemFactory factory;
        internal Keyboard keyboard = Keyboard.Instance;
        protected IScrollBars scrollBars;
        private AutomationEventHandler handler;

        protected UIItem() {}

        public UIItem(AutomationElement automationElement, ActionListener actionListener)
        {
            if (null == automationElement) throw new NullReferenceException();
            this.automationElement = automationElement;
            this.actionListener = actionListener;
            factory = new PrimaryUIItemFactory(new AutomationElementFinder(automationElement));
        }

        /// <summary>
        /// Should be used only if white doesn't support the feature you are looking for.
        /// Knowledge of UIAutomation would be required. It would better idea to also raise an issue if you are using it.
        /// </summary>
        public virtual AutomationElement AutomationElement
        {
            get { return automationElement; }
        }

        protected virtual object Property(AutomationProperty automationProperty)
        {
            return automationElement.GetCurrentPropertyValue(automationProperty);
        }

        public virtual bool Enabled
        {
            get { return automationElement.Current.IsEnabled; }
        }

        public virtual WindowsFramework Framework
        {
            get { return new WindowsFramework(automationElement.Current.FrameworkId); }
        }

        public virtual Point Location
        {
            get { return C.TopLeft(automationElement.Current.BoundingRectangle); }
        }

        protected virtual void ActionPerformed()
        {
            actionListener.ActionPerformed(Action.WindowMessage);
        }

        public virtual Rect Bounds
        {
            get { return automationElement.Current.BoundingRectangle; }
        }

        public virtual string Name
        {
            get
            {
                try
                {
                    return automationElement.Current.Name;
                }
                catch (InvalidOperationException)
                {
                    return automationElement.Current.Name;
                }
            }
        }

        public virtual System.Drawing.Point ClickablePoint
        {
            get
            {
                Point clickablePoint = (Point) Property(AutomationElement.ClickablePointProperty);
                return new System.Drawing.Point((int) clickablePoint.X, (int) clickablePoint.Y);
            }
        }

        public virtual string AccessKey
        {
            get { return automationElement.Current.AccessKey; }
        }

        public virtual bool ValueOfEquals(AutomationProperty property, object compareTo)
        {
            return Property(property).Equals(compareTo);
        }

        protected virtual BasePattern Pattern(AutomationPattern pattern)
        {
            return Pattern(AutomationElement, pattern);
        }

        internal static BasePattern Pattern(AutomationElement automationElement, AutomationPattern pattern)
        {
            object patternObject;
            if (automationElement.TryGetCurrentPattern(pattern, out patternObject))
            {
                return (BasePattern) patternObject;
            }
            return null;
        }

        public virtual void RightClick()
        {
            RightClickOnCenter();
        }

        private void RightClickOnCenter()
        {
            actionListener.ActionPerforming(this);
            System.Drawing.Point point = C.Center(Bounds);
            mouse.RightClick(point, actionListener);
        }

        public virtual void Focus()
        {
            actionListener.ActionPerforming(this);
            try
            {
                if (automationElement.Current.IsKeyboardFocusable) automationElement.SetFocus();
                ActionPerformed();
            }
            catch (InvalidOperationException) {}
        }

        public virtual void Visit(WindowControlVisitor windowControlVisitor)
        {
            windowControlVisitor.Accept(this);
        }

        public virtual string Id
        {
            get { return automationElement.Current.AutomationId; }
        }

        public virtual bool Visible
        {
            get { return !automationElement.Current.IsOffscreen; }
        }

        /// <summary>
        /// Provides the Error on this UIItem. This would return Error object when this item has ErrorProvider displayed next to it.
        /// </summary>
        /// <param name="window"></param>
        /// <returns></returns>
        public virtual Error Error(Window window)
        {
            AutomationElement element = AutomationElement.FromPoint(C.ImmediateExteriorEast(automationElement.Current.BoundingRectangle));
            if (element == null) return null;
            Rect errorProviderBounds = element.Current.BoundingRectangle;
            if (automationElement.Current.BoundingRectangle.Right != errorProviderBounds.Left) return null;
            mouse.Location = C.Center(errorProviderBounds);
            actionListener.ActionPerformed(Action.WindowMessage);
            return new Error(window.ToolTip);
        }

        public virtual bool NameMatches(string text)
        {
            return Name.Equals(text);
        }

        public virtual string PrimaryIdentification
        {
            get { return automationElement.Current.FrameworkId.Equals(Constants.Win32FrameworkId) ? Name : Id; }
        }

        public virtual ActionListener ActionListener
        {
            get { return actionListener; }
        }

        /// <summary>
        /// Performs mouse click at the center of this item
        /// </summary>
        public virtual void Click()
        {
            actionListener.ActionPerforming(this);
            InternalClick();
        }

        internal virtual void InternalClick()
        {
            if (!Enabled) WhiteLogger.Instance.WarnFormat("Clicked on disabled item: {0}", ToString());
            mouse.Click(C.Center(Bounds), actionListener);
        }

        /// <summary>
        /// Performs mouse double click at the center of this item
        /// </summary>
        public virtual void DoubleClick()
        {
            actionListener.ActionPerforming(this);
            mouse.DoubleClick(C.Center(Bounds), actionListener);
        }

        /// <summary>
        /// Perform keyboard action on this UIItem
        /// </summary>
        /// <param name="key"></param>
        public virtual void KeyIn(KeyboardInput.SpecialKeys key)
        {
            actionListener.ActionPerforming(this);
            keyboard.PressSpecialKey(key, actionListener);
        }

        public override bool Equals(object obj)
        {
            if (this == obj) return true;
            UIItem uiItem = obj as UIItem;
            if (uiItem == null) return false;
            return Equals(automationElement, uiItem.AutomationElement);
        }

        public override int GetHashCode()
        {
            return automationElement.GetHashCode();
        }

        public override string ToString()
        {
            return GetType().Name + " with AutomationId=" + S.Get(Id, "<empty>") + " and Name=" + S.Get(Name, "<empty>");
        }

        public virtual IScrollBars ScrollBars
        {
            get
            {
                if (scrollBars == null) scrollBars = ScrollerFactory.CreateBars(automationElement, actionListener);
                return scrollBars;
            }
        }

        protected virtual void HookClickEvent(UIItemEventListener eventListener)
        {
            handler = delegate { eventListener.EventOccured(new UIItemClickEvent(this)); };
            Automation.AddAutomationEventHandler(InvokePattern.InvokedEvent, automationElement, TreeScope.Element, handler);
        }

        protected virtual void UnHookClickEvent()
        {
            Automation.RemoveAutomationEventHandler(InvokePattern.InvokedEvent, automationElement, handler);
        }

        public virtual bool IsOffScreen
        {
            get { return automationElement.Current.IsOffscreen; }
        }

        public virtual bool IsFocussed
        {
            get { return automationElement.Current.HasKeyboardFocus; }
        }

        /// <summary>
        /// Internal to white and intended to be used for white recording
        /// </summary>
        public virtual void UnHookEvents() {}

        /// <summary>
        /// Internal to white and intended to be used for white recording
        /// </summary>
        /// <param name="eventListener"></param>
        public virtual void HookEvents(UIItemEventListener eventListener) {}

        public virtual void SetValue(object value) {}

        public virtual void ActionPerforming(UIItem uiItem) {}

        public virtual void ActionPerformed(Action action)
        {
            actionListener.ActionPerformed(action);
        }

        public virtual void LogStructure()
        {
            WhiteLogger.Instance.Info(Debug.Details(automationElement));
        }

        public static string ToString(AutomationElement element)
        {
            AutomationElement.AutomationElementInformation elementInformation = element.Current;
            return string.Format("AutomationId:{0}, Name:{1}, ControlType:{2}, FrameworkId:{3}", elementInformation.AutomationId, elementInformation.Name,
                          elementInformation.ControlType.ProgrammaticName, elementInformation.FrameworkId);
        }

        /// <summary>
        /// Uses the Raw View provided by UIAutomation to find elements within this UIItem. RawView sometimes contains extra AutomationElements. This is internal to 
        /// white although made public. Should be used only if the standard approaches dont work. Also if you end up using it please raise an issue
        /// so that it can be fixed.
        /// Please understand that calling this method on any UIItem which has a lot of child AutomationElements might result in very bad performance.
        /// </summary>
        /// <param name="searchCriteria"></param>
        /// <returns>null or found AutomationElement</returns>
        public virtual AutomationElement GetElement(SearchCriteria searchCriteria)
        {
            return new AutomationElementFinder(automationElement).FindDescendantRaw(searchCriteria.AutomationSearchCondition);
        }

        public virtual void Enter(string value)
        {
            keyboard.PressSpecialKey(KeyboardInput.SpecialKeys.HOME);
            keyboard.HoldKey(KeyboardInput.SpecialKeys.SHIFT);
            keyboard.PressSpecialKey(KeyboardInput.SpecialKeys.END);
            keyboard.LeaveKey(KeyboardInput.SpecialKeys.SHIFT);
            keyboard.PressSpecialKey(KeyboardInput.SpecialKeys.DELETE);
            ValuePattern pattern = Pattern(ValuePattern.Pattern) as ValuePattern;
            if (pattern != null) pattern.SetValue(string.Empty);
            actionListener.ActionPerformed(Action.WindowMessage);
            EnterData(value);
        }

        protected virtual void EnterData(string value)
        {
            keyboard.Send(value, actionListener);
        }
    }
}