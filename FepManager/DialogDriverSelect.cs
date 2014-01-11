using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SQLite;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace FepManager
{
    internal partial class DialogDriverSelect : Form
    {
        public DialogDriverSelect()
        {
            InitializeComponent();
        }

        private void DrvValidForm_Load(object sender, EventArgs e)
        {
            MainForm parentForm = (MainForm)Owner;
            if (parentForm.SqlLiteConnection.State != ConnectionState.Open)
                return;
            t_driverTableAdapter.Connection = parentForm.SqlLiteConnection;
            tdriverBindingSource.Filter = "preserve = 1";
            t_driverTableAdapter.Fill(dataSetFepCfg.t_driver);
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                t_driverTableAdapter.Update(dataSetFepCfg);
            }
            catch (Exception Error)
            {
                MessageBox.Show(Error.Message);
            }
        }

        private void dataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && e.ColumnIndex == 1)
            {
                DataGridViewCell selectCell = dataGridView[e.ColumnIndex, e.RowIndex];
                if ((short)selectCell.Value == 0)
                {
                    DataGridViewCell validCell = dataGridView[e.ColumnIndex + 1, e.RowIndex];
                    validCell.Value = 0;
                }
            }
        }
    }
}