/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 10:29
 */

using System;
using Core.UIItems.TreeItems;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.ListViewCell.
    /// </summary>
    public sealed class TTreenode : FitUItem<TreeNode>
    {
        [MethodAttribute("从当前Tree中根据路径获取当前节点对象，格式为\"nodetext1;nodetext2;nodetext3;...\"")]	
        public void GetByPath(string path)
        {
            string[] nodePath = SplitString(path);
            Item = tree.Node(nodePath);           
        }

        [MethodAttribute("合闭当前节点")]
        public void Collapse()
        {
            Item.Collapse();
        }

        [MethodAttribute("从当前Tree中根据路径获取当前节点对象，并合闭")]
        public void CollapseByPath(string path)
        {
            GetByPath(path);
            Item.Collapse();
        }

        [MethodAttribute("展开当前节点")]
        public void Expand()
        {
            Item.Expand();
        }

        [MethodAttribute("从当前Tree中根据路径获取当前节点对象，并展开")]
        public void ExpandByPath(string path)
        {
            GetByPath(path);
            Item.Expand();
        }

        [MethodAttribute("选中当前节点")]
        public void Select()
        {
            Item.Select();
        }

        [MethodAttribute("从当前Tree中根据路径获取当前节点对象，并选中")]
        public void SelectByPath(string path)
        {
            GetByPath(path);
            Item.Select();
        }

        [MethodAttribute("返回当前节点是否被选中")]
        public bool IsSelected()
        {
             return Item.IsSelected;
        }

        [MethodAttribute("返回当前节点的文本信息")]
        public string Text()
        {
            return Item.Text.Trim();
        }
    }
}
