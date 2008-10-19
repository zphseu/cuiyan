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
        [MethodAttribute("Check指定文本的项")]
		public void Check(string value) {
			Item.Check(value);
		}

        [MethodAttribute("UnCheck指定文本的项")]
        public void UnCheck(string value)
        {
            Item.UnCheck(value);
		}

        [MethodAttribute("选中指定文本的项")]
        public void Select(string value)
        {
            Item.Select(value);
		}

        //[MethodAttribute("返回指定文本的项是否被Check")]
        //public bool IsChecked(string value)
        //{
        //    return Item.IsChecked(value);
        //}

        //[MethodAttribute("返回指定文本的项是否被选中")]
        //public bool IsSelected(string value)
        //{
        //    return Item.IsSelected(value);
        //}

        [MethodAttribute("返回文本信息")]
        public string Text()
        {
            return Item.SelectedItemText.Trim();
		}

        [MethodAttribute("返回项的个数")]
        public int ItemsCount()
        {
           return Item.Items.Count; 
		}
    }
}
