namespace FepManager
{
    partial class DialogDriverSelect
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
            System.Windows.Forms.Button btnOK;
            System.Windows.Forms.Button btnCancel;
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.nameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.visbleDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.enableDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.descDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tdriverBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.dataSetFepCfg = new DataSet.FepCfg();
            this.t_driverTableAdapter = new DataSet.FepCfgTableAdapters.t_driverTableAdapter();
            btnOK = new System.Windows.Forms.Button();
            btnCancel = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tdriverBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetFepCfg)).BeginInit();
            this.SuspendLayout();
            // 
            // btnOK
            // 
            btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            btnOK.Location = new System.Drawing.Point(85, 312);
            btnOK.Name = "btnOK";
            btnOK.Size = new System.Drawing.Size(88, 30);
            btnOK.TabIndex = 1;
            btnOK.Text = "确认";
            btnOK.UseVisualStyleBackColor = true;
            btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            btnCancel.Location = new System.Drawing.Point(272, 312);
            btnCancel.Name = "btnCancel";
            btnCancel.Size = new System.Drawing.Size(88, 30);
            btnCancel.TabIndex = 2;
            btnCancel.Text = "取消";
            btnCancel.UseVisualStyleBackColor = true;
            // 
            // dataGridView
            // 
            this.dataGridView.AllowUserToAddRows = false;
            this.dataGridView.AllowUserToDeleteRows = false;
            this.dataGridView.AllowUserToOrderColumns = true;
            this.dataGridView.AutoGenerateColumns = false;
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.nameDataGridViewTextBoxColumn,
            this.visbleDataGridViewTextBoxColumn,
            this.enableDataGridViewTextBoxColumn,
            this.descDataGridViewTextBoxColumn});
            this.dataGridView.DataSource = this.tdriverBindingSource;
            this.dataGridView.Location = new System.Drawing.Point(12, 12);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.RowTemplate.Height = 23;
            this.dataGridView.Size = new System.Drawing.Size(438, 288);
            this.dataGridView.TabIndex = 0;
            this.dataGridView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_CellValueChanged);
            // 
            // nameDataGridViewTextBoxColumn
            // 
            this.nameDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.nameDataGridViewTextBoxColumn.DataPropertyName = "name";
            this.nameDataGridViewTextBoxColumn.HeaderText = "名称";
            this.nameDataGridViewTextBoxColumn.Name = "nameDataGridViewTextBoxColumn";
            this.nameDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // visbleDataGridViewTextBoxColumn
            // 
            this.visbleDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.visbleDataGridViewTextBoxColumn.DataPropertyName = "visble";
            this.visbleDataGridViewTextBoxColumn.FalseValue = "0";
            this.visbleDataGridViewTextBoxColumn.FillWeight = 75F;
            this.visbleDataGridViewTextBoxColumn.HeaderText = "可见";
            this.visbleDataGridViewTextBoxColumn.IndeterminateValue = "-1";
            this.visbleDataGridViewTextBoxColumn.Name = "visbleDataGridViewTextBoxColumn";
            this.visbleDataGridViewTextBoxColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.visbleDataGridViewTextBoxColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.visbleDataGridViewTextBoxColumn.TrueValue = "1";
            // 
            // enableDataGridViewTextBoxColumn
            // 
            this.enableDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.enableDataGridViewTextBoxColumn.DataPropertyName = "enable";
            this.enableDataGridViewTextBoxColumn.FalseValue = "0";
            this.enableDataGridViewTextBoxColumn.FillWeight = 75F;
            this.enableDataGridViewTextBoxColumn.HeaderText = "有效";
            this.enableDataGridViewTextBoxColumn.IndeterminateValue = "-1";
            this.enableDataGridViewTextBoxColumn.Name = "enableDataGridViewTextBoxColumn";
            this.enableDataGridViewTextBoxColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.enableDataGridViewTextBoxColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.enableDataGridViewTextBoxColumn.TrueValue = "1";
            // 
            // descDataGridViewTextBoxColumn
            // 
            this.descDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.descDataGridViewTextBoxColumn.DataPropertyName = "desc";
            this.descDataGridViewTextBoxColumn.FillWeight = 200F;
            this.descDataGridViewTextBoxColumn.HeaderText = "描述";
            this.descDataGridViewTextBoxColumn.Name = "descDataGridViewTextBoxColumn";
            this.descDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // tdriverBindingSource
            // 
            this.tdriverBindingSource.DataMember = "t_driver";
            this.tdriverBindingSource.DataSource = this.dataSetFepCfg;
            // 
            // dataSetFepCfg
            // 
            this.dataSetFepCfg.DataSetName = "DataSetFepCfg";
            this.dataSetFepCfg.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // t_driverTableAdapter
            // 
            this.t_driverTableAdapter.ClearBeforeFill = true;
            // 
            // DialogDriverSelect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(462, 357);
            this.Controls.Add(btnCancel);
            this.Controls.Add(btnOK);
            this.Controls.Add(this.dataGridView);
            this.Name = "DialogDriverSelect";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "驱动选择";
            this.TopMost = true;
            this.Load += new System.EventHandler(this.DrvValidForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tdriverBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataSetFepCfg)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView;
        private DataSet.FepCfg dataSetFepCfg;
        private System.Windows.Forms.BindingSource tdriverBindingSource;
        private DataSet.FepCfgTableAdapters.t_driverTableAdapter t_driverTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn nameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn visbleDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewCheckBoxColumn enableDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn descDataGridViewTextBoxColumn;
    }
}