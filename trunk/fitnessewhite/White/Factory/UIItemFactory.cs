using System.Windows.Automation;
using Core.UIItems;
using Core.UIItems.Actions;

namespace Core.Factory
{
    public interface UIItemFactory
    {
        IUIItem Create(AutomationElement automationElement, ActionListener actionListener);
    }
}