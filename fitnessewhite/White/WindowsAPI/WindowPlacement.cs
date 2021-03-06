using System;
using System.Drawing;
using System.Runtime.InteropServices;

namespace Core.WindowsAPI
{
    /// <summary>
    /// Intended for White Internal use only
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct WindowPlacement
    {
        public uint Length;
        public uint Flags;
        public uint ShowCMD;
        public Point MinmizedPosition;
        public Point MaximizedPosition;
        public Rectangle NormalPosition;
    }

    /// <summary>
    /// Intended for White Internal use only
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct WindowInfo
    {
        public uint size;
        public Rectangle layout;
        public Rectangle clientLayout;
        public uint style;
        public uint exStyle;
        public uint activeStatus;
        public uint borderWidth;
        public uint borderHeight;
        public ushort atom;
        public ushort windowVersion;
    }

    /// <summary>
    /// Intended for White Internal use only
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct MouseInput
    {
        private int dx;
        private int dy;
        private int mouseData;
        private int dwFlags;
        private int time;
        private IntPtr dwExtraInfo;

        public MouseInput(int dwFlags, IntPtr dwExtraInfo)
        {
            this.dwFlags = dwFlags;
            this.dwExtraInfo = dwExtraInfo;
            dx = 0;
            dy = 0;
            time = 0;
            mouseData = 0;
        }
    }

    /// <summary>
    /// Intended for White Internal use only
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct KeyboardInput
    {
        private short wVk;
        private short wScan;
        private KeyUpDown dwFlags;
        private int time;
        private IntPtr dwExtraInfo;

        public KeyboardInput(short wVk, KeyUpDown dwFlags, IntPtr dwExtraInfo)
        {
            this.wVk = wVk;
            wScan = 0;
            this.dwFlags = dwFlags;
            time = 0;
            this.dwExtraInfo = dwExtraInfo;
        }

        public enum KeyUpDown
        {
            KEYEVENTF_KEYDOWN = 0x0000,
            KEYEVENTF_EXTENDEDKEY = 0x0001,
            KEYEVENTF_KEYUP = 0x0002,
        }

        public enum SpecialKeys
        {
            //http://pinvoke.net/default.aspx/user32/SendInput.html, http://delphi.about.com/od/objectpascalide/l/blvkc.htm
            SHIFT = 0x10,
            CONTROL = 0x11,
            ALT = 0x12,
            LEFT_ALT = 0xA4,
            RIGHT_ALT = 0xA5,
            RETURN = 0x0D,
            RIGHT = 0x27,
            BACKSPACE = 0x08,
            LEFT = 0x25,
            ESCAPE = 0x1B,
            TAB = 0x09,
            HOME = 0x24,
            END = 0x23,
            UP = 0x26,
            DOWN = 0x28,
            INSERT = 0x2D,
            DELETE = 0x2E,
            CAPS = 0x14,
            F1 = 0x70,
            F2 = 0x71,
            F3 = 0x72,
            F4 = 0x73,
            F5 = 0x74,
            F6 = 0x75,
            F7 = 0x76,
            F8 = 0x77,
            F9 = 0x78,
            F10 = 0x79,
            F11 = 0x7A,
            F12 = 0x7B,
            PAGEUP = 0x21,
            PAGEDOWN = 0x22,
            PRINT = 0x2A,
            PRINTSCREEN = 0x2C
        }
    }

    /// <summary>
    /// Intended for White Internal use only
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct HardwareInput
    {
        private int uMsg;
        private short wParamL;
        private short wParamH;
    }

    /// <summary>
    /// Intended for White Internal use only
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct CursorInfo
    {
        public uint size;
        public uint flags;
        public IntPtr handle;
        public Point point;

        public static CursorInfo New()
        {
            CursorInfo info = new CursorInfo();
            info.size = (uint) Marshal.SizeOf(typeof (CursorInfo));
            return info;
        }
    }

    /// <summary>
    /// Intended for White Internal use only
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct POINT
    {
        public int X;
        public int Y;

        public POINT(int x, int y)
        {
            X = x;
            Y = y;
        }
    }

    /// <summary>
    /// Intended for White Internal use only
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct COLORREF
    {
        public byte R;
        public byte G;
        public byte B;

        public override string ToString()
        {
            return string.Format("R={0},G={1},B={2}", R, G, B);
        }
    }
}