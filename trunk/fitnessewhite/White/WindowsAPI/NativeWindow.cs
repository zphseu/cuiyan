using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;

namespace Core.WindowsAPI
{
    public class NativeWindow
    {
        private readonly IntPtr handle;

        [DllImport("user32.dll")]
        private static extern bool GetWindowInfo(IntPtr hwnd, ref WindowInfo windowInfo);

        [DllImport("kernel32", EntryPoint = "GetLastError")]
        private static extern int GetLastError();

        [DllImport("user32.dll")]
        private static extern IntPtr WindowFromPoint(POINT Point);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern int InternalGetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

        [DllImport("user32")]
        [return : MarshalAs(UnmanagedType.Bool)]
        public static extern bool EnumChildWindows(IntPtr window, EnumWindowsProc callback, IntPtr i);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, long wParam, StringBuilder stringBuilder);

        public delegate bool EnumWindowsProc(IntPtr hWnd, StringBuilder lpszString, IntPtr lParam);

        [DllImport("user32.dll")]
        static extern int EnumProps(IntPtr hWnd, EnumWindowsProc lpEnumFunc);

        [DllImport("user32.dll")]
        private static extern IntPtr GetDC(IntPtr hWnd);

        [DllImport("gdi32.dll")]
        private static extern COLORREF GetBkColor(IntPtr hdc);

        [DllImport("gdi32.dll")]
        private static extern COLORREF GetTextColor(IntPtr hdc);

        public NativeWindow(Point point)
        {
            handle = WindowFromPoint(new POINT(point.X, point.Y));
        }

        public NativeWindow(IntPtr handle)
        {
            this.handle = handle;
        }

        public virtual COLORREF BackgroundColor
        {
            get
            {
                return GetBkColor(GetDC(handle));
            }
        }

        public virtual COLORREF TextColor
        {
            get
            {
                return GetTextColor(GetDC(handle));
            }
        }
    }
}