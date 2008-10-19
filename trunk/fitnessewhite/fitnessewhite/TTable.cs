/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 9:54
 */

using Core.UIItems;
using Core.UIItems.TableItems;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.Table.
    /// </summary>
    public sealed class TTable : FitUItem<Table>
    {
        [MethodAttribute("根据文本获取Table，参数为文本信息")]
        public override void GetByText(string value)
        {
            base.GetByText(value);
            table = Item;
        }

        [MethodAttribute("根据Id获取Table，参数为文本信息")]
        public override void GetById(string value)
        {
            base.GetById(value);
            table = Item;
        }
    
        [MethodAttribute("刷新当前Table")]
        public void Refresh()
        {
            Item.Refresh();
        }

        [MethodAttribute("单击当前Table的列标签，参数是从0开始的列序号")]
        public void ClickColumnHeader(int index)
        {
            Item.Header.Columns[index].Click();
        }

        [MethodAttribute("单击当前Table的列标签，参数是从0开始的列序号")]
        public void ClickRowHeader(int index)
        {
        	Item.Rows[index].Click();
        }

        [MethodAttribute("返回当前Table的行数")]
        public int RowCount()
        {
            return Item.Rows.Count;
        }

        [MethodAttribute("返回当前Table的列数")]
        public int ColumnCount()
        {
            return Item.Header.Columns.Count;
        }
    }
}
