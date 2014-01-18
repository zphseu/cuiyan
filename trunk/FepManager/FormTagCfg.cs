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
        private MainForm parentForm;
        private Dictionary<String, DataSet.FepCfg.t_deviceRow> devNameList = new Dictionary<String, DataSet.FepCfg.t_deviceRow>();
        private Dictionary<String, DataSet.FepCfg.t_tagtypeRow> typeNameList = new Dictionary<String, DataSet.FepCfg.t_tagtypeRow>();
        private FepManager.PropGridHelper.TagRow m_CurPGRow = null;

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
            this.t_tagtypeTableAdapter.Connection = parentForm.SqlLiteConnection;
            this.t_tagTableAdapter.Fill(this.fepCfg.t_tag);
            this.t_deviceTableAdapter.Fill(this.fepCfg.t_device);
            this.t_tagtypeTableAdapter.Fill(this.fepCfg.t_tagtype);

            tsCbxDevice.Items.Add("所有设备");
            tsCbxDevice.SelectedIndex = 0;
            foreach (DataSet.FepCfg.t_deviceRow row in fepCfg.t_device.Rows)
            {
                devNameList[row.name] = row;
                tsCbxDevice.Items.Add(row.name);
            }

            tsCbxType.Items.Add("所有类型");
            tsCbxType.SelectedIndex = 0;
            foreach (DataSet.FepCfg.t_tagtypeRow row in fepCfg.t_tagtype.Rows)
            {
                typeNameList[row.name] = row;
                tsCbxType.Items.Add(row.name);
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

            if (bChanged)
            {
                switch (MessageBox.Show(String.Format("变量配置信息已经修改，要保存吗？"), "确认", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Information))
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

            if (!e.Cancel && parentForm.PropertyGridObject == m_CurPGRow)
                parentForm.PropertyGridObject = null;
        }

        private void dataGridView_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            tsBtnEdit_Click(sender, e);
        }

        private void tsBtnAdd_Click(object sender, EventArgs e)
        {
            try
            {
                if (fepCfg.t_tag.Rows.Count > HelperConst.MAX_TAG_COUNT)
                    throw new Exception(String.Format("变量个数超过限制【{0}】，不可再添加。", HelperConst.MAX_TAG_COUNT));    
                if (tsCbxDevice.SelectedIndex == 0 || tsCbxType.SelectedIndex == 0 )
                    throw new Exception("请首先在工具条上指定要增加的【设备名称】和 【变量类型】！");
                if (tsCbxDevice.SelectedItem == null || !devNameList.ContainsKey(tsCbxDevice.SelectedItem.ToString()))
                    throw new Exception("莫名其妙，怎么找不到你所选择的【设备名称】的ID ？！");
                if (tsCbxType.SelectedItem == null || !typeNameList.ContainsKey(tsCbxType.SelectedItem.ToString()))
                    throw new Exception("莫名其妙，怎么找不到你所选择的【变量类型】的ID ？！");

                fepCfg.t_tag.Addt_tagRow("tag?", devNameList[tsCbxDevice.SelectedItem.ToString()], "", 0, 1, 1000, 0, 0, 1, 3, "", "", "", "", "", 
                    typeNameList[tsCbxType.SelectedItem.ToString()]);
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
                    throw new Exception("请首先选中一条【变量】配置记录！");

                m_CurPGRow = new FepManager.PropGridHelper.TagRow((dataGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_tagRow, devNameList, typeNameList);
                parentForm.PropertyGridObject = m_CurPGRow;
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
                if (MessageBox.Show("你确定要删除变量【" + dataGridView.CurrentRow.Cells["name"].Value.ToString() + "】吗？",
                    "确认", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    ttagBindingSource.RemoveCurrent();
                }
            }
            else if (dataGridView.SelectedRows.Count > 1)
            {
                String sMsg = String.Format("你确定要删除所选的{0}个变量吗？", dataGridView.SelectedRows.Count);
                if (MessageBox.Show(sMsg, "确认", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    foreach (DataGridViewRow dgvRow in dataGridView.SelectedRows)
                    {
                        ttagBindingSource.RemoveAt(dgvRow.Index);
                    }
                }
            }
            else
            {
                MessageBox.Show("请首先选中至少一条【变量】配置记录！");
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
            saveFileDialog.FileName = String.Format("{0}_{1:yyyyMMddHHmmss}", this.Text, DateTime.Now);
            if (saveFileDialog.ShowDialog() != DialogResult.OK)
                return;
            HelperNPOI.TagCfgSaveTo(saveFileDialog.FileName, fepCfg.t_tag);
        }

        private void tsBtnImp_Click(object sender, EventArgs e)
        {
            tsBtnSave_Click(sender, e);

            openFileDialog.FileName = String.Format("{0}_", this.Text);
            if (openFileDialog.ShowDialog() != DialogResult.OK)
                return;

            if (dataGridView.Rows.Count > 0 && MessageBox.Show("是否保留原有数据，并在此基础上导入？\r\n如果选择否的话，则先清除此驱动所有配置信息，再进行导入。", 
                "确认", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                for (int i = dataGridView.RowCount; i > 0; i--)
                {
                    DataGridViewRow dgvRow = dataGridView.Rows[i - 1];
                    DataSet.FepCfg.t_tagRow devRow = (dgvRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_tagRow;
                    ttagBindingSource.RemoveAt(dgvRow.Index);
                }
            }

            try
            {
                DataSet.FepCfg dataTmp = fepCfg.Copy() as DataSet.FepCfg;
                String msg = HelperNPOI.TagCfgLoadFrom(openFileDialog.FileName, dataTmp);
                fepCfg.t_tag.Merge(dataTmp.t_tag);
                if (msg.Length > 0)
                    throw new Exception(msg);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "警告 -- 以下记录未导入", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }               

        }

        private void toolbarFilerChanged(object sender, EventArgs e)
        {
            //tsTxtName, tsCbxDevice, tsCbxType
            try
            {
                String filer = "";

                String tagFiler = tsTxtName.Text.Trim();
                if (tagFiler.Length > 0)
                    filer += String.Format("name like '%{0}%'", tagFiler);

                if (tsCbxDevice.SelectedIndex != 0 && tsCbxDevice.SelectedItem != null)
                {
                    filer += (filer.Length > 0) ? " AND " : "";
                    filer += String.Format("device_id = {0}", devNameList[tsCbxDevice.SelectedItem.ToString()].id);
                }

                if (tsCbxType.SelectedIndex != 0 && tsCbxType.SelectedItem != null)
                {
                    filer += (filer.Length > 0) ? " AND " : "";
                    filer += String.Format("tagtype_id = {0}", typeNameList[tsCbxType.SelectedItem.ToString()].id);
                }

                ttagBindingSource.Filter = filer;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}