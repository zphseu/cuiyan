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
        [MethodAttribute("�����ı���ȡListView������Ϊ�ı���Ϣ")]
        public override void GetByText(string value)
        {
            base.GetByText(value);
            listView = Item;
        }

        [MethodAttribute("����Id��ȡListView������Ϊ�ı���Ϣ")]
        public override void GetById(string value)
        {
            base.GetById(value);
            listView = Item;
        }

        [MethodAttribute("ѡ�е�ǰListView���У�����Ϊ��0��ʼ�������")]
        public void Select(int index)
        {
            Item.Select(index);
        }

        [MethodAttribute("������ǰListView���б�ǩ������Ϊ��0��ʼ�������")]
        public void ClickHeader(int index)
        {
            Item.Header.Columns[index].Click();
        }

        [MethodAttribute("���ص�ǰListView������")]
        public int RowCount()
        {
            return Item.Rows.Count;
        }

        [MethodAttribute("���ص�ǰListView������")]
        public int ColumnCount()
        {
           return Item.Header.Columns.Count; 
        }

        [MethodAttribute("���ص�ǰListView��ѡ�е�����")]
        public int SelectedRowCount()
        {
            return Item.SelectedRows.Count;
        }
	}
}
