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
        [MethodAttribute("�����ı���ȡ��ǰListView��Cell������Ϊ�ı�������Ϊ��0��ʼ�� \"������;��ͷ����\"")]
        public void GetByIndexName(string columnIndex) 
        {
            string[] items = SplitString(columnIndex);

            if (items.Length > 1)
                Item = listView.Cell(items[1], int.Parse(items[0]));
            else
                throw new ArgumentException("param format: zeroBaseRowIndex;columnHeaderName");					
		}

        [MethodAttribute("�����ı���ȡ��ǰListView��Cell������Ϊ�ı�������Ϊ��0��ʼ�� \"�к�;�к�\"")]
        public void GetByIndex(string columnIndex) 
        {
            string[] items = SplitString(columnIndex);

            if (items.Length > 1)
            	Item = listView.Rows[int.Parse(items[0])].Cells[int.Parse(items[1])];
            else
                throw new ArgumentException("param format: zeroBaseRowIndex;eroBasecolumnIndex");					
		}
        
        [MethodAttribute("���ص�ǰCell�Ĳ���Ϊ�ı���Ϣ")]
        public string Text()
        {
			 return Item.Text.Trim();
		}
	}
}
