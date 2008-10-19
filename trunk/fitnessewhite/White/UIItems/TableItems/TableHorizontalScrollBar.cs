using System;
using System.Windows;
using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.UIItems.Scrolling;

namespace Core.UIItems.TableItems
{
    public class TableHorizontalScrollBar : IHScrollBar
    {
        private readonly AutomationElement automationElement;
        private readonly ActionListener actionListener;

        protected TableHorizontalScrollBar() {}

        public TableHorizontalScrollBar(AutomationElement automationElement, ActionListener actionListener)
        {
            this.automationElement = automationElement;
            this.actionListener = actionListener;
        }

        public virtual void ScrollLeft()
        {
            ;
        }

        public virtual void ScrollRight()
        {
            ;
        }

        public virtual void ScrollLeftLarge()
        {
            ;
        }

        public virtual void ScrollRightLarge()
        {
            ;
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

        public virtual Rect Bounds
        {
            get { throw new NotSupportedException(); }
        }
    }
}