using System.Windows.Automation;
using Core.UIItems.Actions;

namespace Core.UIItems.Scrolling
{
    internal class ScrollerFactory
    {
        internal static IScrollBars CreateBars(AutomationElement parentElement, ActionListener listener)
        {
            if (parentElement.Current.FrameworkId.Equals(Constants.WPFFrameworkId))
                return new WPFScrollBars(parentElement, listener);
            else
                return new ScrollBars(parentElement, listener);
        }
    }
}