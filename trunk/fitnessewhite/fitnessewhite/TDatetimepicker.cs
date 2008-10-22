/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 9:39
 */

using System;
using System.Globalization;
using Core.UIItems;
using Core.InputDevices;
using Core.WindowsAPI;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.DateTimePicker.
    /// </summary>
    public sealed class TDatetimepicker : FitUItem<DateTimePicker>
    {
        [MethodAttribute("返回当前设定的时间，格式为2008-10-10")]
        public string GetDate()
        {
            if (Item.Framework.Win32)
                throw new Core.WhiteAssertionException("//cycy，在Win32下可以获取得对象，但是对象没有Date属性。因此读取要单独编程，如窗口MESSAGE方式。");
            return String.Format("{0:d4}-{1:d2}-{2:d2}", Item.Date.Year, Item.Date.Month, Item.Date.Day);
        }

        [MethodAttribute("根据给定字串设定时间，格式为2008-10-10")]
        public void SetDate(string value)
        {
            Item.SetDate(DateTime.Parse(value), DateFormat.YearMonthDay);
            Item.KeyIn(KeyboardInput.SpecialKeys.RIGHT); //回到第一个位置，确保再次输入时从头开始
        }

        [MethodAttribute("返回当前设定的时间，格式为2008-10-10 14:25:28")]
        public string GetDateTime()
        {
            if (Item.Framework.Win32)
                throw new Core.WhiteAssertionException("//cycy，在Win32下可以获取得对象，但是对象没有Date属性。因此读取要单独编程，如窗口MESSAGE方式。");
            return String.Format("{0:d4}-{1:d2}-{2:d2} {3:d2}:{4:d2}:{5:d2}", Item.Date.Year,
                    Item.Date.Month, Item.Date.Day, Item.Date.Hour, Item.Date.Minute, Item.Date.Second);
        }

        [MethodAttribute("根据给定字串设定时间，格式为2008-10-10 14:25:28")]
        public void SetDateTime(string value)
        {
            Keyboard keyboard = Keyboard.Instance;
            DateTime dateTime = DateTime.Parse(value, new CultureInfo("zh-cn",true));
            keyboard.Enter(dateTime.Year.ToString());
            Item.KeyIn(KeyboardInput.SpecialKeys.RIGHT);
            keyboard.Enter(dateTime.Month.ToString());
            Item.KeyIn(KeyboardInput.SpecialKeys.RIGHT);
            keyboard.Enter(dateTime.Day.ToString());
            Item.KeyIn(KeyboardInput.SpecialKeys.RIGHT);
            keyboard.Enter(dateTime.Hour.ToString());
            Item.KeyIn(KeyboardInput.SpecialKeys.RIGHT);
            keyboard.Enter(dateTime.Minute.ToString());
            Item.KeyIn(KeyboardInput.SpecialKeys.RIGHT);
            keyboard.Enter(dateTime.Second.ToString());
            Item.KeyIn(KeyboardInput.SpecialKeys.RIGHT);//回到第一个位置，确保再次输入时从头开始
        }
    }
}
