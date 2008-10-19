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
        [MethodAttribute("选中指定文本的项")]
        public void Select(string value)
        {
            Item.Select(value);
        }

        [MethodAttribute("使用键盘上下键选中指定文本的项")]
        public void SelectWithKey(string value)
        {
            //当Win32时，如果先不选中第一个的话，在选择的时候，当被选Item在当前Item之上的话，
            //上面的坐标与当前的一样，结果仍然选择的是当前Item
            //但White的确编写了Win32ComboBox，因此，现在还不清楚问题在哪里。
            //估计主要出在垂直滚动条上
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

        [MethodAttribute("返回当前被选中项的文本信息")]
        public string Text()
        {
            return Item.SelectedItemText.Trim();
        }

        [MethodAttribute("返回当前项的个数")]
        public int ItemsCount()
        {
            return Item.Items.Count;
        }
	}
}
