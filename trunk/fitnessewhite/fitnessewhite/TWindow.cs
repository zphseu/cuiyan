/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 9:00
 */
using System.Collections.Generic;
using Core.Factory;
using Core.UIItems.WindowItems;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.Window.
	/// </summary>
    public sealed class TWindow : FitUItem<Window>
	{
        [MethodAttribute("根据Title获取对象，参数为Title文本信息")]
        public override void GetByText(string title)
        {
            Item = application.GetWindow(title, InitializeOption.NoCache);
            uitemcontainer = Item;
            mainwin = Item;
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

        [MethodAttribute("返回当前窗口是否有PopupMenu")]
        public bool HasPopup()
        {
             return Item.HasPopup();
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

        [MethodAttribute("返回当前窗口ToolTip中的文本信息")]
        public string ToolTip()
        {
            return (Item != null && !string.IsNullOrEmpty(Item.ToolTip)) ? Item.ToolTip.Trim() : "NULL";
        }
    }
}
