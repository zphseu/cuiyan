namespace FepManager
{
    partial class DummyProperty
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DummyProperty));
            this.dataPropertyGrid = new LuisRuiz.DataPropertyGrid();
            this.SuspendLayout();
            // 
            // dataPropertyGrid
            // 
            this.dataPropertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataPropertyGrid.Location = new System.Drawing.Point(0, 3);
            this.dataPropertyGrid.Name = "dataPropertyGrid";
            this.dataPropertyGrid.Size = new System.Drawing.Size(208, 383);
            this.dataPropertyGrid.TabIndex = 0;
            // 
            // DummyProperty
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.ClientSize = new System.Drawing.Size(208, 389);
            this.Controls.Add(this.dataPropertyGrid);
            this.HideOnClose = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "DummyProperty";
            this.Padding = new System.Windows.Forms.Padding(0, 3, 0, 3);
            this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.DockRight;
            this.TabText = "属性窗口";
            this.Text = "属性窗口";
            this.ResumeLayout(false);

		}
		#endregion

        internal LuisRuiz.DataPropertyGrid dataPropertyGrid;





    }
}