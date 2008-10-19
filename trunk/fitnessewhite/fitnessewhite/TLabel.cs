/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 10:28
 */

using Core.UIItems;

namespace fitnessewhite
{
    public sealed class TLabel : FitUItem<Label>
	{
        [MethodAttribute("返回文本信息")]
        public string Text()
        {
			return Item.Text.Trim();
		}		
	}
}
