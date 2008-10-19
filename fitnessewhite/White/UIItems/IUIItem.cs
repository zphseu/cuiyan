using System.Windows;
using System.Windows.Automation;
using Core.UIItems.Actions;
using Point=System.Drawing.Point;
using Window=Core.UIItems.WindowItems.Window;

namespace Core.UIItems
{
    public interface IUIItem : ActionListener
    {
        AutomationElement AutomationElement { get; }
        Rect Bounds { get; }
        string Name { get; }
        Point ClickablePoint { get; }
        bool ValueOfEquals(AutomationProperty property, object compareTo);
        void RightClick();
        void Focus();
        void Visit(WindowControlVisitor windowControlVisitor);
        string Id { get; }
        bool Visible { get; }
        Error Error(Window window);
        bool NameMatches(string text);
        string PrimaryIdentification { get; }
        bool Enabled { get; }
        WindowsFramework Framework { get; }
        System.Windows.Point Location { get; }
    }
}