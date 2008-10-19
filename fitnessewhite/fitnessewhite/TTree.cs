/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 10:08
 */

using Core.UIItems.TreeItems;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.Tree.
    /// </summary>
    public sealed class TTree : FitUItem<Tree>
    {
        [MethodAttribute("根据文本获取对象，参数为文本信息")]
        public override void GetByText(string value)
        {
            base.GetByText(value);
            tree = Item;
        }

        [MethodAttribute("根据Id获取对象，参数为Id信息")]
        public override void GetById(string value)
        {
            base.GetById(value);
            tree = Item;
        }

        [MethodAttribute("设置Tree中可编辑节点的值")]
        public override void SetText(string value)
        {
            Item.EditableNodeText = value;
        }
    }
}
