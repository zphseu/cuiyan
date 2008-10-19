/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 10:29
 */
using System;
using Core;
using Core.WindowsAPI;
using Core.UIItems.ListBoxItems;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.ComboBox.
	/// </summary>
    public sealed class TCombobox : FitUItem<ComboBox>
	{
        [MethodAttribute("ѡ��ָ���ı�����")]
        public void Select(string value)
        {
            Item.Select(value);
        }

        [MethodAttribute("ʹ�ü������¼�ѡ��ָ���ı�����")]
        public void SelectWithKey(string value)
        {
            //��Win32ʱ������Ȳ�ѡ�е�һ���Ļ�����ѡ���ʱ�򣬵���ѡItem�ڵ�ǰItem֮�ϵĻ���
            //����������뵱ǰ��һ���������Ȼѡ����ǵ�ǰItem
            //��White��ȷ��д��Win32ComboBox����ˣ����ڻ���������������
            //������Ҫ���ڴ�ֱ��������
            if (value == Item.SelectedItemText) return;

            int curIndex = -1;
            int selectIndex = -1;
            int counter = 0;
            string selectText = Item.SelectedItemText;
            foreach (ListItem li in Item.Items)
            {
                if (li.Text == selectText) selectIndex = counter;
                if (li.Text == value) curIndex = counter;
                if (curIndex >= 0 && selectIndex >= 0) break;
                counter++;
            }

            if (curIndex < 0 || selectIndex < 0) return;

            Item.Focus();
            int dest = curIndex - selectIndex;
            KeyboardInput.SpecialKeys key = (dest > 0) ? KeyboardInput.SpecialKeys.DOWN : KeyboardInput.SpecialKeys.UP;
            dest = (dest > 0) ? dest : -dest;

            for (int i = 0; i < dest; i++)
            {
                if (Item.SelectedItemText == value) return;
                mainwin.Keyboard.PressSpecialKey(key);
            }
        }

        [MethodAttribute("���ص�ǰ��ѡ������ı���Ϣ")]
        public string Text()
        {
            return Item.SelectedItemText.Trim();
        }

        [MethodAttribute("���ص�ǰ��ĸ���")]
        public int ItemsCount()
        {
            return Item.Items.Count;
        }
	}
}
