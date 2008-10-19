using System;
using System.Collections.Generic;
using System.Text;
using Core.UIItems;
using Core.UIItems.Finders;
using Core.UIItems.WindowItems;

namespace fitnessewhite
{
    public class TMessagebox : Guifixture
    {
        [MethodAttribute("根据文本获取对象，参数为文本信息")]
        public void GetByTitle(string title)
        {
            messagebox = mainwin.MessageBox(title);
        }

        public string Message()
        {
            SearchCriteria searchCriteria = SearchCriteria.ByAutomationId("65535");
            Label label = messagebox.Get<Label>(searchCriteria);
            return label.Text;
        }

        public void ClickByText(string text)
        {
            SearchCriteria searchCriteria = SearchCriteria.ByText(text);
            Button button = messagebox.Get<Button>(searchCriteria);
            button.Click();
        }

        public void Close()
        {
            messagebox.Close();
        }
    }
}
