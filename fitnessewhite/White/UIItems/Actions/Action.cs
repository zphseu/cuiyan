using System.Collections.Generic;
using Bricks.Core;
using Core.Configuration;
using Core.InputDevices;
using Core.UIItems.WindowItems;

namespace Core.UIItems.Actions
{
    public class Action
    {
        private readonly List<ActionType> types = new List<ActionType>();
        private readonly List<MouseCursor> waitCursors = new List<MouseCursor>();

        public Action(params ActionType[] actionTypes)
        {
            types.AddRange(actionTypes);

            waitCursors.Add(MouseCursor.DefaultAndWait);
            waitCursors.Add(MouseCursor.Wait);
        }

        public virtual void Handle(Window window)
        {
            window.WaitWhileBusy();
            if (CoreAppXmlConfiguration.Instance.WaitBasedOnHourGlass)
            {
                Clock.Do @do = delegate { return Mouse.Instance.Cursor; };
                Clock.Matched matched = delegate(object obj)
                                            {
                                                MouseCursor cursor = (MouseCursor) obj;
                                                if (waitCursors.Contains(cursor))
                                                {
                                                    Mouse.Instance.MoveOut();
                                                    return false;
                                                }
                                                return true;
                                            };
                Clock.Expired expired =
                    delegate { throw new UIActionException("Window in still wait mode. Cursor: " + Mouse.Instance.Cursor + Constants.BusyMessage); };
                new Clock(CoreAppXmlConfiguration.Instance.BusyTimeout).Perform(@do, matched, expired);
            }
            if (types.Contains(ActionType.NewControls)) window.ReloadIfCached();
        }

        public static readonly Action WindowMessage = new Action(ActionType.WindowMessage);
    }
}