/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 10:56
 */

using Core.UIItems.TabItems;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.Tab.
    /// </summary>
    public sealed class TTab : FitUItem<Tab>
    {
        [MethodAttribute("选中Title的Tab页")]
        public void SelectByTitle(string title)
        {
            Item.SelectTabPage(title);
        }

        [MethodAttribute("选中从0开始序号的Tab页")]
        public void SelectByIndex(int index)
        {
            Item.SelectTabPage(index);
        }

        [MethodAttribute("返回被选中的Tab页的名称")]
        public string SelectedTabName()
        {
            return Item.SelectedTab.Name;
        }

        [MethodAttribute("返回Tab页的个数")]
        public int TabCount()
        {
            return Item.TabCount;
        }

        [MethodAttribute("返回所有Tab页的名称，中间以 ; 间隔")]
        public string Pages()
        {
            string snames = "";
            foreach (TabPage tp in Item.Pages)
            {
                snames += tp.Name + ';';
            }
            snames = snames.TrimEnd(';');

            return snames;
        }
    }
}