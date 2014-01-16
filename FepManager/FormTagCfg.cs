using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace FepManager
{
    internal partial class FormTagCfg : FormBase
    {
        internal enum TypeName
        {
            TEXT = 0,	// ASCII string, maximum: 127
            SINT16 = 1,	// 16 bit Signed Integer value
            UINT16 = 2,	// 16 bit Unsigned Integer value
            FLOAT = 3,		// 32 bit IEEE float
            BIT = 4,		// 1 bit value
            ULONG = 6,	// 32 bit integer value
            SLONG = 7,	// 32 bit signed integer value
            DOUBLE = 8,		// 64 bit double
            BLOB = 9,	// blob, maximum 65535
            CHAR = 10,	// 8 bit signed integer value
            UCHAR = 11   // 8 bit unsigned integer value
        };

        private MainForm parentForm;

        public FormTagCfg()
        {
            InitializeComponent();
        }

        private void FormTagCfg_Load(object sender, EventArgs e)
        {
            // TODO: 这行代码将数据加载到表“fepCfg.t_tag”中。您可以根据需要移动或移除它。
            this.t_tagTableAdapter.Fill(this.fepCfg.t_tag);
            parentForm = (MainForm)ParentForm;
            if (parentForm.SqlLiteConnection.State != ConnectionState.Open)
                return;
            
        }

        private void dataGridView_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            tsBtnEdit_Click(sender, e);
        }

        private void tsBtnAdd_Click(object sender, EventArgs e)
        {

        }

        private void tsBtnEdit_Click(object sender, EventArgs e)
        {
            if (dataGridView.SelectedRows.Count < 0)
            {
                MessageBox.Show("请首先选中一个节点！");
                return;
            }

            //setPropertyGrid(row);

            //HelperTag tag = new HelperTag();
            //thePG.SelectedObject = tag;
            //MessageBox.Show((row.Isfd_descNull()) ? "" : (row.fd_desc + "\r\n") + row.fd_config, "信息", MessageBoxButtons.OK);
        }

        private void tsBtnDel_Click(object sender, EventArgs e)
        {
            if (dataGridView.SelectedRows.Count < 0)
            {
                MessageBox.Show("请首先选中一个节点！");
                return;
            }

            try
            {
                //DataSet.DataSetFepCfg.t_cc_drivercfgRow row = (dataGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.DataSetFepCfg.t_cc_drivercfgRow;
                //int index = (int)row.fd_id;
                //if (MessageBox.Show("你确定要删除配置【" + row.fd_id + "】吗？", "确认", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    //this.tccdrivercfgBindingSource.RemoveCurrent();
                    //this.t_cc_drivercfgTableAdapter.DeleteById(index);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void tsBtnExp_Click(object sender, EventArgs e)
        {

        }

        private void tsBtnImp_Click(object sender, EventArgs e)
        {

        }

        private void tsBtnQuery_Click(object sender, EventArgs e)
        {

        }

        private void tsTxtName_TextChanged(object sender, EventArgs e)
        {

        }

        private void tsCbxDevice_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void tsCbxType_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}