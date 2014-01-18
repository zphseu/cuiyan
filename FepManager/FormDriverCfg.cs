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
        private MainForm parentForm;
        private DataSet.FepCfg.t_driverRow m_drvRow = null;
        private Object m_CurPGRow = null;

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

                t_driverTableAdapter.Fill(fepCfg.t_driver);
                t_deviceTableAdapter.Fill(fepCfg.t_device);
                t_datablockTableAdapter.Fill(fepCfg.t_datablock);

                foreach (DataSet.FepCfg.t_driverRow row in fepCfg.t_driver.Rows)
                {
                    if (row.id == (long)this.Tag)
                    {
                        m_drvRow = row;
                        break;
                    }
                }
                if (m_drvRow == null)
                {
                    throw new Exception("无法找到驱动信息！");
                }

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

            if (bDevChanged || bBlkChanged)
            {
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

            if (!e.Cancel && parentForm.PropertyGridObject == m_CurPGRow)
                parentForm.PropertyGridObject = null;
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
                if (fepCfg.t_device.Rows.Count > HelperConst.MAX_DEV_COUNT)
                    throw new Exception(String.Format("设备变量个数超过限制【{0}】，不可再添加。", HelperConst.MAX_DEV_COUNT));
                fepCfg.t_device.Addt_deviceRow(m_drvRow, "device?", "", "", 1000, 3000, 1, "", "", "", "");
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
                {
                    m_CurPGRow = obj;
                    parentForm.PropertyGridObject = m_CurPGRow;
                }
                else
                {
                    m_CurPGRow = row;
                    parentForm.PropertyGridDataRow = (DataRow)m_CurPGRow;
                }
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
                {
                    m_CurPGRow = obj;
                    parentForm.PropertyGridObject = m_CurPGRow;
                }
                else
                {
                    m_CurPGRow = row;
                    parentForm.PropertyGridDataRow = (DataRow)m_CurPGRow;
                }
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
            btnSave_Click(sender, e);
            openFileDialog.FileName = String.Format("{0}_", Text);
            if (openFileDialog.ShowDialog() != DialogResult.OK)
                return;

            if (devGridView.Rows.Count > 0 &&  MessageBox.Show("是否保留原有数据，并在此基础上导入？\r\n如果选择否的话，则先清除此驱动所有配置信息，再进行导入。", 
                "确认", MessageBoxButtons.YesNo) == DialogResult.No)
            {
                for (int i = devGridView.RowCount; i > 0; i--)
                {
                    DataGridViewRow dgvRow = devGridView.Rows[i-1];
                    DataSet.FepCfg.t_deviceRow devRow = (dgvRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_deviceRow;
                    _delDataBlockGridRow(devRow.id);
                    tdeviceBindingSource.RemoveAt(dgvRow.Index); 
                }
            }

            try
            {
                DataSet.FepCfg dataTmp = fepCfg.Copy() as DataSet.FepCfg;
                String msg = HelperNPOI.DriverCfgLoadFrom(openFileDialog.FileName, m_drvRow, dataTmp);
                fepCfg.Clear();
                fepCfg = dataTmp.Copy() as DataSet.FepCfg;
                dataTmp.Dispose();
                this.tdeviceBindingSource.DataSource = this.fepCfg;
                this.tdatablockBindingSource.DataSource = this.fepCfg;
                if (msg.Length > 0)
                    throw new Exception(msg);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            saveFileDialog.FileName = String.Format("{0}_{1:yyyyMMddHHmmss}", m_drvRow.name, DateTime.Now);
            if (saveFileDialog.ShowDialog() != DialogResult.OK)
                return;
            HelperNPOI.DriverCfgSaveTo(saveFileDialog.FileName, fepCfg);
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            try
            {
                t_deviceTableAdapter.Update(fepCfg.t_device);
                t_datablockTableAdapter.Update(fepCfg.t_datablock);
            }
            catch (Exception Error)
            {
                MessageBox.Show(Error.Message);
            }
        }
	}
}
