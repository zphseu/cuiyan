/*
 * Created by SharpDevelop.
 * User: cuiyan
 * Date: 2008-6-2
 * Time: 7:28
 */

using System;
using Core.UIItems;
using Core.UIItems.Finders;

namespace fitnessewhite
{
    public class FitUItem<T> : Guifixture
         where T: UIItem
    {
        private UIItem item = null;

        protected T Item
        {
            get { return (T)item; }
            set { item = value;  }
        }

        [MethodAttribute("根据文本获取对象，参数为文本信息")]
        public virtual void GetByText(string value)
        {
            SearchCriteria searchCriteria = SearchCriteria.ByText(value);
            item = uitemcontainer.Get<T>(searchCriteria);
        }

        [MethodAttribute("根据Id获取对象，参数为Id信息")]
        public virtual void GetById(string value)
        {
            SearchCriteria searchCriteria = SearchCriteria.ByAutomationId(value);
            item = uitemcontainer.Get<T>(searchCriteria);
        }

        [MethodAttribute("设置当前对象的值")]
        public virtual void SetText(string value)
        {
            item.SetValue(value);
        }

        [MethodAttribute("设置焦点到当前对象")]
        public virtual void Focus()
        {
            item.Focus();
        }

        [MethodAttribute("根据文本获取当前对象，并设置焦点到当前对象")]
        public virtual void FocusByText(string text)
        {
            GetByText(text);
            Focus();
        }

        [MethodAttribute("根据Id获取当前对象，并设置焦点到当前对象")]
        public virtual void FocusById(string id)
        {
            GetById(id);
            Focus();
        }

        [MethodAttribute("单击当前对象")]
        public virtual void Click()
        {
            item.Click();
        }

        [MethodAttribute("根据文本获取当前对象，并单击当前对象")]
        public virtual void ClickByText(string text)
        {
            GetByText(text);
            Click();
        }

        [MethodAttribute("根据Id获取当前对象，并单击当前对象")]
        public virtual void ClickById(string id)
        {
            GetById(id);
            Click();
        }

        [MethodAttribute("双击当前对象")]
        public virtual void DoubleClick()
        {
            item.DoubleClick();
        }

        [MethodAttribute("根据文本获取当前对象，并双击当前对象")]
        public virtual void DoubleClickByText(string text)
        {
            GetByText(text);
            DoubleClick();
        }

        [MethodAttribute("根据Id获取当前对象，并双击当前对象")]
        public virtual void DoubleClickById(string id)
        {
            GetById(id);
            DoubleClick();
        }

        [MethodAttribute("右键单击当前对象")]
        public virtual void RightClick()
        {
            item.RightClick();
        }

        [MethodAttribute("根据文本获取当前对象，并右键单击当前对象")]
        public virtual void RightClickByText(string text)
        {
            GetByText(text);
            RightClick();
        }

        [MethodAttribute("根据Id获取当前对象，并右键单击当前对象")]
        public virtual void RightClickById(string id)
        {
            GetById(id);
            RightClick();
        }

        [MethodAttribute("返回是否为焦点对象")]
        public virtual bool IsFocussed()
        {
            return item.IsFocussed; 
        }

        [MethodAttribute("返回对象是否发现")]
        public virtual bool IsFound()
        {
            return item != null;
        }

        [MethodAttribute("返回对象名称")]
        public virtual string Name()
        {
            return item.Name.Trim();
        }

        [MethodAttribute("返回对象是否可见")]
        public virtual bool IsVisible()
        {
            return item.Visible;
        }

        [MethodAttribute("返回对象是否有效")]
        public virtual bool IsEnabled()
        {
            return item.Enabled;
        }

        [MethodAttribute("返回对象的Id")]
        public virtual string Id()
        {
            return item.Id.Trim();
        }

        //[System.Runtime.InteropServices.DllImportAttribute("gdi32.dll")]
        //private static extern bool BitBlt(
        //    IntPtr hdcDest, // 目标 DC的句柄
        //    int nXDest,
        //    int nYDest,
        //    int nWidth,
        //    int nHeight,
        //    IntPtr hdcSrc,  // 源DC的句柄
        //    int nXSrc,
        //    int nYSrc,
        //    System.Int32 dwRop  // 光栅的处理数值
        //    );

        //[MethodAttribute("保存对象为图片，参数为文件名")]
        //public void SavePicture(string picname)
        //{
        //    System.Windows.Point point = Item.Location;
        //    System.Windows.Rect wndrect = Item.Bounds;
        //    Rectangle rect = new Rectangle();
        //    rect = Screen.PrimaryScreen.WorkingArea;

        //    Form form = new Form();
        //    Graphics g1 = form.CreateGraphics();

        //    System.Drawing.Image image = new Bitmap(rect.Width, rect.Height, g1);
        //    Graphics g2 = Graphics.FromImage(image);

        //    IntPtr dc1 = g1.GetHdc();
        //    IntPtr dc2 = g2.GetHdc();

        //    BitBlt(dc2, 0, 0, rect.Width, rect.Height, dc1, -(int)point.X, -(int)point.Y, 13369376);

        //    g1.ReleaseHdc(dc1);
        //    g2.ReleaseHdc(dc2);

        //    image.Save(picname, ImageFormat.Bmp);
        //}

        //public virtual string AccessKey()
        //{
        //    return item.AccessKey;
        //}

        //public virtual string Bounds()
        //{
        //    Rect b = item.Bounds;
        //    return string.Format("({0:F2}, {1:F2}, {2:F2}, {3:F2})", b.Left, b.Top, b.Right, b.Bottom);
        //}

        //public virtual string ClickablePoint()
        //{
        //    System.Drawing.Point p = item.ClickablePoint;
        //    return string.Format("({0:F2}, {1:F2})", p.X, p.Y);
        //}

        //public virtual string Framework()
        //{
        //    if (item.Framework.Win32)
        //        return "Win32";
        //    else if (item.Framework.WPF)
        //        return "WPF";
        //    else if (item.Framework.WinForm)
        //        return "WinForm";
        //    else
        //        return "unknown";
        //}

        //public virtual bool IsOffScreen()
        //{
        //    return item.IsOffScreen;
        //}

        //public virtual string Location()
        //{
        //    Point p = item.Location;
        //    return string.Format("({0:F2}, {1:F2})", p.X, p.Y);
        //}

        //public virtual string PrimaryIdentification()
        //{
        //    return item.PrimaryIdentification;
        //}
    }
}
