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
        [MethodAttribute("����Title��ȡ���󣬲���ΪTitle�ı���Ϣ")]
        public override void GetByText(string title)
        {
            Item = application.GetWindow(title, InitializeOption.NoCache);
            uitemcontainer = Item;
            mainwin = Item;
        }

        [MethodAttribute("�رյ�ǰ����")]
        public void Close()
        {
            Item.Close();
        }

        [MethodAttribute("�ȴ�ֱ��Ӧ�ó���æ")]
        public void WaitWhileBusy()
        {
            Item.WaitWhileBusy();
        }

        [MethodAttribute("���ص�ǰ�����Ƿ���PopupMenu")]
        public bool HasPopup()
        {
             return Item.HasPopup();
        }

        [MethodAttribute("���ص�ǰ���ڵ�Title")]
        public string Title()
        {
            return Item.Title.Trim();
        }

        [MethodAttribute("���ص�ǰ�����Ƿ��Ѿ��ر�")]
        public bool IsClosed()
        {
            return Item.IsClosed;
        }

        [MethodAttribute("���ص�ǰ����ToolTip�е��ı���Ϣ")]
        public string ToolTip()
        {
            return (Item != null && !string.IsNullOrEmpty(Item.ToolTip)) ? Item.ToolTip.Trim() : "NULL";
        }
    }
}
