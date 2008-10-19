/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 10:29
 */

using Core.UIItems.ListBoxItems;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.ListBox.
	/// </summary>
    public sealed class TListbox : FitUItem<ListBox>
	{
        [MethodAttribute("Checkָ���ı�����")]
		public void Check(string value) {
			Item.Check(value);
		}

        [MethodAttribute("UnCheckָ���ı�����")]
        public void UnCheck(string value)
        {
            Item.UnCheck(value);
		}

        [MethodAttribute("ѡ��ָ���ı�����")]
        public void Select(string value)
        {
            Item.Select(value);
		}

        //[MethodAttribute("����ָ���ı������Ƿ�Check")]
        //public bool IsChecked(string value)
        //{
        //    return Item.IsChecked(value);
        //}

        //[MethodAttribute("����ָ���ı������Ƿ�ѡ��")]
        //public bool IsSelected(string value)
        //{
        //    return Item.IsSelected(value);
        //}

        [MethodAttribute("�����ı���Ϣ")]
        public string Text()
        {
            return Item.SelectedItemText.Trim();
		}

        [MethodAttribute("������ĸ���")]
        public int ItemsCount()
        {
           return Item.Items.Count; 
		}
    }
}
