/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 10:29
 */

using Core.UIItems;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.ListView.
	/// </summary>
    public sealed class TListview : FitUItem<ListView>
	{
        [MethodAttribute("根据文本获取ListView，参数为文本信息")]
        public override void GetByText(string value)
        {
            base.GetByText(value);
            listView = Item;
        }

        [MethodAttribute("根据Id获取ListView，参数为文本信息")]
        public override void GetById(string value)
        {
            base.GetById(value);
            listView = Item;
        }

        [MethodAttribute("选中当前ListView的行，参数为从0开始的行序号")]
        public void Select(int index)
        {
            Item.Select(index);
        }

        [MethodAttribute("单击当前ListView的列标签，参数为从0开始的列序号")]
        public void ClickHeader(int index)
        {
            Item.Header.Columns[index].Click();
        }

        [MethodAttribute("返回当前ListView的行数")]
        public int RowCount()
        {
            return Item.Rows.Count;
        }

        [MethodAttribute("返回当前ListView的列数")]
        public int ColumnCount()
        {
           return Item.Header.Columns.Count; 
        }

        [MethodAttribute("返回当前ListView的选中的行数")]
        public int SelectedRowCount()
        {
            return Item.SelectedRows.Count;
        }
	}
}
