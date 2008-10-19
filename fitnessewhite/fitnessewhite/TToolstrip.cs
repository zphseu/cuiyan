/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 9:35
 */

using System;
using Core.UIItems.WindowStripControls;

namespace fitnessewhite
{
	/// <summary>
	/// Description of White.ToolStrip.
	/// </summary>
    public sealed class TToolstrip : FitUItem<ToolStrip>
	{
        [MethodAttribute("根据Id获取当前窗口的ToolStrip，参数为Id信息")]
        public void GetById2(string identification)
        {
            Item = mainwin.GetToolStrip(identification);
        }

        [MethodAttribute("获取当前窗口的ToolStrip")]
        public void Get()
        {
            Item = mainwin.ToolStrip;
        }   
	}
}
