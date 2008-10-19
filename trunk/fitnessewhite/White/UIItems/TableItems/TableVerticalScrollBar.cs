using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.UIItems.Scrolling;

namespace Core.UIItems.TableItems
{
    //TODO Table in scrolled position is not supported
    public class TableVerticalScrollBar : UIItem, IVScrollBar
    {
        protected TableVerticalScrollBar() {}

        public TableVerticalScrollBar(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public virtual void ScrollUp()
        {
            mouse.Click(C.Convert(C.ImmediateInteriorNorth(Bounds)), actionListener);
        }

        public virtual void ScrollDown()
        {
            mouse.Click(C.Convert(C.ImmediateInteriorSouth(Bounds)), actionListener);
        }

        public virtual void ScrollUpLarge()
        {
            ScrollUp();
        }

        public virtual void ScrollDownLarge()
        {
            ScrollDown();
        }

        public virtual bool IsScrollable
        {
            get { return true; }
        }

        public virtual double Value
        {
            get { return 0; }
        }

        public virtual double MinimumValue
        {
            get { return 0; }
        }

        public virtual double MaximumValue
        {
            get { return 100; }
        }

        public virtual void SetToMinimum() {}

        public virtual void SetToMaximum() {}
    }
}