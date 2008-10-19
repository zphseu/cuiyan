/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-5-30
 * Time: 9:51
 */
using System;
using Core.Factory;
using Core.UIItems.WindowStripControls;

namespace fitnessewhite
{
	/// <summary>
	/// Description of WhiteStatusBar.
	/// </summary>
    public sealed class TStatusStrip : FitUItem<StatusStrip>
	{
        [MethodAttribute("获取当前窗口的StatusStrip")]
        public void Get() 
        {
            Item = mainwin.StatusBar(InitializeOption.NoCache);
        }	
	}
}
