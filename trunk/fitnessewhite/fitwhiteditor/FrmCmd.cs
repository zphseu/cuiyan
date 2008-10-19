using System;
using System.Collections.Generic;
using System.Reflection;
using System.Windows.Forms;
using fitnessewhite;

namespace fitwhiteditor
{
    internal partial class FrmCmd : Form
    {
        private FrmCmdShowMethods[] cfg;
        private Command cmd;

        public FrmCmd(Command cmd, FitWhiteCfg cfg)
        {
            InitializeComponent();
            this.cmd = cmd;
            if (cfg != null && cfg.FrmCmdCfg != null)
            this.cfg = cfg.FrmCmdCfg.FrmCmdShowMethods;
        }

        private void FrmCmd_Load(object sender, EventArgs e)
        {
            cbObject.Items.AddRange(Guifixture.GetFixtureNames().ToArray());

            if (cmd.Object != null && cbObject.Items.Contains(cmd.Object))
            {
                cbObject.Text = cmd.Object;
                cbAction.Text = cmd.Action;
                txtParam.Text = cmd.Param;
                txtDesc.Text = cmd.Desc;
            }
            else
                cbObject.SelectedIndex = -1;
        }

        private void cbObject_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbObject.SelectedIndex < 0) return;
            
            Dictionary<string, int> showMethods = new Dictionary<string, int>();
            if (cfg != null)
            {
                foreach (FrmCmdShowMethods theCfg in cfg)
                {
                    if (theCfg.ClassName != cbObject.Text || theCfg.MethodName == null) continue;
                    foreach (string s in theCfg.MethodName)
                        showMethods.Add(s, 0);
                    break;
                }
            }

            cbAction.Items.Clear();
            if (showMethods.Count > 0)
            {
                foreach (string s in Guifixture.GetMethodNames(cbObject.Text).ToArray())
                {
                    if (showMethods.ContainsKey(s))
                        cbAction.Items.Add(s);
                }
            }
            else
                cbAction.Items.AddRange(Guifixture.GetMethodNames(cbObject.Text).ToArray());

            if (!cbAction.Items.Contains(cbAction.Text))
                cbAction.SelectedIndex = -1;
        }

        private void cbAction_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbAction.Text== null) return;
            MethodInfo mi = Guifixture.GetMethod(cbObject.Text, cbAction.Text);
            if (mi == null) return;
            txtParam.Enabled = (mi.GetParameters().Length > 0 || mi.ReturnType != typeof(void));
            if (!txtParam.Enabled) txtParam.Text = "";

            object[] implAttributes = mi.GetCustomAttributes(typeof(MethodAttribute), false);
            List<string> ls = new List<string>();
            for(int i = 0; i <implAttributes.Length; i++)
            {
                MethodAttribute implAttribute = implAttributes[i] as MethodAttribute;
                if (implAttribute == null) continue;
                ls.Add(implAttribute.Name);
            }
            txtComment.Lines = ls.ToArray();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            cmd.Object = cbObject.Text;
            cmd.Action = cbAction.Text;
            cmd.Param = txtParam.Text;
            cmd.Desc = txtDesc.Text;
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
