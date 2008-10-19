/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 10:29
 */

using System;
using Core.UIItems;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.ListViewCell.
	/// </summary>
    public sealed  class TListviewcell : FitUItem<ListViewCell>
	{
        [MethodAttribute("根据文本获取当前ListView的Cell，参数为文本，个数为从0开始的 \"行名称;列头名称\"")]
        public void GetByIndex(string columnIndex) 
        {
            string[] items = SplitString(columnIndex);

            if (items.Length > 1)
                Item = listView.Cell(items[1], int.Parse(items[0]));
            else
                throw new ArgumentException("param format: zeroBaseRowIndex;columnHeaderName");					
		}

        [MethodAttribute("返回当前Cell的参数为文本信息")]
        public string Text()
        {
			 return Item.Text.Trim();
		}
	}
}
