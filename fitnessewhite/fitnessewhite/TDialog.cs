using System.Collections.Generic;
using Core.Factory;
using Core.UIItems.WindowItems;

namespace fitnessewhite
{
    public sealed class TDialog : FitUItem<Window>
    {
        [MethodAttribute("����Title��ȡ���󣬲���ΪTitle�ı���Ϣ")]
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
    }
}
