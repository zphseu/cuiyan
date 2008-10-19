/*
 * Created by SharpDevelop.
 * User: Administrator
 * Date: 2008-9-28
 * Time: 13:04
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using Core;
using Core.Factory;
using Core.UIItems;
using Core.UIItems.Finders;
using Core.UIItems.WindowItems;
using fit;

namespace fitnessewhite
{
	/// <summary>
	/// Description of TIcvConfig.
	/// </summary>
	public class TConfig : Guifixture
	{
        protected string[] SplitBySemicolon(string value)
        {
            return value.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
        }
        
        [MethodAttribute("登陆。参数为:IP;IP;USR;PWD")]
        public void Login(string name)
        {
        	application = Application.Attach("VFC2000");
        	if (application == null)
        		throw new ArgumentException("application can not be attached!");
            string[] items = SplitBySemicolon(name);
            if (items.Length < 4)
                throw new ArgumentException("param format: IP;IP;USR;PWD");
            
            List<Window> wins = application.GetWindows();            
            Window mainWinTmp = null;
            foreach (Window w in wins)
            {
                if (w.Name.Trim().StartsWith("一体化监控指挥平台"))
                {
                	mainWinTmp = w;
                }
                else if (w.Name.Trim().StartsWith("集中配置登录界面"))
                {
                	mainwin = w;
                	uitemcontainer = mainwin;
                }
            }
            
            if (mainWinTmp == null)
            	throw new ArgumentException("MainWindow can not be found!");
            
            if (mainwin == null)
            	throw new ArgumentException("LoginWindow can not be found!");
            
            doCmd("Combobox", "FocusById", "1004"); //配置服务节点
            doCmd("Inputdevice", "Enter", "127.0.0.1");
            doCmd("Combobox", "FocusById", "1005"); //权限服务节点
            doCmd("Inputdevice", "Enter", "127.0.0.1");
            doCmd("Textbox", "FocusById", "10082");
            doCmd("Inputdevice", "Enter", "admin");
            doCmd("Textbox", "FocusById", "1002");
            doCmd("Inputdevice", "Enter", "admin");
            doCmd("Button", "ClickByText", "确定");
            mainwin = mainWinTmp;
           	uitemcontainer = mainwin;
        }
	}
}
