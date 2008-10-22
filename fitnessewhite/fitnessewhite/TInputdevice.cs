/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 10:54
 */
using System;
using Core.InputDevices;
using Core.WindowsAPI;
using System.Threading;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.Mouse.
    /// </summary>
    public sealed class TInputdevice : Guifixture
    {
        private string keys;
        private int delayMiSec;
        private Thread thread;

        [MethodAttribute("输入字符串")]
        static private void Enter(string keysToType)
        {
            mainwin.Keyboard.Enter(keysToType);
        }
        
        [MethodAttribute("依据AutoItX的Send格式输入字符串，" + 
                         "这个方式需要注册AutoItX3.DLL，AutoItX可以在" + 
                         "http://www.autoitscript.com/autoit3/下载")]
        static public void EnterWithAutoItX(string keysToType)
        {
        	AutoItX3Lib.AutoItX3 autoitx = new AutoItX3Lib.AutoItX3Class();
        	autoitx.Send(keysToType,0);
        }

        [MethodAttribute("开启一个独立线程，延时指定毫秒发送出，依据AutoItX的Send格式输入字符串，" +
                         "这个方式需要注册AutoItX3.DLL，AutoItX可以在" +
                         "http://www.autoitscript.com/autoit3/下载。参数格式为：keysToType;miSec。" +
                         "如果keysToType中有;，用[@@]代替")]
        public void ThreadEnterWithAutoItX(string keysToType)
        {
            string[] items = SplitString(keysToType);
            if (items.Length < 2) return;
            keys = items[0].Replace("@@", ";");
            delayMiSec = int.Parse(items[1]);
            thread = new Thread(new ThreadStart(this.ThreadProcessEnterWithAutoItX));
            thread.Start();
        }

        private void ThreadProcessEnterWithAutoItX()
        {
            Thread.Sleep(delayMiSec);
            EnterWithAutoItX(keys);
            thread.Abort();
        }

        [MethodAttribute("输入一个特殊键，包括SHIFT, CONTROL, ALT, LEFT_ALT, " + 
                         "RIGHT_ALT, RETURN, RIGHT, BACKSPACE, LEFT, ESCAPE, " +
                         "TAB, HOME, END, UP, DOWN, INSERT, DELETE, CAPS, F1-F12")]
        static private void PressSpecialKey(string key)
        {
        	mainwin.Keyboard.PressSpecialKey(SpecialKey(key));
        }

        [MethodAttribute("保持按住一个特殊键，包括SHIFT, CONTROL, ALT, LEFT_ALT, " + 
                         "RIGHT_ALT, RETURN, RIGHT, BACKSPACE, LEFT, ESCAPE, " +
                         "TAB, HOME, END, UP, DOWN, INSERT, DELETE, CAPS, F1-F12")]
        static private void HoldKey(string key)
        {
            mainwin.Keyboard.HoldKey(SpecialKey(key));
        }

        [MethodAttribute("释放之前按下的特殊键，包括SHIFT, CONTROL, ALT, LEFT_ALT, " + 
                         "RIGHT_ALT, RETURN, RIGHT, BACKSPACE, LEFT, ESCAPE, " +
                         "TAB, HOME, END, UP, DOWN, INSERT, DELETE, CAPS, F1-F12")]
        static private void LeaveKey(string key)
        {
            mainwin.Keyboard.LeaveKey(SpecialKey(key));
        }

        [MethodAttribute("在当前位置点击")]
        static public void Click()
        {
            mainwin.Mouse.Click();
        }

        [MethodAttribute("在指定位置点击，位置格式为 \"(int, int)\"")]
        static public void ClickAt(string location)
        {
            Location = location;
            mainwin.Mouse.Click();
        }

        [MethodAttribute("在指定位置双击，位置格式为 \"(int, int)\"")]
        static public void DoubleClickAt(string location)
        {
            Location = location;
            mainwin.Mouse.DoubleClick(Mouse.Instance.Location);
        }

        [MethodAttribute("在当前位置右键单击")]
        static public void RightClick()
        {
            mainwin.Mouse.RightClick();
        }

        [MethodAttribute("在指定位置右键单击，位置格式为 \"(int, int)\"")]
        static public void RightClickAt(string location)
        {
            Location = location;
            mainwin.Mouse.RightClick();
        }

        private static string Location
        {
            get
            {
                System.Drawing.Point xy = Mouse.Instance.Location;
                return string.Format("({0:F2}, {1:F2})", xy.X, xy.Y);
            }
            set
            {
                string[] items = SplitString(value);
                if (items.Length > 1)
                {
                    System.Drawing.Point xy = Mouse.Instance.Location;
                    xy.X = int.Parse(items[0]);
                    xy.Y = int.Parse(items[1]);
                }
                else
                    throw new ArgumentException("param format: x;y");		
            }
        }

        [MethodAttribute("返回指针状态，为Pointer、Wait、DefaultAndWait、IShapedCursor和unknown")]
        public static string Cursor()
        {
            switch(Mouse.Instance.Cursor)
            {
                case MouseCursor.Pointer:
                    return "Pointer";
                case MouseCursor.Wait:
                    return "Wait";
                case MouseCursor.DefaultAndWait:
                    return "DefaultAndWait";
                case MouseCursor.IShapedCursor:
                    return "IShapedCursor";
                default:
                    return "unknown";
            }
        }
        
        static private KeyboardInput.SpecialKeys SpecialKey(string s)
        {
        	switch(s)
        	{
        		case "SHIFT" :
        			return KeyboardInput.SpecialKeys.SHIFT;
        		case "CONTROL" :
        			return KeyboardInput.SpecialKeys.CONTROL;
        		case "ALT" :
        			return KeyboardInput.SpecialKeys.ALT;
        		case "LEFT_ALT" :
        			return KeyboardInput.SpecialKeys.LEFT_ALT;
        		case "RIGHT_ALT" :
        			return KeyboardInput.SpecialKeys.RIGHT_ALT;
        		case "RETURN" :
        			return KeyboardInput.SpecialKeys.RETURN;
        		case "RIGHT" :
        			return KeyboardInput.SpecialKeys.RIGHT;
        		case "BACKSPACE" :
        			return KeyboardInput.SpecialKeys.BACKSPACE;
        		case "LEFT" :
        			return KeyboardInput.SpecialKeys.LEFT;      			
        		case "ESCAPE" :
        			return KeyboardInput.SpecialKeys.ESCAPE;        			
        		case "TAB" :
        			return KeyboardInput.SpecialKeys.TAB;
        		case "HOME" :
        			return KeyboardInput.SpecialKeys.HOME;
        		case "END" :
        			return KeyboardInput.SpecialKeys.END;
        		case "UP" :
        			return KeyboardInput.SpecialKeys.UP;
        		case "DOWN" :
        			return KeyboardInput.SpecialKeys.DOWN;
        		case "INSERT" :
        			return KeyboardInput.SpecialKeys.INSERT;
        		case "DELETE" :
        			return KeyboardInput.SpecialKeys.DELETE;
        		case "CAPS" :
        			return KeyboardInput.SpecialKeys.CAPS;
        		case "F1" :
        			return KeyboardInput.SpecialKeys.F1;
        		case "F2" :
        			return KeyboardInput.SpecialKeys.F2;
        		case "F3" :
        			return KeyboardInput.SpecialKeys.F3;
        		case "F4" :
        			return KeyboardInput.SpecialKeys.F4;
        		case "F5" :
        			return KeyboardInput.SpecialKeys.F5;
        		case "F6" :
        			return KeyboardInput.SpecialKeys.F6;
        		case "F7" :
        			return KeyboardInput.SpecialKeys.F7;
        		case "F8" :
        			return KeyboardInput.SpecialKeys.F8;
        		case "F9" :
        			return KeyboardInput.SpecialKeys.F9;
        		case "F10" :
        			return KeyboardInput.SpecialKeys.F10;
        		case "F11" :
        			return KeyboardInput.SpecialKeys.F11;
        		case "F12" :
        			return KeyboardInput.SpecialKeys.F12;
        		default:
        			return KeyboardInput.SpecialKeys.F12;
        	}
        }
    }
}
