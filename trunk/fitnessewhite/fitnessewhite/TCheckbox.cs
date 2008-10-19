/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 9:04
 */

using Core.UIItems;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.CheckBox.
    /// </summary>
    public sealed class TCheckbox : FitUItem<CheckBox>
    {
        [MethodAttribute("选中当前CheckBox")]
        public void Select()
        {
            Item.Select();
        }

        [MethodAttribute("根据文本获取当前CheckBox，并选中")]
        public void SelectByText(string text)
        {
            GetByText(text);
            Select();
        }

        [MethodAttribute("根据Id获取当前CheckBox，并选中")]
        public void SelectById(string id)
        {
            GetById(id);
            Select();
        }

        [MethodAttribute("取消选中当前CheckBox")]
        public void UnSelect()
        {
            Item.UnSelect();
        }

        [MethodAttribute("根据文本获取当前CheckBox，并取消选中")]
        public void UnSelectByText(string text)
        {
            GetByText(text);
            UnSelect();
        }

        [MethodAttribute("根据Id获取当前CheckBox，并取消选中")]
        public void UnSelectById(string id)
        {
            GetById(id);
            UnSelect();
        }

        [MethodAttribute("返回当前CheckBox是否选中")]
        public bool IsSelected()
        {
            return Item.IsSelected;
        }

        //[MethodAttribute("根据文本获取当前CheckBox，并返回是否选中")]
        //public bool IsSelectedByText(string text)
        //{
        //    GetByText(text);
        //    return Item.IsSelected;
        //}

        //[MethodAttribute("根据Id获取当前CheckBox，并返回是否选中")]
        //public bool IsSelectedById(string id)
        //{
        //    GetById(id);
        //    return Item.IsSelected;
        //}

        [MethodAttribute("返回当前CheckBox是否Checked")]
        public bool IsChecked()
        {
            return Item.Checked;
        }

        //[MethodAttribute("根据文本获取当前CheckBox，并返回是否Checked")]
        //public bool IsCheckedByText(string text)
        //{
        //    GetByText(text);
        //    return Item.Checked;
        //}

        //[MethodAttribute("根据Id获取当前CheckBox，并返回是否Checked")]
        //public bool IsCheckedById(string id)
        //{
        //    GetById(id);
        //    return Item.Checked;
        //}
    }
}
