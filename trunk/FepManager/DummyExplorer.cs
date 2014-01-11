using System;
using System.Data;
using System.Data.SQLite;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;

namespace FepManager
{
    internal partial class DummyExplorer : DummyBase
    {
        private String sProject = "���� ";

        private TreeNode treeNodeProject;
        private TreeNode treeNodeDriverCfg;
        private TreeNode treeNodeChannelCfg;
        private TreeNode treeNodeTagCfg;
        private TreeNode treeNodeAuthCfg;

        public DummyExplorer()
        {
            InitializeComponent();
        }

        protected override void OnRightToLeftLayoutChanged(EventArgs e)
        {
            treeView.RightToLeftLayout = RightToLeftLayout;
        }

        private void DummyExplorer_Load(object sender, EventArgs e)
        {
            treeNodeDriverCfg = new TreeNode("����", 4, 4);
            treeNodeChannelCfg = new TreeNode("ͨ��", 2, 1);
            treeNodeTagCfg = new TreeNode("�ڵ�", 8, 8);
            treeNodeAuthCfg = new TreeNode("��Ȩ", 7, 7);
            treeNodeProject = new TreeNode("����", 0, 0, new TreeNode[] {
                    new TreeNode("������Ϣ", 3, 3, new TreeNode[] { treeNodeDriverCfg, treeNodeTagCfg, treeNodeChannelCfg, treeNodeAuthCfg }), 
                    new TreeNode("������Ϣ", 3, 3),
                    new TreeNode("����", 3, 3)
                });

            this.treeView.Nodes.AddRange(new TreeNode[] {treeNodeProject});

            treeNodeProject.Expand();
            sProject = treeNodeProject.Text;
            if (treeNodeProject.Nodes.Count > 0)
                treeNodeProject.Nodes[0].Expand();
        }

        public void UpdateTreeNode(SQLiteConnection sqlConnection, String filename)
        {
            treeView.Enabled = (sqlConnection.State == ConnectionState.Open);

            if (treeNodeProject == null)
                return;

            treeNodeProject.Text = String.Format("{0} \"{1}\"", sProject, System.IO.Path.GetFileName(filename));
            
            if (!treeView.Enabled)
                return;
            
            try
            {
                DataSet.FepCfgTableAdapters.t_driverTableAdapter ds = new DataSet.FepCfgTableAdapters.t_driverTableAdapter();
                ds.Connection = sqlConnection;
                while (treeNodeDriverCfg.Nodes.Count > 0)
                    treeNodeDriverCfg.Nodes.RemoveAt(0);
                
                foreach (DataSet.FepCfg.t_driverRow row in ds.GetData().Rows)
                {
                    if (row.preserve == 0 || row.visble == 0)
                        continue;

                    TreeNode node = treeNodeDriverCfg.Nodes.Insert((int)row.id, row.name, row.name, 6, 6);
                    node.Tag = row.id;
                    node.ToolTipText = row.desc;
                }

                treeNodeDriverCfg.Expand();
            }
            catch (Exception ex)
            {
                MessageBox.Show("���������б�ʧ�ܣ��������ÿ��Ƿ���Ч��������Ϣ��" + ex.Message);
            }
        }

        private void treeView_DoubleClick(object sender, EventArgs e)
        {
            TreeNode node = treeView.SelectedNode;            
            MainForm main = (MainForm)ParentForm;

            if (node == null)
                return;
            else if (node.Parent == treeNodeDriverCfg)
                main.OpenDockContent(@"FepManager.FormDriverCfg", node.Text, node.Tag);
            else if (node == treeNodeTagCfg)
                main.OpenDockContent(@"FepManager.FormTagCfg", "�ڵ�����", null);
            else if (node == treeNodeAuthCfg)
                    main.OpenDockContent(@"FepManager.FormAuthCfg", "��Ȩ����", null);
        }
    }
}