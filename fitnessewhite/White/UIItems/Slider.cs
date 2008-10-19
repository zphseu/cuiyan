using System.Windows.Automation;
using Core.Factory;
using Core.Sessions;
using Core.UIItems.Actions;
using Core.WindowsAPI;

namespace Core.UIItems
{
    public abstract class Slider : UIItem
    {
        private readonly UIItemContainer uiItemContainer;

        protected Slider() {}
        public Slider(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener)
        {
            uiItemContainer = new UIItemContainer(automationElement, actionListener, InitializeOption.NoCache, new NullWindowSession());
        }

        public virtual double Value
        {
            get { return RangePattern().Current.Value; }
            set { RangePattern().SetValue(value); }
        }

        private RangeValuePattern RangePattern()
        {
            return ((RangeValuePattern)Pattern(RangeValuePattern.Pattern));
        }

        public virtual Button LargeIncrementButton
        {
            get
            {
                return uiItemContainer.Get<Button>(IncrementButtonId());
            }
        }

        protected abstract string IncrementButtonId();
        protected abstract string DecrementButtonId();

        public virtual Button LargeDecrementButton
        {
            get
            {
                return uiItemContainer.Get<Button>(DecrementButtonId());
            }
        }
        
        public virtual double LargeChangeAmount
        {
            get { return RangePattern().Current.LargeChange; }
        }

        public virtual double SmallChangeAmount
        {
            get { return RangePattern().Current.SmallChange; }
        }

        public virtual void SmallIncrement()
        {
            keyboard.PressSpecialKey(KeyboardInput.SpecialKeys.RIGHT, actionListener);
        }

        public virtual void SmallDecrement()
        {
            keyboard.PressSpecialKey(KeyboardInput.SpecialKeys.LEFT, actionListener);
        }
    }
}