/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 8:44
 */

using Core.UIItems;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.RadioButton.
    /// </summary>
    public sealed class TRadiobutton : FitUItem<RadioButton>
    {
        [MethodAttribute("选中当前RadioButton")]
        public void Select()
        {
            Item.Select();
        }

        [MethodAttribute("返回当前RadioButton是否选中")]
        public bool IsSelected()
        {
            return Item.IsSelected;
        }

        [MethodAttribute("根据文本信息获取当前RadioButton，并选中")]
        public void SelectByText(string text)
        {
            GetByText(text);
            Select();
        }

        [MethodAttribute("根据Id获取当前RadioButton，并选中")]
        public void SelectById(string id)
        {
            GetById(id);
            Select();
        }

        //[MethodAttribute("根据文本信息获取当前RadioButton，并返回是否选中")]
        //public bool IsSelectedByText(string text)
        //{
        //    GetByText(text);
        //    return Item.IsSelected;
        //}

        //[MethodAttribute("根据Id获取当前RadioButton，并返回是否选中")]
        //public bool IsSelectedById(string id)
        //{
        //    GetById(id);
        //    return Item.IsSelected;
        //}
    }
}
