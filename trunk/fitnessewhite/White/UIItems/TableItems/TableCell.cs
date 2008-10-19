using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.WindowsAPI;

namespace Core.UIItems.TableItems
{
    //Todo Cannot find whether the cell is read-only or not
    //BUG There is better support for ComboBox cells, try it out
    public class TableCell : UIItem
    {
        private const string NullValue = "(null)";

        protected TableCell() {}
        public TableCell(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        //BUG: Document use of TableCell.Value method
        //BUG: Fix table which doesn't have header in it
        public virtual object Value
        {
            get
            {
                object value = Property(ValuePattern.ValueProperty);
                return NullValue.Equals(value) ? string.Empty : value;
            }
            set
            {
                actionListener.ActionPerforming(this);
                ValuePattern valuePattern = (ValuePattern) Pattern(ValuePattern.Pattern);
                if (value is string)
                {
                    Click();
                    valuePattern.SetValue(string.Empty);
                    keyboard.Send((string) value, actionListener);
                    keyboard.PressSpecialKey(KeyboardInput.SpecialKeys.TAB);
                }
                else
                {
                    if (!Value.Equals(value.ToString()))
                    {
                        Click();
                        valuePattern.SetValue(value.ToString());
                    }
                }
            }
        }

        public override void Click()
        {
            ((InvokePattern) Pattern(InvokePattern.Pattern)).Invoke();
        }

        public override void RightClick()
        {
            new TooltipSafeMouse(mouse).RightClickOutsideToolTip(this, actionListener);
        }

        public override void DoubleClick()
        {
            new TooltipSafeMouse(mouse).DoubleClickOutsideToolTip(this, actionListener);
        }
    }
}