using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using System.IO;

namespace FepManager
{
    internal partial class FormBase : DockContent
    {
        internal MainForm main;
        public FormBase()
        {
            InitializeComponent();
        }

		protected override string GetPersistString()
		{
			return GetType().ToString();
		}

        private void FormBase_Load(object sender, EventArgs e)
        {
            main = (MainForm)ParentForm;
        }

        private void menuItemClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void menuItemCloseAll_Click(object sender, EventArgs e)
        {
            main.CloseAllDockContent(false);
        }

        private void menuItemCloseAllButThisOne_Click(object sender, EventArgs e)
        {
            main.CloseAllDockContent(true);
        }
    }
}