using System.Drawing;
using System.Threading;
using Core.Configuration;
using Core.InputDevices;
using Core.Logging;
using Core.UIItems.Actions;

namespace Core.UIItems
{
    //TODO this problem can occur on ListView as well
    internal class TooltipSafeMouse
    {
        private readonly Mouse mouse;

        public TooltipSafeMouse(Mouse mouse)
        {
            this.mouse = mouse;
        }

        public virtual void RightClickOutsideToolTip(UIItem uiItem, ActionListener actionListener)
        {
            actionListener.ActionPerforming(uiItem);
            ToolTip toolTip = GetToolTip(uiItem, actionListener);
            if (toolTip == null)
            {
                //Because mouse has already been moved
                mouse.RightClickHere(actionListener);
            }
            else
            {
                WhiteLogger.Instance.Debug("Found tooltip RightClicking outside tooltip bounds");
                mouse.RightClick(toolTip.LeftOutside(uiItem.Bounds), actionListener);
            }
        }

        public virtual void DoubleClickOutsideToolTip(UIItem uiItem, ActionListener actionListener)
        {
            actionListener.ActionPerforming(uiItem);
            ToolTip toolTip = GetToolTip(uiItem, actionListener);
            if (toolTip == null)
                mouse.DoubleClick(C.Center(uiItem.Bounds), actionListener);
            else
            {
                WhiteLogger.Instance.Debug("Found tooltip DoubleClicking outside tooltip bounds");
                mouse.DoubleClick(toolTip.LeftOutside(uiItem.Bounds), actionListener);
            }
        }

        public virtual void ClickOutsideToolTip(UIItem uiItem, ActionListener actionListener)
        {
            actionListener.ActionPerforming(uiItem);
            ToolTip toolTip = GetToolTip(uiItem, actionListener);
            if (toolTip == null)
                mouse.Click(C.Center(uiItem.Bounds), actionListener);
            else
            {
                WhiteLogger.Instance.Debug("Found tooltip Clicking outside tooltip bounds");
                mouse.Click(toolTip.LeftOutside(uiItem.Bounds), actionListener);
            }
        }

        private ToolTip GetToolTip(UIItem uiItem, ActionListener actionListener)
        {
            Point clickPoint = C.Center(uiItem.Bounds);
            mouse.Click(clickPoint);
            actionListener.ActionPerformed(Action.WindowMessage);
            Thread.Sleep(CoreAppXmlConfiguration.Instance.TooltipWaitTime);
            return ToolTip.GetFrom(clickPoint);
        }
    }
}