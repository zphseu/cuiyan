using System;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;
using fit;

namespace fitwhiteditor
{
    internal partial class FrmFitEditor : Form
    {
        private Parse tables;
        private string fixtureFileName;
        private FitWhiteCfg cfg;

        public FrmFitEditor(string fixtureFileName)
        {
            InitializeComponent();
            this.fixtureFileName = fixtureFileName;
        }

        private void FrmFitEditor_Load(object sender, EventArgs e)
        {
            listView.Items.Clear();
            StreamReader reader = null;
            try
            {
                reader = new StreamReader(fixtureFileName, Encoding.Unicode);
                string input = reader.ReadToEnd();
                tables = new Parse(input);
                Parse rows = tables.parts;
                while (rows != null && rows.more != null)
                {
                    Parse more = rows.more;
                    listView.Items.Add(new Command(more).ListViewItem);
                    rows = more;
                }

                using (FileStream fs = new FileStream("fitwhite.editor.config",
                    FileMode.Open, FileAccess.Read, FileShare.None))
                {
                    XmlSerializer xs = new XmlSerializer(typeof(FitWhiteCfg));
                    cfg = (FitWhiteCfg)xs.Deserialize(fs);
                }
            }
            catch
            {
            }
            finally
            {
                if (reader != null)   reader.Close();
            }
        }

        private void btnInsert_Click(object sender, EventArgs e)
        {
            int index = (listView.SelectedIndices.Count <= 0) ? 
                listView.Items.Count - 1 :listView.SelectedIndices[0];

            Command cmd = new Command();
            if (new FrmCmd(cmd, cfg).ShowDialog() == DialogResult.OK)
            {
                listView.Items.Insert(index + 1, cmd.ListViewItem);
            }
        }

        private void btnModify_Click(object sender, EventArgs e)
        {
            if (listView.SelectedIndices.Count <= 0) return;
            ListViewItem item = listView.SelectedItems[0];

            Command cmd = new Command(item);
            
            if (new FrmCmd(cmd, cfg).ShowDialog() == DialogResult.OK)
            {
                cmd.ListViewItem = item;
            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (listView.SelectedIndices.Count <= 0) return;
            ListViewItem item = listView.SelectedItems[0];
            Command cmd = new Command(item);

            if (MessageBox.Show(string.Format("你确定要删除[{0}:{1}-{2}]这个命令吗？", cmd.Object, cmd.Action, cmd.Param),
                "删除命令", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                item.Remove();
            }
        }

        private void btnUp_Click(object sender, EventArgs e)
        {
            if (listView.SelectedIndices.Count <= 0) return;
            int index = listView.SelectedIndices[0];
            if (index <= 0) return;
            ListViewItem p = listView.Items[index];
            p.Remove();
            listView.Items.Insert(index - 1, p);
            listView.FocusedItem = p;
            listView.Focus();
        }

        private void btnDown_Click(object sender, EventArgs e)
        {
            if (listView.SelectedIndices.Count <= 0) return;
            int index = listView.SelectedIndices[0];
            if (index >= listView.Items.Count - 1) return;
            ListViewItem p = listView.Items[index];
            p.Remove();
            listView.Items.Insert(index + 1, p);
            listView.FocusedItem = p;
            listView.Focus();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                File.Copy(fixtureFileName, fixtureFileName + ".bak", true);
            }
            catch
            {
            }

            StreamWriter output = new StreamWriter(fixtureFileName, false, Encoding.Unicode);
            output.WriteLine("<html><head><title>fitnessewhite</title></head><body><table border=\"1\">");
            output.WriteLine("  <tr><td colspan=\"4\">fitnessewhite.Guifixture</td></tr>");
            foreach (ListViewItem item in listView.Items)
            {
                Command cmd = new Command(item);
                cmd.ParseToHtml();
                output.WriteLine(string.Format("  <tr><td>{0}</td><td>{1}</td><td>{2}</td><td>{3}</td></tr>",
                    cmd.Object, cmd.Action, cmd.Param, cmd.Desc));
            }
            output.WriteLine("</table></body></html>");
            output.Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void listView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listView.SelectedIndices.Count <= 0)
            {
                btnUp.Enabled = false;
                btnDown.Enabled = false;
            }
            else
            {
                int index = listView.SelectedIndices[0];
                btnUp.Enabled = (index > 0);
                btnDown.Enabled = (index < listView.Items.Count - 1);
            }
        }

        private void listView_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            listView.SelectedIndices.Clear();
            listView.SelectedIndices.Add(e.Index);
            listView.FocusedItem = listView.Items[e.Index];
            listView.Focus();
        }

        private void btnRun_Click(object sender, EventArgs e)
        {
            btnOK_Click(sender, e);
            string resultFile = fixtureFileName.Remove(fixtureFileName.LastIndexOf('.')) + ".result.html";
            String[] argv = { fixtureFileName, resultFile, "." };
            new fitnessewhite.FitRunner().run(argv);
            try
            {
                System.Diagnostics.Process.Start(resultFile);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void FrmFitEditor_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop, false))
            {
                e.Effect = DragDropEffects.All;
            }
        }

        private void FrmFitEditor_DragDrop(object sender, DragEventArgs e)
        {
            this.fixtureFileName  = ((string[])e.Data.GetData(DataFormats.FileDrop))[0];
            FrmFitEditor_Load(sender, e);
        }
    }
}
