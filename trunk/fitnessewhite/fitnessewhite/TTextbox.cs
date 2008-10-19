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
        [MethodAttribute("���м䵥��")]
        public void ClickAtCenter()
        {
            Item.ClickAtCenter();
        }

        [MethodAttribute("���Ҳ��Ե����")]
        public void ClickAtRightEdge()
        {
            Item.ClickAtRightEdge();
        }

        [MethodAttribute("�����ı���Ϣ")]
        public string Text()
        {
            return Item.Text.Trim();
        }
	}
}
