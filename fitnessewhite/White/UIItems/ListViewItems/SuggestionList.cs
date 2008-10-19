using System.Collections.Generic;

namespace Core.UIItems.ListViewItems
{
    public interface SuggestionList
    {
        List<string> Items { get; }
        void Select(string text);
    }
}