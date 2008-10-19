using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.Scrolling
{
    public class ComboBoxScrollBars : ScrollBars
    {
        public ComboBoxScrollBars(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public override IHScrollBar Horizontal
        {
            get { return FindHorizontalBar(finder.Descendant); }
        }
        public override IVScrollBar Vertical
        {
            get { return FindVerticalBar(finder.Descendant); }
        }
    }
}