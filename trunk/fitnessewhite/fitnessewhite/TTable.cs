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
        [MethodAttribute("刷新当前Table")]
        public void Refresh()
        {
            Item.Refresh();
        }

        [MethodAttribute("单击当前Table的列标签，参数是从0开始的列序号")]
        public void ClickHeader(int index)
        {
            Item.Header.Columns[index].Click();
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
