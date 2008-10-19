/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-3
 * Time: 9:39
 */

using System;
using Core.UIItems;

namespace fitnessewhite
{
    /// <summary>
    /// Description of White.DateTimePicker.
    /// </summary>
    public sealed class TDatetimepicker : FitUItem<DateTimePicker>
    {
        private DateTime Date
        {
            get { return Item.Date; }
        }

        private void SetDateTime(DateTime dt)
        {
            Item.SetDate(dt, DateFormat.CultureDefault);
        }

        [MethodAttribute("返回当前设定的时间，格式为？？？")]
        public string DateTimeString()
        {
            return Item.Date.ToString(); 
        }

        [MethodAttribute("根据给定字串设定时间，格式为？？？")]
        public void SetDate(string value)
        {
            SetDateTime(DateTime.Parse(value));
        }
    }
}
