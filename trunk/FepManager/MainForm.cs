using System;
using System.Data;
using System.Data.SQLite;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Reflection;
using System.Windows.Forms;
using System.IO;
using WeifenLuo.WinFormsUI.Docking;

namespace FepManager
{
    internal partial class MainForm : Form
    {
        private bool m_bSaveLayout = true;
        private DeserializeDockContent m_deserializeDockContent;
        private DummyExplorer m_explorerWindow = new DummyExplorer();
        private DummyProperty m_propertyWindow = new DummyProperty();
        private DummyOutput m_outputWindow = new DummyOutput();
        private SQLiteConnection sqlConnection = new SQLiteConnection();
        private String dbFileName;

        internal MainForm()
        {
            InitializeComponent();
            m_deserializeDockContent = new DeserializeDockContent(GetContentFromPersistString);
            dockPanel.DocumentStyle = DocumentStyle.DockingMdi;
        }

        #region Methods

        internal SQLiteConnection SqlLiteConnection
        {
            get { return sqlConnection; }
        }

        internal void SetPropertyGridRow(DataRow row, String field, String dispname, String category, String description, String order, String readOnly)
        {
            m_propertyWindow.dataPropertyGrid.MuestraDatos(row, field, dispname, category, description, order, readOnly);
        }

        internal void SetPropertyGridRow(DataRow row)
        {
            m_propertyWindow.dataPropertyGrid.MuestraDatos(row);
        }

        internal void SetPropertyGridObject(Object obj)
        {
            m_propertyWindow.dataPropertyGrid.SelectedObject = obj;
        }

        private DockContent FindDockContent(string text)
        {
            foreach (IDockContent content in dockPanel.Documents)
                if (content.DockHandler.TabText == text)
                    return (DockContent)content;
            return null;
        }

        internal void CloseAllDockContent(Boolean bButThisOne)
        {
            foreach (IDockContent document in dockPanel.DocumentsToArray())
            {
                if (document.DockHandler.IsActivated && bButThisOne)
                    continue;
                document.DockHandler.Close();
            }
        }

        internal void OpenDockContent(String formName, String text, Object obj)
        {
            DockContent document = FindDockContent(text);
            if (document == null)
            {
                Assembly _assembly = Assembly.GetExecutingAssembly();
                document = (DockContent)_assembly.CreateInstance(formName);
                if (document != null)
                {
                    document.Text = text;
                    document.Tag = obj;
                    document.DockHandler.TabText = text;
                    document.Show(dockPanel);
                }
                else
                {
                    MessageBox.Show(String.Format("Œ¥ƒ‹’“µΩ≈‰÷√¥∞ø⁄ [{0}]£°", formName));
                }
            }
            else
            {
                document.Show(dockPanel);
            }
        }

        private IDockContent GetContentFromPersistString(string persistString)
        {
            if (persistString == typeof(DummyExplorer).ToString())
                return m_explorerWindow;
            else if (persistString == typeof(DummyProperty).ToString())
                return m_propertyWindow;
            else if (persistString == typeof(DummyOutput).ToString())
                return m_outputWindow;
            else
                return null;
        }

        private void _OpenCfgFile(String filename)
        {
            if (dbFileName == filename)
                return;

            bool dbOpened = false;
            sqlConnection.Close();
            dbFileName = filename;

            sqlConnection.ConnectionString = "synchronous=Full;data source=" + filename;

            try
            {
                sqlConnection.Open();
                dbFileName = filename;
                dbOpened = true;
            }
            catch (Exception e)
            {
                if (filename.Length != 0)
                    MessageBox.Show(e.Message);
            }

            m_explorerWindow.UpdateTreeNode(sqlConnection, filename);
            toolBarButtonSave.Enabled = toolBarButtonDriverSelect.Enabled  = toolBarButtonChannelSelect.Enabled = dbOpened;
            menuItemSave.Enabled = menuItemDriver.Enabled = menuItemChannel.Enabled = dbOpened;
        }

        #endregion

        #region Event Handlers

        private void MainForm_Load(object sender, System.EventArgs e)
        {
            string configFile = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "DockPanel.config");

            if (File.Exists(configFile))
                dockPanel.LoadFromXml(configFile, m_deserializeDockContent);

            _OpenCfgFile("");
        }

        private void menuItemExit_Click(object sender, System.EventArgs e)
        {
            Close();
        }

        private void menuItemSolutionExplorer_Click(object sender, System.EventArgs e)
        {
            m_explorerWindow.Show(dockPanel);
        }

        private void menuItemPropertyWindow_Click(object sender, System.EventArgs e)
        {
            m_propertyWindow.Show(dockPanel);
        }

        private void menuItemOutputWindow_Click(object sender, System.EventArgs e)
        {
            m_outputWindow.Show(dockPanel);
        }

        private void menuItemAbout_Click(object sender, System.EventArgs e)
        {
            DialogAbout aboutDialog = new DialogAbout();
            aboutDialog.ShowDialog(this);
        }

        private void menuItemNew_Click(object sender, System.EventArgs e)
        {
            if (saveFileDialog.ShowDialog() != DialogResult.OK)
                return;

            Assembly _assembly = System.Reflection.Assembly.GetExecutingAssembly();
            Stream sStream = _assembly.GetManifestResourceStream("FepManager.Resources.default.repo");
            if (sStream == null)
                return;

            byte[] buffer = new byte[sStream.Length];
            sStream.Read(buffer, 0, buffer.Length);
            FileStream fs = new FileStream(saveFileDialog.FileName, FileMode.OpenOrCreate, FileAccess.Write);
            fs.Write(buffer, 0, buffer.Length);
            fs.Flush();
            fs.Close();
            _OpenCfgFile(saveFileDialog.FileName);
        }

        private void menuItemOpen_Click(object sender, System.EventArgs e)
        {
            if (openFileDialog.ShowDialog() == DialogResult.OK)
                _OpenCfgFile(openFileDialog.FileName);
        }

        private void menuItemSave_Click(object sender, EventArgs e)
        {
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                File.Copy(dbFileName, saveFileDialog.FileName, true);
                _OpenCfgFile(saveFileDialog.FileName);
            }
        }

        private void MainForm_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            string configFile = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "DockPanel.config");
            if (m_bSaveLayout)
                dockPanel.SaveAsXml(configFile);
            else if (File.Exists(configFile))
                File.Delete(configFile);

            sqlConnection.Close();
        }

        private void menuItemToolBar_Click(object sender, System.EventArgs e)
        {
            toolBar.Visible = menuItemToolBar.Checked = !menuItemToolBar.Checked;
        }

        private void menuItemStatusBar_Click(object sender, System.EventArgs e)
        {
            statusBar.Visible = menuItemStatusBar.Checked = !menuItemStatusBar.Checked;
        }

        private void toolBar_ButtonClick(object sender, System.Windows.Forms.ToolStripItemClickedEventArgs e)
        {
            if (e.ClickedItem == toolBarButtonNew)
                menuItemNew_Click(null, null);
            else if (e.ClickedItem == toolBarButtonOpen)
                menuItemOpen_Click(null, null);
            else if (e.ClickedItem == toolBarButtonSave)
                menuItemSave_Click(null, null);
            else if (e.ClickedItem == toolBarButtonSolutionExplorer)
                menuItemSolutionExplorer_Click(null, null);
            else if (e.ClickedItem == toolBarButtonPropertyWindow)
                menuItemPropertyWindow_Click(null, null);
            else if (e.ClickedItem == toolBarButtonOutputWindow)
                menuItemOutputWindow_Click(null, null);
            else if (e.ClickedItem == toolBarButtonDriverSelect)
                menuItemDriver_Click(null, null);
            else if (e.ClickedItem == toolBarButtonChannelSelect)
                menuItemChannel_Click(null, null);
            else if (e.ClickedItem == toolBarButtonAbout)
                menuItemAbout_Click(null, null);
        }

        private void menuItemTools_Popup(object sender, System.EventArgs e)
        {
            menuItemLockLayout.Checked = !this.dockPanel.AllowEndUserDocking;
        }

        private void menuItemLockLayout_Click(object sender, System.EventArgs e)
        {
            dockPanel.AllowEndUserDocking = !dockPanel.AllowEndUserDocking;
        }

        private void menuItemShowDocumentIcon_Click(object sender, System.EventArgs e)
        {
            dockPanel.ShowDocumentIcon = menuItemShowDocumentIcon.Checked = !menuItemShowDocumentIcon.Checked;
        }

        private void menuItemDriver_Click(object sender, EventArgs e)
        {
            DialogDriverSelect dlg = new DialogDriverSelect();
            if (dlg.ShowDialog(this) == DialogResult.OK)
                m_explorerWindow.UpdateTreeNode(sqlConnection, dbFileName);
        }

        private void menuItemChannel_Click(object sender, EventArgs e)
        {
            //MessageBox.Show("Not implemented!");
            FormBase form = new FormBase();
            form.Text = "Hello";
            form.MdiParent = this;
            form.Show();
        }

        #endregion
    }
}