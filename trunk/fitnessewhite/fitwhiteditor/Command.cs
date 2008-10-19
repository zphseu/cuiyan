using fit;
using System.Windows.Forms;

namespace fitwhiteditor
{
    class Command
    {
        public Command()
        {
        }

        public Command(Parse row)
        {
            _object = row.parts.text();
            _action = row.parts.more.text();
            _param = row.parts.more.more.text();
            _desc = "";
            try
            {
                _desc = row.parts.more.more.more.text();
            }
            catch
            {
            }
        }

        public Command(ListViewItem item)
        {
            int i = 0;
            _object = item.SubItems[i++].Text;
            _action = item.SubItems[i++].Text;
            _param = item.SubItems[i++].Text;
            _desc = item.SubItems[i++].Text;
        }

        public ListViewItem ListViewItem
        {
            get
            {
                int i = 1;
                ListViewItem lvi = new ListViewItem(_object);
                SetListViewSubItemText(lvi, i++, _action);
                SetListViewSubItemText(lvi, i++, _param);
                SetListViewSubItemText(lvi, i++, _desc);
                return lvi;
            }
            set
            {
                int i = 0;
                SetListViewSubItemText(value, i++, _object);
                SetListViewSubItemText(value, i++, _action);
                SetListViewSubItemText(value, i++, _param);
                SetListViewSubItemText(value, i++, _desc);
            }
        }

        public void ParseToHtml()
        {
            if (string.IsNullOrEmpty(_object))
                _object = "&nbsp;";
            if (string.IsNullOrEmpty(_action))
                _action = "&nbsp;";
            if (string.IsNullOrEmpty(_param))
                _param = "&nbsp;";
            if (string.IsNullOrEmpty(_desc))
                _desc = "&nbsp;";
        }

        private void SetListViewSubItemText(ListViewItem lvi, int index, string text)
        {
            if (lvi.SubItems.Count < index + 1)
                lvi.SubItems.Add(text);
            else
                lvi.SubItems[index].Text = text;
        }

        private string _object;

        public string Object
        {
            get { return _object; }
            set { _object = value; }
        }
        private string _action;

        public string Action
        {
            get { return _action; }
            set { _action = value; }
        }

        private string _param;

        public string Param
        {
            get { return _param; }
            set { _param = value; }
        }


        private string _desc;

        public string Desc
        {
            get { return _desc; }
            set { _desc = value; }
        }
    }
}
