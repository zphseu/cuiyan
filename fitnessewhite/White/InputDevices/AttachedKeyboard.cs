using Core.UIItems.WindowItems;
using Core.WindowsAPI;

namespace Core.InputDevices
{
    /// <summary>
    /// Any operation performed using the keyboard would wait till the window is busy after this operation. Before any operation is 
    /// performed the window, from which it was retreived, is brought to focus if it is not.
    /// </summary>
    public class AttachedKeyboard : IKeyboard
    {
        private readonly Window window;
        private readonly Keyboard keyboard;

        internal AttachedKeyboard(Window window, Keyboard keyboard)
        {
            this.window = window;
            this.keyboard = keyboard;
        }

        public virtual void Enter(string keysToType)
        {
            window.Focus();
            keyboard.Send(keysToType, window);
        }

        public virtual void PressSpecialKey(KeyboardInput.SpecialKeys key)
        {
            window.Focus();
            keyboard.PressSpecialKey(key, window);
        }

        public virtual void HoldKey(KeyboardInput.SpecialKeys key)
        {
            window.Focus();
            keyboard.HoldKey(key, window);
        }

        public virtual void LeaveKey(KeyboardInput.SpecialKeys key)
        {
            window.Focus();
            keyboard.LeaveKey(key, window);
        }

        public virtual bool CapsLockOn
        {
            get { return keyboard.CapsLockOn; }
            set
            {
                window.Focus();
                keyboard.CapsLockOn = value;
            }
        }
    }
}