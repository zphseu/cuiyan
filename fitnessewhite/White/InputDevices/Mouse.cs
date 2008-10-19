using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Threading;
using Core.Configuration;
using Core.Logging;
using Core.UIItems;
using Core.UIItems.Actions;
using Core.WindowsAPI;

namespace Core.InputDevices
{
    public class Mouse : IMouse
    {
        [DllImport("user32", EntryPoint = "SendInput")]
        private static extern int SendInput(int numberOfInputs, ref Input input, int structSize);

        [DllImport("kernel32", EntryPoint = "GetLastError")]
        private static extern int GetLastError();

        [DllImport("user32.dll")]
        private static extern IntPtr GetMessageExtraInfo();

        [DllImport("user32.dll")]
        private static extern IntPtr GetCursor();

        [DllImport("user32.dll")]
        private static extern bool GetCursorPos(ref Point cursorInfo);

        [DllImport("user32.dll")]
        private static extern bool SetCursorPos(Point cursorInfo);

        [DllImport("user32.dll")]
        private static extern bool GetCursorInfo(ref CursorInfo cursorInfo);

        [DllImport("user32.dll")]
        private static extern short GetDoubleClickTime();

        public static Mouse Instance = new Mouse();
        private DateTime lastClickTime = DateTime.Now;
        private readonly short doubleClickTime = GetDoubleClickTime();
        private Point lastClickLocation;
        private const int extraMillisecondsBecauseOfBugInWindows = 13;

        private Mouse() {}

        public virtual Point Location
        {
            get
            {
                Point point = new Point();
                GetCursorPos(ref point);
                return point;
            }
            set { SetCursorPos(value); }
        }

        public virtual MouseCursor Cursor
        {
            get
            {
                CursorInfo cursorInfo = CursorInfo.New();
                GetCursorInfo(ref cursorInfo);
                int i = cursorInfo.handle.ToInt32();
                return (MouseCursor) Enum.ToObject(typeof (MouseCursor), i);
            }
        }

        public virtual void RightClick()
        {
            SendInput(Input.Mouse(MouseInput(WindowsConstants.MOUSEEVENTF_RIGHTDOWN)));
            SendInput(Input.Mouse(MouseInput(WindowsConstants.MOUSEEVENTF_RIGHTUP)));
        }

        public virtual void Click()
        {
            Point clickLocation = Location;
            if (lastClickLocation.Equals(clickLocation))
            {
                int timeout = doubleClickTime - DateTime.Now.Subtract(lastClickTime).Milliseconds;
                if (timeout > 0) Thread.Sleep(timeout + extraMillisecondsBecauseOfBugInWindows);
            }
            MouseLeftButtonUpAndDown();
            lastClickTime = DateTime.Now;
            lastClickLocation = Location;
        }

        public static void LeftUp()
        {
            SendInput(Input.Mouse(MouseInput(WindowsConstants.MOUSEEVENTF_LEFTUP)));
        }

        public static void LeftDown()
        {
            SendInput(Input.Mouse(MouseInput(WindowsConstants.MOUSEEVENTF_LEFTDOWN)));
        }

        public virtual void DoubleClick(Point point)
        {
            DoubleClick(point, new NullActionListener());
        }

        public virtual void DoubleClick(Point point, ActionListener actionListener)
        {
            Location = point;
            MouseLeftButtonUpAndDown();
            MouseLeftButtonUpAndDown();
            ActionPerformed(actionListener);
        }

        private static void SendInput(Input input)
        {
            SendInput(1, ref input, Marshal.SizeOf(typeof (Input)));
        }

        private static MouseInput MouseInput(int command)
        {
            return new MouseInput(command, GetMessageExtraInfo());
        }

        public virtual void RightClick(Point point, ActionListener actionListener)
        {
            Location = point;
            RightClickHere(actionListener);
        }

        public virtual void RightClick(Point point)
        {
            RightClick(point, new NullActionListener());
        }

        internal virtual void RightClickHere(ActionListener actionListener)
        {
            RightClick();
            actionListener.ActionPerformed(Action.WindowMessage);
        }

        public virtual void Click(Point point)
        {
            Click(point, new NullActionListener());
        }

        public virtual void Click(Point point, ActionListener actionListener)
        {
            Location = point;
            Click();
            ActionPerformed(actionListener);
        }

        private static void ActionPerformed(ActionListener actionListener)
        {
            actionListener.ActionPerformed(new Action(ActionType.WindowMessage));
        }

        //Doc: DragStepCount
        /// <summary>
        /// Drags the dragged item and drops it on the drop item. This can be used for any two UIItems
        /// whether they are same application or different. To drop items on desktop use Desktop 
        /// class's Drop method.
        /// Some drag and drop operation need to wait for application to process something while item is being dragged.
        /// This can be set but configuring DragStepCount property. This is by default set to 1.
        /// </summary>
        /// <param name="draggedItem"></param>
        /// <param name="dropItem"></param>
        public virtual void DragAndDrop(IUIItem draggedItem, IUIItem dropItem)
        {
            Point startPosition = C.Center(draggedItem.Bounds);
            Point endPosition = C.Center(dropItem.Bounds);

            Location = startPosition;
            LeftDown();
            LeftUp();
            LeftDown();
            draggedItem.ActionPerformed(Action.WindowMessage);
            float dragStepFraction = (float) (1.0/CoreAppXmlConfiguration.Instance.DragStepCount);
            WhiteLogger.Instance.Info(CoreAppXmlConfiguration.Instance.DragStepCount + ":" + dragStepFraction);
            for (int i = 1; i <= CoreAppXmlConfiguration.Instance.DragStepCount; i++)
            {
                double newX = startPosition.X + (endPosition.X - startPosition.X)*(dragStepFraction*i);
                double newY = startPosition.Y + (endPosition.Y - startPosition.Y)*(dragStepFraction*i);
                Point newPoint = new Point((int) newX, (int) newY);
                Location = newPoint;
                draggedItem.ActionPerformed(Action.WindowMessage);
            }
            LeftUp();
            dropItem.ActionPerformed(Action.WindowMessage);
        }

        public static void MouseLeftButtonUpAndDown()
        {
            LeftDown();
            LeftUp();
        }

        public virtual void MoveOut()
        {
            Location = new Point(0, 0);
        }
    }
}