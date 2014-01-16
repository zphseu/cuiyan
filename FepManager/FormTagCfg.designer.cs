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
            System.Windows.Forms.ToolStripButton tsBtnImp;
            System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormTagCfg));
            this.toolBar = new System.Windows.Forms.ToolStrip();
            this.tsTxtName = new System.Windows.Forms.ToolStripTextBox();
            this.tsCbxDevice = new System.Windows.Forms.ToolStripComboBox();
            this.tsCbxType = new System.Windows.Forms.ToolStripComboBox();
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.nameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.descDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.type = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.deviceidDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.addressDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.scanintvDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ctrlenableDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ttagBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.fepCfg = new DataSet.FepCfg();
            this.t_tagTableAdapter = new DataSet.FepCfgTableAdapters.t_tagTableAdapter();
            toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            toolStripLabel5 = new System.Windows.Forms.ToolStripLabel();
            tsBtnAdd = new System.Windows.Forms.ToolStripButton();
            tsBtnEdit = new System.Windows.Forms.ToolStripButton();
            tsBtnDel = new System.Windows.Forms.ToolStripButton();
            tsBtnExp = new System.Windows.Forms.ToolStripButton();
            tsBtnImp = new System.Windows.Forms.ToolStripButton();
            toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolBar.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ttagBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fepCfg)).BeginInit();
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
            // tsBtnImp
            // 
            tsBtnImp.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            tsBtnImp.Image = global::FepManager.Properties.Resources._54;
            tsBtnImp.ImageTransparentColor = System.Drawing.Color.Magenta;
            tsBtnImp.Name = "tsBtnImp";
            tsBtnImp.Size = new System.Drawing.Size(23, 22);
            tsBtnImp.ToolTipText = "导入Excel文件中的配置信息";
            tsBtnImp.Click += new System.EventHandler(this.tsBtnImp_Click);
            // 
            // toolStripSeparator5
            // 
            toolStripSeparator5.Name = "toolStripSeparator5";
            toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // toolBar
            // 
            this.toolBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            tsBtnAdd,
            tsBtnEdit,
            tsBtnDel,
            tsBtnExp,
            tsBtnImp,
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
            this.dataGridView.AllowUserToDeleteRows = false;
            this.dataGridView.AllowUserToOrderColumns = true;
            this.dataGridView.AutoGenerateColumns = false;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.nameDataGridViewTextBoxColumn,
            this.descDataGridViewTextBoxColumn,
            this.type,
            this.deviceidDataGridViewTextBoxColumn,
            this.addressDataGridViewTextBoxColumn,
            this.scanintvDataGridViewTextBoxColumn,
            this.ctrlenableDataGridViewTextBoxColumn});
            this.dataGridView.DataSource = this.ttagBindingSource;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridView.DefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView.Location = new System.Drawing.Point(0, 29);
            this.dataGridView.MultiSelect = false;
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.ReadOnly = true;
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.dataGridView.RowTemplate.Height = 23;
            this.dataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridView.Size = new System.Drawing.Size(1028, 322);
            this.dataGridView.TabIndex = 2;
            this.dataGridView.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_CellDoubleClick);
            // 
            // nameDataGridViewTextBoxColumn
            // 
            this.nameDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.nameDataGridViewTextBoxColumn.DataPropertyName = "name";
            this.nameDataGridViewTextBoxColumn.HeaderText = "变量名称";
            this.nameDataGridViewTextBoxColumn.Name = "nameDataGridViewTextBoxColumn";
            this.nameDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // descDataGridViewTextBoxColumn
            // 
            this.descDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.descDataGridViewTextBoxColumn.DataPropertyName = "desc";
            this.descDataGridViewTextBoxColumn.HeaderText = "变量描述";
            this.descDataGridViewTextBoxColumn.Name = "descDataGridViewTextBoxColumn";
            this.descDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // type
            // 
            this.type.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.type.DataPropertyName = "type";
            this.type.HeaderText = "变量类型";
            this.type.Name = "type";
            this.type.ReadOnly = true;
            // 
            // deviceidDataGridViewTextBoxColumn
            // 
            this.deviceidDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.deviceidDataGridViewTextBoxColumn.DataPropertyName = "device_id";
            this.deviceidDataGridViewTextBoxColumn.HeaderText = "设备名称";
            this.deviceidDataGridViewTextBoxColumn.Name = "deviceidDataGridViewTextBoxColumn";
            this.deviceidDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // addressDataGridViewTextBoxColumn
            // 
            this.addressDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.addressDataGridViewTextBoxColumn.DataPropertyName = "address";
            this.addressDataGridViewTextBoxColumn.HeaderText = "设备地址";
            this.addressDataGridViewTextBoxColumn.Name = "addressDataGridViewTextBoxColumn";
            this.addressDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // scanintvDataGridViewTextBoxColumn
            // 
            this.scanintvDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.scanintvDataGridViewTextBoxColumn.DataPropertyName = "scan_intv";
            this.scanintvDataGridViewTextBoxColumn.HeaderText = "扫描周期";
            this.scanintvDataGridViewTextBoxColumn.Name = "scanintvDataGridViewTextBoxColumn";
            this.scanintvDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // ctrlenableDataGridViewTextBoxColumn
            // 
            this.ctrlenableDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.ctrlenableDataGridViewTextBoxColumn.DataPropertyName = "ctrl_enable";
            this.ctrlenableDataGridViewTextBoxColumn.FalseValue = "0";
            this.ctrlenableDataGridViewTextBoxColumn.FillWeight = 50F;
            this.ctrlenableDataGridViewTextBoxColumn.HeaderText = "是否可控";
            this.ctrlenableDataGridViewTextBoxColumn.IndeterminateValue = "0";
            this.ctrlenableDataGridViewTextBoxColumn.Name = "ctrlenableDataGridViewTextBoxColumn";
            this.ctrlenableDataGridViewTextBoxColumn.ReadOnly = true;
            this.ctrlenableDataGridViewTextBoxColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.ctrlenableDataGridViewTextBoxColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.ctrlenableDataGridViewTextBoxColumn.TrueValue = "1";
            // 
            // ttagBindingSource
            // 
            this.ttagBindingSource.DataMember = "t_tag";
            this.ttagBindingSource.DataSource = this.fepCfg;
            // 
            // fepCfg
            // 
            this.fepCfg.DataSetName = "FepCfg";
            this.fepCfg.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // t_tagTableAdapter
            // 
            this.t_tagTableAdapter.ClearBeforeFill = true;
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
            this.toolBar.ResumeLayout(false);
            this.toolBar.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ttagBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fepCfg)).EndInit();
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
        private System.Windows.Forms.DataGridViewTextBoxColumn nameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn descDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn type;
        private System.Windows.Forms.DataGridViewTextBoxColumn deviceidDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn addressDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn scanintvDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ctrlenableDataGridViewTextBoxColumn;
    }
}