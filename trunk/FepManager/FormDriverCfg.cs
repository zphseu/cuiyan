using System;
using System.Drawing;
using System.IO;
using System.Data;
using System.Windows.Forms;
using System.Xml;

namespace FepManager
{
	/// <summary>
	/// Description of DrvCfgForm.
	/// </summary>
	internal partial class FormDriverCfg : FormBase
	{
        MainForm parentForm;

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

            tdeviceBindingSource.Filter = String.Format("driver_id = {0}", this.Tag);
            t_deviceTableAdapter.Connection = parentForm.SqlLiteConnection;
            t_datablockTableAdapter.Connection = parentForm.SqlLiteConnection;
            t_deviceTableAdapter.Fill(fepCfg.t_device);
            t_datablockTableAdapter.Fill(fepCfg.t_datablock);
            
            devGridView_SelectionChanged(this, new EventArgs());
        }

        private void FormDriverCfg_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                t_deviceTableAdapter.Update(fepCfg);
                t_datablockTableAdapter.Update(fepCfg);
            }
            catch (Exception Error)
            {
                MessageBox.Show(Error.Message);
            }
        }

        private void devGridView_SelectionChanged(object sender, EventArgs e)
        {
            long device_id = -1;
            if (devGridView.CurrentRow != null)
            {
                DataSet.FepCfg.t_deviceRow row = (devGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_deviceRow;
                device_id = row.id;
            }
            tdatablockBindingSource.Filter = String.Format("device_id={0}", device_id);
        }

        private void devGridView_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            btnDevModify_Click(sender, e);
        }

        private void blockGridView_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            btnBlkModify_Click(sender, e);
        }

        private void btnDevAdd_Click(object sender, EventArgs e)
        {
        }

        private void btnDevModify_Click(object sender, EventArgs e)
        {
            if (devGridView.SelectedRows.Count < 0)
            {
                MessageBox.Show("请首先选中一条【设备】配置信息！");
                return;
            }

            DataSet.FepCfg.t_deviceRow row = (devGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_deviceRow;
            //parentForm.SetPropertyGridRow(row);
            FepManager.PropGridHelper.ModbusEthDevRow devRow = new FepManager.PropGridHelper.ModbusEthDevRow(row);
            parentForm.SetPropertyGridObject(devRow);
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
        }

        private void btnBlkModify_Click(object sender, EventArgs e)
        {
            if (blockGridView.SelectedRows.Count < 0)
            {
                MessageBox.Show("请首先选中一条【设备】配置信息！");
                return;
            }

            DataSet.FepCfg.t_datablockRow row = (blockGridView.CurrentRow.DataBoundItem as DataRowView).Row as DataSet.FepCfg.t_datablockRow;
            parentForm.SetPropertyGridRow(row);
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
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
        }
	}
}
