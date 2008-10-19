/*
 * Created by SharpDevelop.
 * User: Administrator
 * Date: 2008-10-19
 * Time: 20:09
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
//using System;
using System.Windows.Automation;
using Core.UIItems;
using Core.UIItems.Finders;
using Core.AutomationElementSearch;

namespace fitnessewhite
{
	/// <summary>
	/// Description of TEcopGrid.
	/// </summary>
	public class TEcopGrid : Guifixture
	{
		private ListView item = null;
		private int selectindex = -1;
		
        [MethodAttribute("根据文本获取ListView，参数为文本信息")]
        public void GetByText(string value)
        {
            SearchCriteria searchCriteria = SearchCriteria.ByText(value);
            item = uitemcontainer.Get<ListView>(searchCriteria);
        }

        [MethodAttribute("根据Id获取ListView，参数为文本信息")]
        public void GetById(string value)
        {
            SearchCriteria searchCriteria = SearchCriteria.ByAutomationId(value);
            item = uitemcontainer.Get<ListView>(searchCriteria);
        }

        [MethodAttribute("选中当前ListView的行，参数为从0开始的行序号")]
        public void Select(int index)
        {
            item.Select(index);
        	selectindex = index;
        }
     
        [MethodAttribute("返回当前ListView的行数")]
        public int RowCount()
        {
            return item.Rows.Count;
        }

        [MethodAttribute("返回当前ListView的列数")]
        public int ColumnCount()
        {
           return item.Header.Columns.Count; 
        }
        
        [MethodAttribute("返回指定行的状态。格式为：checkBoxStatus;text1;text2;...。注意末尾要写;号。")]
        public string SelectRowStatus()
        {
        	string s = searchCheckBox(selectindex).IsSelected.ToString();
        	foreach(ListViewCell cell in item.SelectedRows[0].Cells)
        		s += cell.Text + ";";
        	return s;
        }
    	
        private CheckBox searchCheckBox(int rowIndex)
        {
        	AutomationElementFinder rowfinder = new AutomationElementFinder(item.AutomationElement);
        	AutomationElementCollection collection = rowfinder.Descendants(AutomationSearchCondition.ByControlType(ControlType.DataItem));
        	AutomationElementFinder cellfinder = new AutomationElementFinder(collection[rowIndex]);
        	collection = cellfinder.Children(AutomationSearchCondition.ByControlType(ControlType.CheckBox));
        	return new CheckBox(collection[0], item.ActionListener);
        }
        
        [MethodAttribute("选中指定行。参数为rowIndex，如果为负数则全选中。")]
        public void Check(int rowIndex)
        {
        	if (rowIndex >= 0)
        		searchCheckBox(rowIndex).Select();
        	else
        		for(int i = 0; i < RowCount(); i++)	Check(i);
        }

        [MethodAttribute("取消选中指定行。参数为rowIndex，如果为负数则全取消选中。")]
        public void UnCheck(int rowIndex)
        {
        	if (rowIndex >= 0)
        		searchCheckBox(rowIndex).UnSelect();
        	else
        		for(int i = 0; i < RowCount(); i++)	UnCheck(i);
        }

        [MethodAttribute("选中指定多行。参数格式为：rowIndex1;rowIndex2;rowIndex3;...")]
        public void Checks(string rowIndexs)
        {
        	UnCheck(-1);
        	foreach(string index in SplitString(rowIndexs))
        		Check(int.Parse(index));
        }

        [MethodAttribute("取消选中指定多行。参数为rowIndex1;rowIndex2;rowIndex3;...")]
        public void UnChecks(string rowIndexs)
        {
        	Check(-1);
        	foreach(string index in SplitString(rowIndexs))
        		UnCheck(int.Parse(index));
        }        
	}
}
