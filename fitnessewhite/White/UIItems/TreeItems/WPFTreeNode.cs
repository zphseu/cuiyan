using System.Drawing;
using System.Windows.Automation;
using Core.UIItems.Actions;
using Core.UIItems.Finders;

namespace Core.UIItems.TreeItems
{
    [PlatformSpecificItem]
    public class WPFTreeNode : TreeNode
    {
        protected WPFTreeNode() {}
        public WPFTreeNode(AutomationElement automationElement, ActionListener actionListener) : base(automationElement, actionListener) {}

        protected override Point SelectPoint
        {
            get
            {
                System.Windows.Point point = C.ImmediateExteriorEast(GetExpandCollapseButton().Bounds);
                return C.Convert(point);
            }
        }

        protected override void DoExpand()
        {
            GetExpandCollapseButton().Click();
        }

        protected override void DoCollapse()
        {
            GetExpandCollapseButton().Click();
        }

        private Button GetExpandCollapseButton()
        {
            return (Button) factory.Create(SearchCriteria.ByControlType(ControlType.Button), actionListener);
        }
    }
}