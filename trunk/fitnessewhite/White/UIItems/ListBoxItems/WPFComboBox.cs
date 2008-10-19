using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.UIItems.Scrolling;

namespace Core.UIItems.ListBoxItems
{
    [PlatformSpecificItem]
    public class WPFComboBox : ComboBox
    {
        protected WPFComboBox() {}
        public WPFComboBox(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        public override IScrollBars ScrollBars
        {
            get
            {
                if (scrollBars == null) scrollBars = new WPFScrollBars(automationElement, actionListener);
                return scrollBars;
            }
        }

        protected override VerticalSpan VerticalSpan
        {
            get
            {
                double listTop = Items[0].Bounds.Top;
                double listBottom = Items[Items.Count - 1].Bounds.Bottom;

                ScrollPattern scrollPattern = (ScrollPattern) Pattern(ScrollPattern.Pattern);
                double percentVisible = scrollPattern.Current.VerticalViewSize;

                double comboBoxBottom = Bounds.Bottom;
                return new VerticalSpan(comboBoxBottom, comboBoxBottom + (((listBottom - listTop)*percentVisible)/100));
            }
        }

        protected override void ToggleDropDown()
        {
            mouse.Click(C.Center(automationElement.Current.BoundingRectangle), actionListener);
        }

        public override void ActionPerforming(UIItem uiItem)
        {
//            ToggleDropDown();
            base.ActionPerforming(uiItem);
        }
    }
}