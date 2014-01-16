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
        private Dictionary<String, DataSet.FepCfg.t_deviceRow> devNameList = new Dictionary<String, DataSet.FepCfg.t_deviceRow>();

        public FormTagCfg()
        {
            InitializeComponent();
        }

        private void FormTagCfg_Load(object sender, EventArgs e)
        {
            parentForm = (MainForm)ParentForm;
            if (parentForm.SqlLiteConnection.State != ConnectionState.Open)
                return;

            this.t_tagTableAdapter.Connection = parentForm.SqlLiteConnection;
            this.t_deviceTableAdapter.Connection = parentForm.SqlLiteConnection;
            this.t_tagTableAdapter.Fill(this.fepCfg.t_tag);
            this.t_deviceTableAdapter.Fill(this.fepCfg.t_device);

            tsCbxDevice.Items.Add("�����豸");
            tsCbxDevice.SelectedIndex = 0;
            foreach (DataSet.FepCfg.t_deviceRow row in fepCfg.t_device.Rows)
            {
                devNameList[row.name] = row;
                tsCbxDevice.Items.Add(row.name);
            }
        }

        private void FormTagCfg_FormClosing(object sender, FormClosingEventArgs e)
        {
            Boolean bChanged = false;

            foreach (DataRow row in fepCfg.t_tag.Rows)
            {
                if (row.RowState != DataRowState.Unchanged)
                {
                    bChanged = true;
                    break;
                }
                else
                {
                    continue;
                }
            }

            if (!bChanged)
                return;

            switch (MessageBox.Show(String.Format("����������Ϣ�Ѿ��޸ģ�Ҫ������"), "ȷ��", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Information))
            {
                case DialogResult.Yes:
                    try
                    {
                        t_tagTableAdapter.Update(fepCfg.t_tag);
                    }
                    catch (Exception Error)
                    {
                        MessageBox.Show(Error.Message);
                        e.Cancel = true;
                    }
                    break;
                case DialogResult.Cancel:
                    e.Cancel = true;
                    break;
                default:
                    break;
            }
        }

        private void dataGridView_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            tsBtnEdit_Click(sender, e);
        }

        private void tsBtnAdd_Click(object sender, EventArgs e)
        {
            try
            {
                if (tsCbxDevice.SelectedIndex == 0)
                    throw new Exception("�������ڹ�������ָ��Ҫ���ӵġ��������͡���");
                if (!devNameList.ContainsKey(tsCbxDevice.SelectedItem.ToString()))
                    throw new Exception("Ī�������ô�Ҳ�������ѡ��ġ��������͡���ID ����");

                fepCfg.t_tag.Addt_tagRow("tag?", devNameList[tsCbxDevice.SelectedItem.ToString()], 0, "", 0, 0, 0, 0, 0, 0, 0, "", "", "", "", "");
                dataGridView.Update();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void tsBtnEdit_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridView.SelectedRows.Count <= 0)
                    throw new Exception("������ѡ��һ�������������ü�¼��");
                parentForm.SetPropertyGridObject(new FepManager.PropGridHelper.TagRow((dataGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_tagRow, devNameList));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void tsBtnDel_Click(object sender, EventArgs e)
        {
            if (dataGridView.SelectedRows.Count == 1)
            {
                if (MessageBox.Show("��ȷ��Ҫɾ��������" + dataGridView.CurrentRow.Cells["name"].Value.ToString() + "����",
                    "ȷ��", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    ttagBindingSource.RemoveCurrent();
                }
            }
            else if (dataGridView.SelectedRows.Count > 1)
            {
                String sMsg = String.Format("��ȷ��Ҫɾ����ѡ��{0}��������", dataGridView.SelectedRows.Count);
                if (MessageBox.Show(sMsg, "ȷ��", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    foreach (DataGridViewRow dgvRow in dataGridView.SelectedRows)
                    {
                        ttagBindingSource.RemoveAt(dgvRow.Index);
                    }
                }
            }
            else
            {
                MessageBox.Show("������ѡ������һ�������������ü�¼��");
            }
        }


        private void tsBtnSave_Click(object sender, EventArgs e)
        {
            try
            {
                t_tagTableAdapter.Update(fepCfg.t_tag);
            }
            catch (Exception Error)
            {
                MessageBox.Show(Error.Message);
            }
        }

        private void tsBtnExp_Click(object sender, EventArgs e)
        {

        }

        private void tsBtnImp_Click(object sender, EventArgs e)
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