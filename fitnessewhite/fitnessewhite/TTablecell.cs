/*
 * Created by SharpDevelop.
 * User: Administrator
 * Date: 2008-10-19
 * Time: 18:58
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using Core.UIItems.TableItems;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.ListViewCell.
	/// </summary>
    public sealed  class TTablecell : FitUItem<TableCell>
	{
        [MethodAttribute("�����ı���ȡ��ǰTable��Cell������Ϊ�ı�������Ϊ��0��ʼ�� \"�к�;�к�\"")]
        public void GetByIndex(string columnIndex) 
        {
            string[] items = SplitString(columnIndex);

            if (items.Length > 1)
            	Item = table.Rows[int.Parse(items[0])].Cells[int.Parse(items[1])];
            else
                throw new ArgumentException("param format: zeroBaseRowIndex;eroBasecolumnIndex");					
		}
        
        [MethodAttribute("����ֵ���磺b:true��b:false��i:124��Hello��")]
        public void SetValue(string s)
        {
        	object v = null;
        	string stmp = s.ToLower();
        	if (stmp == "b:true")
        		v = true;
        	else if (stmp == "b:false")
        		v = false;
        	else if (stmp.StartsWith("i:"))
        	{
        		stmp = stmp.Remove(0, 2);
        		v = int.Parse(stmp);
        	}
        	else
        		v = s;
        		
        	Item.Value = s;
        }
        
        [MethodAttribute("���ֵ���磺b:true��b:false��i:124��Hello��")]
        public string GetValue()
        {
        	string v = null;
        	if (Item.Value.GetType() == typeof(bool))
        	{
        		bool bv = (bool)Item.Value;
        		v = bv ? "b:true" : "b:false";
        	}
        	else if (Item.Value.GetType() == typeof(int))
        	{
        		v = "i:" + Item.Value.ToString();
        	}
        	else
        		v = Item.Value.ToString();
        		
        	return v;
        }
	}
}
