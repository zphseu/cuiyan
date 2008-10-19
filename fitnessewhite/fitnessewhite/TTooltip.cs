/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 9:38
 */

using Core.UIItems;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.ToolTip.
    /// </summary>
    public sealed class TTooltip : FitUItem<ToolTip>
    {
        [MethodAttribute("返回文本信息")]
        public string Text()
        {
            return Item.Text.Trim();
        }
    }
}
