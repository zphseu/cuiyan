using System.Collections.Generic;
using Core.Factory;
using Core.UIItems.WindowItems;

namespace fitnessewhite
{
    public sealed class TDialog : FitUItem<Window>
    {
        [MethodAttribute("根据Title获取对象，参数为Title文本信息")]
        public override void GetByText(string title)
        {
            List<Window> wins = application.GetWindows();
            foreach (Window w in wins)
            {
                if (!w.Name.Trim().StartsWith(title)) continue;
                uitemcontainer = w;
                Item = w;
            }
        }

        [MethodAttribute("关闭当前窗口")]
        public void Close()
        {
            Item.Close();
        }

        [MethodAttribute("等待直到应用程序忙")]
        public void WaitWhileBusy()
        {
            Item.WaitWhileBusy();
        }

        [MethodAttribute("返回当前窗口的Title")]
        public string Title()
        {
            return Item.Title.Trim();
        }

        [MethodAttribute("返回当前窗口是否已经关闭")]
        public bool IsClosed()
        {
            return Item.IsClosed;
        }
    }
}
