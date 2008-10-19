/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 10:28
 */

using Core.UIItems;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.TextBox.
	/// </summary>
    public sealed class TTextbox : FitUItem<TextBox>
	{
        [MethodAttribute("在中间单击")]
        public void ClickAtCenter()
        {
            Item.ClickAtCenter();
        }

        [MethodAttribute("在右侧边缘单击")]
        public void ClickAtRightEdge()
        {
            Item.ClickAtRightEdge();
        }

        [MethodAttribute("返回文本信息")]
        public string Text()
        {
            return Item.Text.Trim();
        }
	}
}
