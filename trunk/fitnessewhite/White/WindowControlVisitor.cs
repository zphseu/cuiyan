using Core.UIItems;

namespace Core
{
    public interface WindowControlVisitor
    {
        void Accept(UIItem uiItem);
    }
}