/*
 * Created by SharpDevelop.
 * User: edson
 * Date: 2013/12/6 星期五
 * Time: 22:20
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace FepManager
{
	partial class FormDriverCfg
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.ToolStrip toolStrip;
            System.Windows.Forms.ToolStripButton btnDevAdd;
            System.Windows.Forms.ToolStripButton btnDevModify;
            System.Windows.Forms.ToolStripButton btnDevDel;
            System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
            System.Windows.Forms.ToolStripButton btnBlkAdd;
            System.Windows.Forms.ToolStripButton btnBlkModify;
            System.Windows.Forms.ToolStripButton btnBlkDel;
            System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
            System.Windows.Forms.ToolStripButton btnExport;
            System.Windows.Forms.ToolStripButton btnImport;
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormDriverCfg));
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.devGridView = new System.Windows.Forms.DataGridView();
            this.devName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devConntype = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devConnparam = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devCyclerate = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devRecvtimeout = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devTask = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devDesc = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devParam1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devParam2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.devParam3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tdeviceBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.fepCfg = new DataSet.FepCfg();
            this.blockGridView = new System.Windows.Forms.DataGridView();
            this.dbName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbAddress = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbCyclerate = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbElembytes = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbElemcount = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbPhase = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbTask = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbDesc = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbParam1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbParam2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dbParam3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tdatablockBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.t_deviceTableAdapter = new DataSet.FepCfgTableAdapters.t_deviceTableAdapter();
            this.t_datablockTableAdapter = new DataSet.FepCfgTableAdapters.t_datablockTableAdapter();
            toolStrip = new System.Windows.Forms.ToolStrip();
            btnDevAdd = new System.Windows.Forms.ToolStripButton();
            btnDevModify = new System.Windows.Forms.ToolStripButton();
            btnDevDel = new System.Windows.Forms.ToolStripButton();
            toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            btnBlkAdd = new System.Windows.Forms.ToolStripButton();
            btnBlkModify = new System.Windows.Forms.ToolStripButton();
            btnBlkDel = new System.Windows.Forms.ToolStripButton();
            toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            btnExport = new System.Windows.Forms.ToolStripButton();
            btnImport = new System.Windows.Forms.ToolStripButton();
            toolStrip.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.devGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tdeviceBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fepCfg)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.blockGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tdatablockBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // toolStrip
            // 
            toolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            btnDevAdd,
            btnDevModify,
            btnDevDel,
            toolStripSeparator1,
            btnBlkAdd,
            btnBlkModify,
            btnBlkDel,
            toolStripSeparator2,
            btnExport,
            btnImport});
            toolStrip.Location = new System.Drawing.Point(0, 4);
            toolStrip.Name = "toolStrip";
            toolStrip.Size = new System.Drawing.Size(655, 25);
            toolStrip.TabIndex = 1;
            toolStrip.Text = "修改所选数据块";
            // 
            // btnDevAdd
            // 
            btnDevAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            btnDevAdd.Image = global::FepManager.Properties.Resources._60;
            btnDevAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            btnDevAdd.Name = "btnDevAdd";
            btnDevAdd.Size = new System.Drawing.Size(23, 22);
            btnDevAdd.ToolTipText = "添加设备";
            btnDevAdd.Click += new System.EventHandler(this.btnDevAdd_Click);
            // 
            // btnDevModify
            // 
            btnDevModify.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            btnDevModify.Image = global::FepManager.Properties.Resources._64;
            btnDevModify.ImageTransparentColor = System.Drawing.Color.Magenta;
            btnDevModify.Name = "btnDevModify";
            btnDevModify.Size = new System.Drawing.Size(23, 22);
            btnDevModify.ToolTipText = "修改所选设备";
            btnDevModify.Click += new System.EventHandler(this.btnDevModify_Click);
            // 
            // btnDevDel
            // 
            btnDevDel.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            btnDevDel.Image = global::FepManager.Properties.Resources._59;
            btnDevDel.ImageTransparentColor = System.Drawing.Color.Magenta;
            btnDevDel.Name = "btnDevDel";
            btnDevDel.Size = new System.Drawing.Size(23, 22);
            btnDevDel.ToolTipText = "删除所选设备";
            btnDevDel.Click += new System.EventHandler(this.btnDevDel_Click);
            // 
            // toolStripSeparator1
            // 
            toolStripSeparator1.Name = "toolStripSeparator1";
            toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // btnBlkAdd
            // 
            btnBlkAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            btnBlkAdd.Image = global::FepManager.Properties.Resources._13;
            btnBlkAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            btnBlkAdd.Name = "btnBlkAdd";
            btnBlkAdd.Size = new System.Drawing.Size(23, 22);
            btnBlkAdd.ToolTipText = "添加数据块";
            btnBlkAdd.Click += new System.EventHandler(this.btnBlkAdd_Click);
            // 
            // btnBlkModify
            // 
            btnBlkModify.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            btnBlkModify.Image = global::FepManager.Properties.Resources._41;
            btnBlkModify.ImageTransparentColor = System.Drawing.Color.Magenta;
            btnBlkModify.Name = "btnBlkModify";
            btnBlkModify.Size = new System.Drawing.Size(23, 22);
            btnBlkModify.ToolTipText = "修改所选数据块";
            btnBlkModify.Click += new System.EventHandler(this.btnBlkModify_Click);
            // 
            // btnBlkDel
            // 
            btnBlkDel.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            btnBlkDel.Image = global::FepManager.Properties.Resources._14;
            btnBlkDel.ImageTransparentColor = System.Drawing.Color.Magenta;
            btnBlkDel.Name = "btnBlkDel";
            btnBlkDel.Size = new System.Drawing.Size(23, 22);
            btnBlkDel.ToolTipText = "删除所选数据块";
            btnBlkDel.Click += new System.EventHandler(this.btnBlkDel_Click);
            // 
            // toolStripSeparator2
            // 
            toolStripSeparator2.Name = "toolStripSeparator2";
            toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // btnExport
            // 
            btnExport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            btnExport.Image = global::FepManager.Properties.Resources._55;
            btnExport.ImageTransparentColor = System.Drawing.Color.Magenta;
            btnExport.Name = "btnExport";
            btnExport.Size = new System.Drawing.Size(23, 22);
            btnExport.ToolTipText = "导出配置到Excel文件";
            btnExport.Click += new System.EventHandler(this.btnExport_Click);
            // 
            // btnImport
            // 
            btnImport.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            btnImport.Image = global::FepManager.Properties.Resources._54;
            btnImport.ImageTransparentColor = System.Drawing.Color.Magenta;
            btnImport.Name = "btnImport";
            btnImport.Size = new System.Drawing.Size(23, 22);
            btnImport.ToolTipText = "导入Excel文件中的配置信息";
            btnImport.Click += new System.EventHandler(this.btnImport_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 29);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.devGridView);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.blockGridView);
            this.splitContainer1.Size = new System.Drawing.Size(655, 438);
            this.splitContainer1.SplitterDistance = 216;
            this.splitContainer1.TabIndex = 2;
            // 
            // devGridView
            // 
            this.devGridView.AllowUserToAddRows = false;
            this.devGridView.AllowUserToDeleteRows = false;
            this.devGridView.AllowUserToOrderColumns = true;
            this.devGridView.AutoGenerateColumns = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.devGridView.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.devGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.devGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.devName,
            this.devConntype,
            this.devConnparam,
            this.devCyclerate,
            this.devRecvtimeout,
            this.devTask,
            this.devDesc,
            this.devParam1,
            this.devParam2,
            this.devParam3});
            this.devGridView.DataSource = this.tdeviceBindingSource;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.devGridView.DefaultCellStyle = dataGridViewCellStyle2;
            this.devGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.devGridView.Location = new System.Drawing.Point(0, 0);
            this.devGridView.Name = "devGridView";
            this.devGridView.ReadOnly = true;
            this.devGridView.RowTemplate.Height = 23;
            this.devGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.devGridView.Size = new System.Drawing.Size(655, 216);
            this.devGridView.TabIndex = 0;
            this.devGridView.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.devGridView_CellDoubleClick);
            this.devGridView.SelectionChanged += new System.EventHandler(this.devGridView_SelectionChanged);
            // 
            // devName
            // 
            this.devName.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devName.DataPropertyName = "name";
            this.devName.HeaderText = "设备名称";
            this.devName.Name = "devName";
            this.devName.ReadOnly = true;
            // 
            // devConntype
            // 
            this.devConntype.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devConntype.DataPropertyName = "conntype";
            this.devConntype.HeaderText = "连接类型";
            this.devConntype.Name = "devConntype";
            this.devConntype.ReadOnly = true;
            // 
            // devConnparam
            // 
            this.devConnparam.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devConnparam.DataPropertyName = "connparam";
            this.devConnparam.FillWeight = 200F;
            this.devConnparam.HeaderText = "连接串";
            this.devConnparam.Name = "devConnparam";
            this.devConnparam.ReadOnly = true;
            // 
            // devCyclerate
            // 
            this.devCyclerate.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devCyclerate.DataPropertyName = "cyclerate";
            this.devCyclerate.FillWeight = 50F;
            this.devCyclerate.HeaderText = "周期";
            this.devCyclerate.Name = "devCyclerate";
            this.devCyclerate.ReadOnly = true;
            // 
            // devRecvtimeout
            // 
            this.devRecvtimeout.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devRecvtimeout.DataPropertyName = "recvtimeout";
            this.devRecvtimeout.FillWeight = 50F;
            this.devRecvtimeout.HeaderText = "超时";
            this.devRecvtimeout.Name = "devRecvtimeout";
            this.devRecvtimeout.ReadOnly = true;
            // 
            // devTask
            // 
            this.devTask.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devTask.DataPropertyName = "task";
            this.devTask.FillWeight = 50F;
            this.devTask.HeaderText = "任务号";
            this.devTask.Name = "devTask";
            this.devTask.ReadOnly = true;
            // 
            // devDesc
            // 
            this.devDesc.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devDesc.DataPropertyName = "desc";
            this.devDesc.HeaderText = "描述";
            this.devDesc.Name = "devDesc";
            this.devDesc.ReadOnly = true;
            // 
            // devParam1
            // 
            this.devParam1.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devParam1.DataPropertyName = "param1";
            this.devParam1.HeaderText = "参数1";
            this.devParam1.Name = "devParam1";
            this.devParam1.ReadOnly = true;
            // 
            // devParam2
            // 
            this.devParam2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devParam2.DataPropertyName = "param2";
            this.devParam2.HeaderText = "参数2";
            this.devParam2.Name = "devParam2";
            this.devParam2.ReadOnly = true;
            // 
            // devParam3
            // 
            this.devParam3.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.devParam3.DataPropertyName = "param3";
            this.devParam3.HeaderText = "参数3";
            this.devParam3.Name = "devParam3";
            this.devParam3.ReadOnly = true;
            // 
            // tdeviceBindingSource
            // 
            this.tdeviceBindingSource.DataMember = "t_device";
            this.tdeviceBindingSource.DataSource = this.fepCfg;
            // 
            // fepCfg
            // 
            this.fepCfg.DataSetName = "FepCfg";
            this.fepCfg.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // blockGridView
            // 
            this.blockGridView.AllowUserToAddRows = false;
            this.blockGridView.AllowUserToDeleteRows = false;
            this.blockGridView.AllowUserToOrderColumns = true;
            this.blockGridView.AutoGenerateColumns = false;
            this.blockGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.blockGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dbName,
            this.dbType,
            this.dbAddress,
            this.dbCyclerate,
            this.dbElembytes,
            this.dbElemcount,
            this.dbPhase,
            this.dbTask,
            this.dbDesc,
            this.dbParam1,
            this.dbParam2,
            this.dbParam3});
            this.blockGridView.DataSource = this.tdatablockBindingSource;
            this.blockGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.blockGridView.Location = new System.Drawing.Point(0, 0);
            this.blockGridView.Name = "blockGridView";
            this.blockGridView.ReadOnly = true;
            this.blockGridView.RowTemplate.Height = 23;
            this.blockGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.blockGridView.Size = new System.Drawing.Size(655, 218);
            this.blockGridView.TabIndex = 0;
            this.blockGridView.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.blockGridView_CellDoubleClick);
            // 
            // dbName
            // 
            this.dbName.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbName.DataPropertyName = "name";
            this.dbName.HeaderText = "块名称";
            this.dbName.Name = "dbName";
            this.dbName.ReadOnly = true;
            // 
            // dbType
            // 
            this.dbType.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbType.DataPropertyName = "type";
            this.dbType.HeaderText = "类型";
            this.dbType.Name = "dbType";
            this.dbType.ReadOnly = true;
            // 
            // dbAddress
            // 
            this.dbAddress.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbAddress.DataPropertyName = "address";
            this.dbAddress.HeaderText = "起始地址";
            this.dbAddress.Name = "dbAddress";
            this.dbAddress.ReadOnly = true;
            // 
            // dbCyclerate
            // 
            this.dbCyclerate.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbCyclerate.DataPropertyName = "cyclerate";
            this.dbCyclerate.HeaderText = "周期";
            this.dbCyclerate.Name = "dbCyclerate";
            this.dbCyclerate.ReadOnly = true;
            // 
            // dbElembytes
            // 
            this.dbElembytes.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbElembytes.DataPropertyName = "elembytes";
            this.dbElembytes.HeaderText = "元素字节数";
            this.dbElembytes.Name = "dbElembytes";
            this.dbElembytes.ReadOnly = true;
            // 
            // dbElemcount
            // 
            this.dbElemcount.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbElemcount.DataPropertyName = "elemcount";
            this.dbElemcount.HeaderText = "元素个数";
            this.dbElemcount.Name = "dbElemcount";
            this.dbElemcount.ReadOnly = true;
            // 
            // dbPhase
            // 
            this.dbPhase.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbPhase.DataPropertyName = "phase";
            this.dbPhase.HeaderText = "相位";
            this.dbPhase.Name = "dbPhase";
            this.dbPhase.ReadOnly = true;
            // 
            // dbTask
            // 
            this.dbTask.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbTask.DataPropertyName = "task";
            this.dbTask.HeaderText = "任务号";
            this.dbTask.Name = "dbTask";
            this.dbTask.ReadOnly = true;
            // 
            // dbDesc
            // 
            this.dbDesc.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbDesc.DataPropertyName = "desc";
            this.dbDesc.HeaderText = "描述";
            this.dbDesc.Name = "dbDesc";
            this.dbDesc.ReadOnly = true;
            // 
            // dbParam1
            // 
            this.dbParam1.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbParam1.DataPropertyName = "param1";
            this.dbParam1.HeaderText = "参数1";
            this.dbParam1.Name = "dbParam1";
            this.dbParam1.ReadOnly = true;
            // 
            // dbParam2
            // 
            this.dbParam2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbParam2.DataPropertyName = "param2";
            this.dbParam2.HeaderText = "参数2";
            this.dbParam2.Name = "dbParam2";
            this.dbParam2.ReadOnly = true;
            // 
            // dbParam3
            // 
            this.dbParam3.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.dbParam3.DataPropertyName = "param3";
            this.dbParam3.HeaderText = "参数3";
            this.dbParam3.Name = "dbParam3";
            this.dbParam3.ReadOnly = true;
            // 
            // tdatablockBindingSource
            // 
            this.tdatablockBindingSource.DataMember = "t_datablock";
            this.tdatablockBindingSource.DataSource = this.fepCfg;
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "Excel File|*.xls|All files|*.*";
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.Filter = "Excel File|*.xls|All files|*.*";
            // 
            // t_deviceTableAdapter
            // 
            this.t_deviceTableAdapter.ClearBeforeFill = true;
            // 
            // t_datablockTableAdapter
            // 
            this.t_datablockTableAdapter.ClearBeforeFill = true;
            // 
            // FormDriverCfg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(655, 467);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(toolStrip);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormDriverCfg";
            this.ShowInTaskbar = false;
            this.Text = "驱动配置窗口";
            this.Load += new System.EventHandler(this.FormDriverCfg_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormDriverCfg_FormClosing);
            toolStrip.ResumeLayout(false);
            toolStrip.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.devGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tdeviceBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fepCfg)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.blockGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tdatablockBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        private System.Windows.Forms.DataGridView devGridView;
        private System.Windows.Forms.DataGridView blockGridView;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private DataSet.FepCfg fepCfg;
        private System.Windows.Forms.BindingSource tdeviceBindingSource;
        private DataSet.FepCfgTableAdapters.t_deviceTableAdapter t_deviceTableAdapter;
        private System.Windows.Forms.BindingSource tdatablockBindingSource;
        private DataSet.FepCfgTableAdapters.t_datablockTableAdapter t_datablockTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn devName;
        private System.Windows.Forms.DataGridViewTextBoxColumn devConntype;
        private System.Windows.Forms.DataGridViewTextBoxColumn devConnparam;
        private System.Windows.Forms.DataGridViewTextBoxColumn devCyclerate;
        private System.Windows.Forms.DataGridViewTextBoxColumn devRecvtimeout;
        private System.Windows.Forms.DataGridViewTextBoxColumn devTask;
        private System.Windows.Forms.DataGridViewTextBoxColumn devDesc;
        private System.Windows.Forms.DataGridViewTextBoxColumn devParam1;
        private System.Windows.Forms.DataGridViewTextBoxColumn devParam2;
        private System.Windows.Forms.DataGridViewTextBoxColumn devParam3;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbName;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbType;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbAddress;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbCyclerate;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbElembytes;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbElemcount;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbPhase;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbTask;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbDesc;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbParam1;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbParam2;
        private System.Windows.Forms.DataGridViewTextBoxColumn dbParam3;
	}
}
