using System;
using System.Drawing;
using System.IO;
using System.Data;
using System.Windows.Forms;
using System.Xml;
using System.Reflection;

namespace FepManager
{
	/// <summary>
	/// Description of DrvCfgForm.
	/// </summary>
	internal partial class FormDriverCfg : FormBase
	{
        MainForm parentForm;
        DataSet.FepCfg.t_driverRow drvRow = null;

        public FormDriverCfg()
		{
			InitializeComponent();
		}

        protected override string GetPersistString()
        {
            return GetType().ToString();
        }

        private void FormDriverCfg_Load(object sender, EventArgs e)
        {
            parentForm = (MainForm)ParentForm;
            if (parentForm.SqlLiteConnection.State != ConnectionState.Open)
                return;
            try
            {
                tdeviceBindingSource.Filter = String.Format("driver_id = {0}", this.Tag);
                t_driverTableAdapter.Connection = parentForm.SqlLiteConnection;
                t_deviceTableAdapter.Connection = parentForm.SqlLiteConnection;
                t_datablockTableAdapter.Connection = parentForm.SqlLiteConnection;

                t_deviceTableAdapter.Fill(fepCfg.t_device);
                t_datablockTableAdapter.Fill(fepCfg.t_datablock);
                t_driverTableAdapter.FillById(fepCfg.t_driver, (int)(long)this.Tag);

                if (fepCfg.t_driver.Count == 1)
                    drvRow = fepCfg.t_driver.Rows[0] as DataSet.FepCfg.t_driverRow;
                else
                    throw new Exception(String.Format("无法找到id={0}的驱动信息！", this.Tag));

                devGridView_SelectionChanged(this, new EventArgs());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void FormDriverCfg_FormClosing(object sender, FormClosingEventArgs e)
        {
            Boolean bDevChanged = false;
            Boolean bBlkChanged = false;

            foreach (DataRow row in fepCfg.t_device.Rows)
            {
                if (row.RowState == DataRowState.Unchanged)
                    continue;

                bDevChanged = true;
                break;
            }

            foreach (DataRow row in fepCfg.t_datablock.Rows)
            {
                if (row.RowState == DataRowState.Unchanged)
                    continue;

                bBlkChanged = true;
                break;
            }

            if (!bDevChanged && !bBlkChanged)
                return;

            switch (MessageBox.Show(String.Format("驱动[{0}]的配置信息已经修改，要保存吗？", Text), "确认", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Information))
            {
                case DialogResult.Yes:
                    try
                    {
                        t_deviceTableAdapter.Update(fepCfg.t_device);
                        t_datablockTableAdapter.Update(fepCfg.t_datablock);
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

        private void devGridView_SelectionChanged(object sender, EventArgs e)
        {
            long device_id = -1;
            if (devGridView.CurrentRow != null && !devGridView.CurrentRow.IsNewRow)
            {
                DataSet.FepCfg.t_deviceRow row = (devGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_deviceRow;
                device_id = row.id;
            }
            tdatablockBindingSource.Filter = String.Format("device_id={0}", device_id);
        }

        private void blockGridView_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            btnBlkModify_Click(sender, e);
        }

        private void devGridView_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            btnDevModify_Click(sender, e);
        }

        private void btnDevAdd_Click(object sender, EventArgs e)
        {
            try
            {
                fepCfg.t_device.Addt_deviceRow(this.drvRow, "device?", "", "", 1000, 3000, 1, "", "", "", "");
                devGridView.Update();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnDevModify_Click(object sender, EventArgs e)
        {
            try
            {
                if (devGridView.SelectedRows.Count <= 0)
                    throw new Exception("请首先选中一条【设备】配置信息！");

                DataSet.FepCfg.t_deviceRow row = (devGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_deviceRow;
                Assembly _assembly = Assembly.GetExecutingAssembly();
                Object obj = _assembly.CreateInstance("FepManager.PropGridHelper." + this.Text + "DevRow",
                    false, BindingFlags.Default, null, new object[] { row }, null, null);
                
                if (obj != null)
                    parentForm.SetPropertyGridObject(obj);
                else
                    parentForm.SetPropertyGridRow(row);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void _delDataBlockGridRow(long deviceId)
        {
            for(int i = tdatablockBindingSource.List.Count - 1; i >= 0; i--)
            {
                DataRowView dgvDbRow = tdatablockBindingSource.List[i] as DataRowView;
                DataSet.FepCfg.t_datablockRow dbRow = dgvDbRow.Row as DataSet.FepCfg.t_datablockRow;
                if (dbRow.device_id == deviceId)
                {
                    tdatablockBindingSource.Remove(dgvDbRow);
                }
            }
        }

        private void btnDevDel_Click(object sender, EventArgs e)
        {
            if (devGridView.SelectedRows.Count == 1)
            {
                if (MessageBox.Show("你确定要删除设备【" + devGridView.CurrentRow.Cells["devName"].Value.ToString() + "】及相关的数据块吗？", 
                    "确认", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    DataSet.FepCfg.t_deviceRow devRow = (devGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_deviceRow;
                    _delDataBlockGridRow(devRow.id);
                    tdeviceBindingSource.RemoveCurrent();
                }
            }
            else if (devGridView.SelectedRows.Count > 1)
            {
                String sMsg = String.Format("你确定要删除所选的{0}个设备及相关的数据块吗？", devGridView.SelectedRows.Count);
                if (MessageBox.Show(sMsg, "确认", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    foreach (DataGridViewRow dgvRow in devGridView.SelectedRows)
                    {
                        DataSet.FepCfg.t_deviceRow devRow = (dgvRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_deviceRow;
                        _delDataBlockGridRow(devRow.id);                        
                        tdeviceBindingSource.RemoveAt(dgvRow.Index);
                    }
                }
            }
            else
            {
                MessageBox.Show("请首先选中至少一条【设备】配置信息！");
            }
        }

        private void btnBlkAdd_Click(object sender, EventArgs e)
        {
            try
            {
                if (devGridView.SelectedRows.Count <= 0)
                    throw new Exception("请首先选中一条【设备】配置信息！");

                DataSet.FepCfg.t_deviceRow devRow = (devGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_deviceRow;
                fepCfg.t_datablock.Addt_datablockRow(devRow, "block?", "", "", 1000, 2, 100, 0, 1, "", "", "", "");
                blockGridView.Update();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnBlkModify_Click(object sender, EventArgs e)
        {
            try
            {
                if (blockGridView.SelectedRows.Count <= 0)
                    throw new Exception("请首先选中一条【数据块】配置信息！");

                DataSet.FepCfg.t_datablockRow row = (blockGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_datablockRow;
                Assembly _assembly = Assembly.GetExecutingAssembly();
                Object obj = _assembly.CreateInstance("FepManager.PropGridHelper." + this.Text + "BlockRow",
                    false, BindingFlags.Default, null, new object[] { row }, null, null);
                if (obj != null)
                    parentForm.SetPropertyGridObject(obj);
                else
                    parentForm.SetPropertyGridRow(row);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnBlkDel_Click(object sender, EventArgs e)
        {
            if (blockGridView.SelectedRows.Count == 1)
            {
                if (MessageBox.Show("你确定要删除数据块【" + blockGridView.CurrentRow.Cells["dbName"].Value.ToString() + "】吗？",
                    "确认", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    tdatablockBindingSource.RemoveCurrent();
                }
            }
            else if (blockGridView.SelectedRows.Count > 1)
            {
                String sMsg = String.Format("你确定要删除所选的{0}个数据块吗？", blockGridView.SelectedRows.Count);
                if (MessageBox.Show(sMsg, "确认", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    foreach (DataGridViewRow dgvRow in blockGridView.SelectedRows)
                    {
                        tdatablockBindingSource.RemoveAt(dgvRow.Index);
                    }
                }
            }
            else
            {
                MessageBox.Show("请首先选中至少一条【数据块】配置信息！");
            }
        }

        private void btnImport_Click(object sender, EventArgs e)
        {
            if (openFileDialog.ShowDialog() != DialogResult.OK)
                return;

            try
            {
                DataSet.FepCfg dataTmp = fepCfg.Copy() as DataSet.FepCfg;
                HelperNPOI.DriverCfgLoadFrom(openFileDialog.FileName, dataTmp);
                fepCfg.Clear();
                fepCfg = dataTmp.Copy() as DataSet.FepCfg;
                dataTmp.Dispose();
                this.tdeviceBindingSource.DataSource = this.fepCfg;
                this.tdatablockBindingSource.DataSource = this.fepCfg;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            if (saveFileDialog.ShowDialog() != DialogResult.OK)
                return;
            HelperNPOI.DriverCfgSaveTo(saveFileDialog.FileName, fepCfg);
        }
	}
}
