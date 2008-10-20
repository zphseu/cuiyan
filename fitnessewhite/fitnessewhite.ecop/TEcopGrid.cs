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
		
        [MethodAttribute("�����ı���ȡEcopGrid������Ϊ�ı���Ϣ")]
        public void GetByText(string value)
        {
            SearchCriteria searchCriteria = SearchCriteria.ByText(value);
            item = uitemcontainer.Get<ListView>(searchCriteria);
        }

        [MethodAttribute("����Id��ȡEcopGrid������Ϊ�ı���Ϣ")]
        public void GetById(string value)
        {
            SearchCriteria searchCriteria = SearchCriteria.ByAutomationId(value);
            item = uitemcontainer.Get<ListView>(searchCriteria);
        }

        [MethodAttribute("ѡ�е�ǰEcopGrid���У�����Ϊ��0��ʼ�������")]
        public void Select(int index)
        {
            item.Select(index);
        	selectindex = index;
        }

        [MethodAttribute("���ص�ǰEcopGrid������")]
        public int RowCount()
        {
            return item.Rows.Count;
        }

        [MethodAttribute("���ص�ǰEcopGrid������")]
        public int ColumnCount()
        {
           return item.Header.Columns.Count; 
        }
        
        [MethodAttribute("����ָ���е�״̬����ʽΪ��checkBoxStatus;text1;text2;...��ע��ĩβҪд;�š�")]
        public string SelectRowStatus()
        {
        	string s = searchCheckBox(selectindex).IsSelected.ToString();
        	foreach(ListViewCell cell in item.SelectedRows[0].Cells)
        		s += cell.Text + ";";
        	return s;
        }
    	
        private CheckBox searchCheckBox(int rowIndex)
        {
        	AutomationElementFinder cellfinder = new AutomationElementFinder(item.Rows[rowIndex].AutomationElement);
            AutomationElementCollection collection = cellfinder.Children(AutomationSearchCondition.ByControlType(ControlType.CheckBox));
        	return new CheckBox(collection[0], item.ActionListener);
        }
        
        [MethodAttribute("ѡ��ָ���С�����ΪrowIndex�����Ϊ������ȫѡ�С�")]
        public void Check(int rowIndex)
        {
        	if (rowIndex >= 0)
        		searchCheckBox(rowIndex).Select();
        	else
        		for(int i = 0; i < RowCount(); i++)	Check(i);
        }

        [MethodAttribute("ȡ��ѡ��ָ���С�����ΪrowIndex�����Ϊ������ȫȡ��ѡ�С�")]
        public void UnCheck(int rowIndex)
        {
        	if (rowIndex >= 0)
        		searchCheckBox(rowIndex).UnSelect();
        	else
        		for(int i = 0; i < RowCount(); i++)	UnCheck(i);
        }

        [MethodAttribute("ѡ��ָ�����С�������ʽΪ��rowIndex1;rowIndex2;rowIndex3;...")]
        public void Checks(string rowIndexs)
        {
        	UnCheck(-1);
        	foreach(string index in SplitString(rowIndexs))
        		Check(int.Parse(index));
        }

        [MethodAttribute("ȡ��ѡ��ָ�����С�����ΪrowIndex1;rowIndex2;rowIndex3;...")]
        public void UnChecks(string rowIndexs)
        {
        	Check(-1);
        	foreach(string index in SplitString(rowIndexs))
        		UnCheck(int.Parse(index));
        }        
	}
}
