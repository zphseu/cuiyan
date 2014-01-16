namespace FepManager
{
    partial class FormTagCfg
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.ToolStripLabel toolStripLabel1;
            System.Windows.Forms.ToolStripLabel toolStripLabel4;
            System.Windows.Forms.ToolStripLabel toolStripLabel5;
            System.Windows.Forms.ToolStripButton tsBtnAdd;
            System.Windows.Forms.ToolStripButton tsBtnEdit;
            System.Windows.Forms.ToolStripButton tsBtnDel;
            System.Windows.Forms.ToolStripButton tsBtnExp;
            System.Windows.Forms.ToolStripButton tsBtnSave;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormTagCfg));
            System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
            System.Windows.Forms.ToolStripButton toolStripButton1;
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            this.toolBar = new System.Windows.Forms.ToolStrip();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsTxtName = new System.Windows.Forms.ToolStripTextBox();
            this.tsCbxDevice = new System.Windows.Forms.ToolStripComboBox();
            this.tsCbxType = new System.Windows.Forms.ToolStripComboBox();
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.desc = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.type = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.deviceid = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.fepCfg = new DataSet.FepCfg();
            this.address = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.scanintv = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ctrlenable = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ttagBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.t_tagTableAdapter = new DataSet.FepCfgTableAdapters.t_tagTableAdapter();
            this.t_deviceTableAdapter = new DataSet.FepCfgTableAdapters.t_deviceTableAdapter();
            toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            toolStripLabel5 = new System.Windows.Forms.ToolStripLabel();
            tsBtnAdd = new System.Windows.Forms.ToolStripButton();
            tsBtnEdit = new System.Windows.Forms.ToolStripButton();
            tsBtnDel = new System.Windows.Forms.ToolStripButton();
            tsBtnExp = new System.Windows.Forms.ToolStripButton();
            tsBtnSave = new System.Windows.Forms.ToolStripButton();
            toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolBar.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fepCfg)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ttagBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // toolStripLabel1
            // 
            toolStripLabel1.Name = "toolStripLabel1";
            toolStripLabel1.Size = new System.Drawing.Size(53, 22);
            toolStripLabel1.Text = "变量名称";
            // 
            // toolStripLabel4
            // 
            toolStripLabel4.Name = "toolStripLabel4";
            toolStripLabel4.Size = new System.Drawing.Size(29, 22);
            toolStripLabel4.Text = "设备";
            // 
            // toolStripLabel5
            // 
            toolStripLabel5.Name = "toolStripLabel5";
            toolStripLabel5.Size = new System.Drawing.Size(29, 22);
            toolStripLabel5.Text = "类型";
            // 
            // tsBtnAdd
            // 
            tsBtnAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            tsBtnAdd.Image = global::FepManager.Properties.Resources._60;
            tsBtnAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
            tsBtnAdd.Name = "tsBtnAdd";
            tsBtnAdd.Size = new System.Drawing.Size(23, 22);
            tsBtnAdd.ToolTipText = "添加设备";
            tsBtnAdd.Click += new System.EventHandler(this.tsBtnAdd_Click);
            // 
            // tsBtnEdit
            // 
            tsBtnEdit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            tsBtnEdit.Image = global::FepManager.Properties.Resources._64;
            tsBtnEdit.ImageTransparentColor = System.Drawing.Color.Magenta;
            tsBtnEdit.Name = "tsBtnEdit";
            tsBtnEdit.Size = new System.Drawing.Size(23, 22);
            tsBtnEdit.ToolTipText = "修改所选设备";
            tsBtnEdit.Click += new System.EventHandler(this.tsBtnEdit_Click);
            // 
            // tsBtnDel
            // 
            tsBtnDel.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            tsBtnDel.Image = global::FepManager.Properties.Resources._59;
            tsBtnDel.ImageTransparentColor = System.Drawing.Color.Magenta;
            tsBtnDel.Name = "tsBtnDel";
            tsBtnDel.Size = new System.Drawing.Size(23, 22);
            tsBtnDel.ToolTipText = "删除所选设备";
            tsBtnDel.Click += new System.EventHandler(this.tsBtnDel_Click);
            // 
            // tsBtnExp
            // 
            tsBtnExp.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            tsBtnExp.Image = global::FepManager.Properties.Resources._55;
            tsBtnExp.ImageTransparentColor = System.Drawing.Color.Magenta;
            tsBtnExp.Name = "tsBtnExp";
            tsBtnExp.Size = new System.Drawing.Size(23, 22);
            tsBtnExp.ToolTipText = "导入配置到Excel文件";
            tsBtnExp.Click += new System.EventHandler(this.tsBtnExp_Click);
            // 
            // tsBtnSave
            // 
            tsBtnSave.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            tsBtnSave.Image = ((System.Drawing.Image)(resources.GetObject("tsBtnSave.Image")));
            tsBtnSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            tsBtnSave.Name = "tsBtnSave";
            tsBtnSave.Size = new System.Drawing.Size(23, 22);
            tsBtnSave.ToolTipText = "立即保存";
            tsBtnSave.Click += new System.EventHandler(this.tsBtnSave_Click);
            // 
            // toolStripSeparator5
            // 
            toolStripSeparator5.Name = "toolStripSeparator5";
            toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton1
            // 
            toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            toolStripButton1.Image = global::FepManager.Properties.Resources._54;
            toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            toolStripButton1.Name = "toolStripButton1";
            toolStripButton1.Size = new System.Drawing.Size(23, 22);
            toolStripButton1.ToolTipText = "导入Excel文件中的配置信息";
            // 
            // toolBar
            // 
            this.toolBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            tsBtnAdd,
            tsBtnEdit,
            tsBtnDel,
            this.toolStripSeparator1,
            tsBtnSave,
            tsBtnExp,
            toolStripButton1,
            toolStripSeparator5,
            toolStripLabel1,
            this.tsTxtName,
            toolStripLabel4,
            this.tsCbxDevice,
            toolStripLabel5,
            this.tsCbxType});
            this.toolBar.Location = new System.Drawing.Point(0, 4);
            this.toolBar.Name = "toolBar";
            this.toolBar.Size = new System.Drawing.Size(1028, 25);
            this.toolBar.TabIndex = 1;
            this.toolBar.Text = "查询工具条";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // tsTxtName
            // 
            this.tsTxtName.Name = "tsTxtName";
            this.tsTxtName.Size = new System.Drawing.Size(100, 25);
            this.tsTxtName.TextChanged += new System.EventHandler(this.tsTxtName_TextChanged);
            // 
            // tsCbxDevice
            // 
            this.tsCbxDevice.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.tsCbxDevice.Name = "tsCbxDevice";
            this.tsCbxDevice.Size = new System.Drawing.Size(121, 25);
            this.tsCbxDevice.SelectedIndexChanged += new System.EventHandler(this.tsCbxDevice_SelectedIndexChanged);
            // 
            // tsCbxType
            // 
            this.tsCbxType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.tsCbxType.Name = "tsCbxType";
            this.tsCbxType.Size = new System.Drawing.Size(121, 25);
            this.tsCbxType.SelectedIndexChanged += new System.EventHandler(this.tsCbxType_SelectedIndexChanged);
            // 
            // dataGridView
            // 
            this.dataGridView.AllowUserToAddRows = false;
            this.dataGridView.AllowUserToOrderColumns = true;
            this.dataGridView.AutoGenerateColumns = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.name,
            this.desc,
            this.type,
            this.deviceid,
            this.address,
            this.scanintv,
            this.ctrlenable});
            this.dataGridView.DataSource = this.ttagBindingSource;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridView.DefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView.Location = new System.Drawing.Point(0, 29);
            this.dataGridView.MultiSelect = false;
            this.dataGridView.Name = "dataGridView";
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.dataGridView.RowTemplate.Height = 23;
            this.dataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView.Size = new System.Drawing.Size(1028, 322);
            this.dataGridView.TabIndex = 2;
            this.dataGridView.CellMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridView_CellMouseClick);
            // 
            // name
            // 
            this.name.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.name.DataPropertyName = "name";
            this.name.HeaderText = "变量名称";
            this.name.Name = "name";
            // 
            // desc
            // 
            this.desc.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.desc.DataPropertyName = "desc";
            this.desc.HeaderText = "变量描述";
            this.desc.Name = "desc";
            // 
            // type
            // 
            this.type.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.type.DataPropertyName = "type";
            this.type.HeaderText = "变量类型";
            this.type.Name = "type";
            // 
            // deviceid
            // 
            this.deviceid.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.deviceid.DataPropertyName = "device_id";
            this.deviceid.DataSource = this.fepCfg;
            this.deviceid.DisplayMember = "t_device.name";
            this.deviceid.HeaderText = "设备名称";
            this.deviceid.Name = "deviceid";
            this.deviceid.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.deviceid.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.deviceid.ValueMember = "t_device.id";
            // 
            // fepCfg
            // 
            this.fepCfg.DataSetName = "FepCfg";
            this.fepCfg.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // address
            // 
            this.address.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.address.DataPropertyName = "address";
            this.address.HeaderText = "设备地址";
            this.address.Name = "address";
            // 
            // scanintv
            // 
            this.scanintv.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.scanintv.DataPropertyName = "scan_intv";
            this.scanintv.HeaderText = "扫描周期";
            this.scanintv.Name = "scanintv";
            // 
            // ctrlenable
            // 
            this.ctrlenable.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ctrlenable.DataPropertyName = "ctrl_enable";
            this.ctrlenable.FalseValue = "0";
            this.ctrlenable.FillWeight = 50F;
            this.ctrlenable.HeaderText = "是否可控";
            this.ctrlenable.IndeterminateValue = "0";
            this.ctrlenable.Name = "ctrlenable";
            this.ctrlenable.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.ctrlenable.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.ctrlenable.TrueValue = "1";
            // 
            // ttagBindingSource
            // 
            this.ttagBindingSource.DataMember = "t_tag";
            this.ttagBindingSource.DataSource = this.fepCfg;
            // 
            // t_tagTableAdapter
            // 
            this.t_tagTableAdapter.ClearBeforeFill = true;
            // 
            // t_deviceTableAdapter
            // 
            this.t_deviceTableAdapter.ClearBeforeFill = true;
            // 
            // FormTagCfg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1028, 351);
            this.Controls.Add(this.dataGridView);
            this.Controls.Add(this.toolBar);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormTagCfg";
            this.ShowInTaskbar = false;
            this.Text = "变量配置";
            this.Load += new System.EventHandler(this.FormTagCfg_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormTagCfg_FormClosing);
            this.toolBar.ResumeLayout(false);
            this.toolBar.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fepCfg)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ttagBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolBar;
        private System.Windows.Forms.ToolStripTextBox tsTxtName;
        private System.Windows.Forms.ToolStripComboBox tsCbxDevice;
        private System.Windows.Forms.ToolStripComboBox tsCbxType;
        private System.Windows.Forms.DataGridView dataGridView;
        private DataSet.FepCfg fepCfg;
        private System.Windows.Forms.BindingSource ttagBindingSource;
        private DataSet.FepCfgTableAdapters.t_tagTableAdapter t_tagTableAdapter;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private DataSet.FepCfgTableAdapters.t_deviceTableAdapter t_deviceTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn name;
        private System.Windows.Forms.DataGridViewTextBoxColumn desc;
        private System.Windows.Forms.DataGridViewTextBoxColumn type;
        private System.Windows.Forms.DataGridViewComboBoxColumn deviceid;
        private System.Windows.Forms.DataGridViewTextBoxColumn address;
        private System.Windows.Forms.DataGridViewTextBoxColumn scanintv;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ctrlenable;
    }
}