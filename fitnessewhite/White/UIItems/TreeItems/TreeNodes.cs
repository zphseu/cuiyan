using System.Collections.Generic;
using System.Windows.Automation;
using Core.AutomationElementSearch;
using Core.Factory;
using Core.UIItems.Actions;

namespace Core.UIItems.TreeItems
{
    public class TreeNodes : UIItemList<TreeNode>
    {
        public TreeNodes(AutomationElementFinder finder, ActionListener actionListener)
            : base(finder.Children(AutomationSearchCondition.ByControlType(ControlType.TreeItem)), actionListener) {}

        /// <summary>
        /// Gets the TreeNode matching the path. If multi-level find is specified in arguments then in process of finding the TreeNode it would also expand the TreeNodes.
        /// </summary>
        /// <param name="path">e.g. when arguments are ("Parent", "Child", "GrandChild") it would return the TreeNode "GrandChild" which is under "Child", which 
        /// in turn is under "Parent", root node. To get the "Parent" node one needs to just specify ("Parent") as argument.</param>
        /// <returns>true if it finds such node, false otherwise</returns>
        public virtual TreeNode GetItem(params string[] path)
        {
            List<string> nodePath = new List<string>(path);
            if (nodePath.Count == 0) return null;

            string nodeText = nodePath[0];
            TreeNode node = Find(delegate(TreeNode uiItem) { return uiItem.Name.Equals(nodeText); });
            nodePath.RemoveAt(0);
            if (nodePath.Count == 0) return node;
            if (node == null) throw new UIItemSearchException("Could not find node " + nodeText);
            node.Expand();
            return node.GetItem(nodePath.ToArray());
        }

        public virtual List<TreeNode> GetPathTo(TreeNode treeNode)
        {
            List<TreeNode> nodePath = new List<TreeNode>();
            Path(treeNode, nodePath);
            return nodePath;
        }

        private bool Path(TreeNode treeNode, List<TreeNode> treeNodes)
        {
            bool pathFound = false;
            foreach (TreeNode currentNode in this)
            {
                if (currentNode.Equals(treeNode))
                {
                    treeNodes.Add(currentNode);
                    return true;
                }
                else
                {
                    treeNodes.Add(currentNode);
                    pathFound = currentNode.Nodes.Path(treeNode, treeNodes);
                    if (pathFound) return true;
                    else treeNodes.Remove(currentNode);
                }
            }
            return pathFound;
        }

        public virtual void Visit(TreeNodeVisitor visitor)
        {
            foreach (TreeNode treeNode in this)
                treeNode.Visit(visitor);
        }
    }
}