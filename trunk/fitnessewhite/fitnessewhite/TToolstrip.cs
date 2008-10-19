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
        [MethodAttribute("����Id��ȡ��ǰ���ڵ�ToolStrip������ΪId��Ϣ")]
        public void GetById2(string identification)
        {
            Item = mainwin.GetToolStrip(identification);
        }

        [MethodAttribute("��ȡ��ǰ���ڵ�ToolStrip")]
        public void Get()
        {
            Item = mainwin.ToolStrip;
        }   
	}
}
