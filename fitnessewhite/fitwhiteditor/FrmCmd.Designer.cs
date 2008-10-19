namespace fitwhiteditor
{
    partial class FrmCmd
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.Label labelDesc;
            System.Windows.Forms.Label labelParam1;
            System.Windows.Forms.Label labelAction;
            System.Windows.Forms.Label labelObject;
            System.Windows.Forms.Button btnCancel;
            System.Windows.Forms.Button btnOK;
            this.txtDesc = new System.Windows.Forms.TextBox();
            this.cbAction = new System.Windows.Forms.ComboBox();
            this.cbObject = new System.Windows.Forms.ComboBox();
            this.txtParam = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.labelComment = new System.Windows.Forms.Label();
            this.txtComment = new System.Windows.Forms.TextBox();
            labelDesc = new System.Windows.Forms.Label();
            labelParam1 = new System.Windows.Forms.Label();
            labelAction = new System.Windows.Forms.Label();
            labelObject = new System.Windows.Forms.Label();
            btnCancel = new System.Windows.Forms.Button();
            btnOK = new System.Windows.Forms.Button();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // labelDesc
            // 
            labelDesc.AutoSize = true;
            labelDesc.Dock = System.Windows.Forms.DockStyle.Fill;
            labelDesc.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            labelDesc.Location = new System.Drawing.Point(3, 81);
            labelDesc.Name = "labelDesc";
            labelDesc.Size = new System.Drawing.Size(74, 77);
            labelDesc.TabIndex = 6;
            labelDesc.Text = "描述(&D)";
            // 
            // labelParam1
            // 
            labelParam1.AutoSize = true;
            labelParam1.Dock = System.Windows.Forms.DockStyle.Fill;
            labelParam1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            labelParam1.Location = new System.Drawing.Point(3, 54);
            labelParam1.Name = "labelParam1";
            labelParam1.Size = new System.Drawing.Size(74, 27);
            labelParam1.TabIndex = 4;
            labelParam1.Text = "参数(&P)";
            // 
            // labelAction
            // 
            labelAction.AutoSize = true;
            labelAction.Dock = System.Windows.Forms.DockStyle.Fill;
            labelAction.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            labelAction.Location = new System.Drawing.Point(3, 27);
            labelAction.Name = "labelAction";
            labelAction.Size = new System.Drawing.Size(74, 27);
            labelAction.TabIndex = 2;
            labelAction.Text = "动作(&A)";
            // 
            // labelObject
            // 
            labelObject.AutoSize = true;
            labelObject.Dock = System.Windows.Forms.DockStyle.Fill;
            labelObject.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            labelObject.Location = new System.Drawing.Point(3, 0);
            labelObject.Name = "labelObject";
            labelObject.Size = new System.Drawing.Size(74, 27);
            labelObject.TabIndex = 0;
            labelObject.Text = "对象(&O)";
            // 
            // btnCancel
            // 
            btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            btnCancel.Dock = System.Windows.Forms.DockStyle.Fill;
            btnCancel.Location = new System.Drawing.Point(191, 3);
            btnCancel.Name = "btnCancel";
            btnCancel.Size = new System.Drawing.Size(84, 23);
            btnCancel.TabIndex = 1;
            btnCancel.Text = "取消(&C)";
            btnCancel.UseVisualStyleBackColor = true;
            btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnOK
            // 
            btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            btnOK.Dock = System.Windows.Forms.DockStyle.Fill;
            btnOK.Location = new System.Drawing.Point(56, 3);
            btnOK.Name = "btnOK";
            btnOK.Size = new System.Drawing.Size(84, 23);
            btnOK.TabIndex = 0;
            btnOK.Text = "确定(&Y)";
            btnOK.UseVisualStyleBackColor = true;
            btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // txtDesc
            // 
            this.txtDesc.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtDesc.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtDesc.Location = new System.Drawing.Point(83, 84);
            this.txtDesc.Multiline = true;
            this.txtDesc.Name = "txtDesc";
            this.txtDesc.Size = new System.Drawing.Size(253, 71);
            this.txtDesc.TabIndex = 7;
            // 
            // cbAction
            // 
            this.cbAction.DisplayMember = "name";
            this.cbAction.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cbAction.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbAction.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbAction.FormattingEnabled = true;
            this.cbAction.Location = new System.Drawing.Point(83, 30);
            this.cbAction.Name = "cbAction";
            this.cbAction.Size = new System.Drawing.Size(253, 25);
            this.cbAction.Sorted = true;
            this.cbAction.TabIndex = 3;
            this.cbAction.ValueMember = "id";
            this.cbAction.SelectedIndexChanged += new System.EventHandler(this.cbAction_SelectedIndexChanged);
            // 
            // cbObject
            // 
            this.cbObject.DisplayMember = "name";
            this.cbObject.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cbObject.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbObject.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbObject.FormattingEnabled = true;
            this.cbObject.Location = new System.Drawing.Point(83, 3);
            this.cbObject.Name = "cbObject";
            this.cbObject.Size = new System.Drawing.Size(253, 25);
            this.cbObject.Sorted = true;
            this.cbObject.TabIndex = 1;
            this.cbObject.ValueMember = "id";
            this.cbObject.SelectedIndexChanged += new System.EventHandler(this.cbObject_SelectedIndexChanged);
            // 
            // txtParam
            // 
            this.txtParam.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtParam.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtParam.Location = new System.Drawing.Point(83, 57);
            this.txtParam.Name = "txtParam";
            this.txtParam.Size = new System.Drawing.Size(253, 23);
            this.txtParam.TabIndex = 5;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 5;
            this.tableLayoutPanel1.SetColumnSpan(this.tableLayoutPanel2, 2);
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 35F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 90F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 90F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 35F));
            this.tableLayoutPanel2.Controls.Add(btnCancel, 3, 0);
            this.tableLayoutPanel2.Controls.Add(btnOK, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 238);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(333, 29);
            this.tableLayoutPanel2.TabIndex = 16;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 80F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.txtDesc, 1, 3);
            this.tableLayoutPanel1.Controls.Add(labelDesc, 0, 3);
            this.tableLayoutPanel1.Controls.Add(labelParam1, 0, 2);
            this.tableLayoutPanel1.Controls.Add(labelAction, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.cbAction, 1, 1);
            this.tableLayoutPanel1.Controls.Add(labelObject, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.cbObject, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.txtParam, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.labelComment, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.txtComment, 1, 4);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 6;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(339, 270);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // labelComment
            // 
            this.labelComment.AutoSize = true;
            this.labelComment.Location = new System.Drawing.Point(3, 158);
            this.labelComment.Name = "labelComment";
            this.labelComment.Size = new System.Drawing.Size(32, 17);
            this.labelComment.TabIndex = 8;
            this.labelComment.Text = "说明";
            // 
            // txtComment
            // 
            this.txtComment.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtComment.Location = new System.Drawing.Point(83, 161);
            this.txtComment.Multiline = true;
            this.txtComment.Name = "txtComment";
            this.txtComment.ReadOnly = true;
            this.txtComment.Size = new System.Drawing.Size(253, 71);
            this.txtComment.TabIndex = 8;
            // 
            // FrmCmd
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(339, 270);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "FrmCmd";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "指令编辑";
            this.Load += new System.EventHandler(this.FrmCmd_Load);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TextBox txtDesc;
        private System.Windows.Forms.ComboBox cbAction;
        private System.Windows.Forms.ComboBox cbObject;
        private System.Windows.Forms.TextBox txtParam;
        private System.Windows.Forms.Label labelComment;
        private System.Windows.Forms.TextBox txtComment;

    }
}