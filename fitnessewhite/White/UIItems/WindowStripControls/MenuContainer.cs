using Core.UIItems.MenuItems;

namespace Core.UIItems.WindowStripControls
{
    public interface MenuContainer
    {
        Menu MenuItem(params string[] path);
    }
}