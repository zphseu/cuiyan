using System.Windows.Automation;
using Bricks.Core;
using Core.AutomationElementSearch;
using Core.Configuration;
using Core.Factory;
using Core.UIItems.Actions;
using Core.UIItems.Finders;

namespace Core.UIItems.Scrolling
{
    internal class ScrollBar : UIItem, IScrollBar
    {
        private readonly PrimaryUIItemFactory primaryUIItemFactory;

        protected virtual Button backSmallChangeButton
        {
            get { return FindButton(actionListener, "Back by small amount"); }
        }

        protected virtual Button forwardSmallChangeButton
        {
            get { return FindButton(actionListener, "Forward by small amount"); }
        }

        protected virtual Button backLargeChangeButton
        {
            get {return FindButton(actionListener, "Back by large amount");}
        }

        protected virtual Button forwardLargeChangeButton
        {
            get { return FindButton(actionListener, "Forward by large amount"); }
        }

        protected ScrollBar() {}

        protected ScrollBar(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            AutomationElementFinder finder = new AutomationElementFinder(automationElement);
            primaryUIItemFactory = new PrimaryUIItemFactory(finder);
        }

        private Button FindButton(ActionListener listener, string text)
        {
            return (Button) primaryUIItemFactory.Create(SearchCriteria.ByControlType(ControlType.Button).AndByText(text), listener);
        }

        public virtual double Value
        {
            get { return (double) Property(RangeValuePattern.ValueProperty); }
        }

        public virtual void SetToMinimum()
        {
            Clock clock = new Clock(CoreAppXmlConfiguration.Instance.BusyTimeout, 0);
            clock.RunWhile(delegate { backLargeChangeButton.Click(); }, delegate { return Value > 0; },
                           delegate { throw new UIActionException("Could not set the ScrollBar to minimum visible" + Constants.BusyMessage); });
        }

        public virtual void SetToMaximum()
        {
            ((RangeValuePattern) Pattern(RangeValuePattern.Pattern)).SetValue(MaximumValue);
        }

        public virtual double MinimumValue
        {
            get { return (double) Property(RangeValuePattern.MinimumProperty); }
        }

        public virtual double MaximumValue
        {
            get { return (double) Property(RangeValuePattern.MaximumProperty); }
        }
    }
}