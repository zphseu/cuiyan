using System;
using System.Collections.Generic;
using System.Data;
using System.Reflection;
using System.ComponentModel;
using LuisRuiz;

namespace FepManager.PropGridHelper
{
    [TypeConverter(typeof(PropertySorter))]
    class TagRow
    {
        private DataSet.FepCfg.t_tagRow m_Row = null;
        private Dictionary<String, DataSet.FepCfg.t_deviceRow> m_devNameList = null;
        private Dictionary<String, DataSet.FepCfg.t_tagtypeRow> m_typeNameList = null;
        private String m_Device = "";
        private String m_Type = "";
        private String m_Order = "";

        public TagRow(DataSet.FepCfg.t_tagRow row, Dictionary<String, DataSet.FepCfg.t_deviceRow> devNameList, Dictionary<String, DataSet.FepCfg.t_tagtypeRow> typeNameList)
	    {
		    m_Row = row;
            m_devNameList = devNameList;
            m_typeNameList = typeNameList;

            CtrlEnable = row.evtctrl_enable == 1;
            ScanEnable = row.scan_enable == 1;

            if (m_Row.IsdescNull())
                m_Row.desc = "";
            if (m_Row.IsaddressNull())
                m_Row.address = "";
            if (m_Row.Isparam3Null())
                m_Row.param3 = "";

            m_Order = m_Row.param3.Replace("{\"t\":\"", "").Replace("\"}", "");
            Device = m_Row.t_deviceRow.name;
            TheType = m_Row.t_tagtypeRow.name;

            _SetPropertyList("Device", m_devNameList.Keys);
            _SetPropertyList("TheType", m_typeNameList.Keys);
        }

        //http://www.codeproject.com/Articles/152945/Enabling-disabling-properties-at-runtime-in-the-Pr
        private void _SetReadOnlyProperty(String PropertyName, Boolean IsReadOnly)
        {
            PropertyDescriptor descriptor = TypeDescriptor.GetProperties(this.GetType())[PropertyName];
            ReadOnlyAttribute attribute = (ReadOnlyAttribute)descriptor.Attributes[typeof(ReadOnlyAttribute)];
            FieldInfo fieldToChange = attribute.GetType().GetField("isReadOnly", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance);
            fieldToChange.SetValue(attribute, IsReadOnly);
        }

        private void _SetPropertyList(String propertyName, ICollection<String> Lists)
        {
            List<String> s = new List<string>();
            foreach (String key in Lists)
                s.Add(key);
            _SetPropertyList(propertyName, s.ToArray());
        }

        private void _SetPropertyList(String propertyName, String[] Lists)
        {
            PropertyDescriptor descriptor = TypeDescriptor.GetProperties(this.GetType())[propertyName];
            StringListAttribute attribute = (StringListAttribute)descriptor.Attributes[typeof(StringListAttribute)];
            attribute.Lists = Lists;
        }

        [DescriptionAttribute("����ĸΪӢ���ַ�������ΪӢ�ġ����ֻ��»��ߣ���ͬ�豸���в���������")
        , CategoryAttribute("\t\t\t\t��������"), DisplayNameAttribute("��������"), PropertyOrder(1), DefaultValue("tag_?")]
        public String Name
	    {
		    get { return m_Row.name; }
		    set 
            {
                if (!HelperRegex.IsDevName(value))
                    throw new ArgumentException("��������Ч�ġ����ݿ�����������ĸΪӢ���ַ�������ΪӢ�ġ����ֻ��»��ߡ�");
                m_Row.name = value; 
            }
	    }

        [CategoryAttribute("\t\t\t\t��������"), DisplayNameAttribute("��������"), PropertyOrder(2), DescriptionAttribute("����������"), DefaultValue("")]
        public String Desc
        {
            get { return m_Row.desc; }
            set { m_Row.desc = value; }
        }

        [CategoryAttribute("\t\t\t\t��������"), DisplayNameAttribute("��������"), PropertyOrder(3), DescriptionAttribute("�������͡�"), DefaultValue(1)
            , TypeConverter(typeof(StringListConverter)), StringListAttribute(new String[] { "��δ���£�" })
            , RefreshProperties(RefreshProperties.All)]
        public String TheType
        {
            get { return m_Type; }
            set {
                
                if (m_Row.t_tagtypeRow != m_typeNameList[value])
                    m_Row.t_tagtypeRow = m_typeNameList[value];

                m_Type = value;
                Length = m_Row.t_tagtypeRow.length;
                _SetReadOnlyProperty("Length", Length > 0);

                Boolean b = false;
                String[] s = null;

                if (m_Row.t_tagtypeRow.length == 2)
                    s = new String[] { "12", "21" };
                else if (m_Row.t_tagtypeRow.length == 4)
                    s = new String[] { "1234", "2143", "3412", "4321" };
                else if (m_Row.t_tagtypeRow.length == 8)
                    s = new String[] { "12345678", "21436587", "34127856", "43218765", "56781234", "65872143", "78563412", "87654321" };
                else
                {
                    b = true;
                    s = new String[] {};
                }

                _SetPropertyList("Order", s);
                _SetReadOnlyProperty("Order", b);
            }
        }

        [CategoryAttribute("\t\t\t\t��������"), DisplayNameAttribute("��������"), PropertyOrder(4), DescriptionAttribute("�������ȡ�"), DefaultValue(0), ReadOnly(false)]
        public Int64 Length
        {
            get { return m_Row.length; }
            set { m_Row.length = value; }
        }

        [CategoryAttribute("\t\t\t�豸����"), DisplayNameAttribute("�豸����"), PropertyOrder(10), DescriptionAttribute("�豸���ơ�"), DefaultValue("")
            , TypeConverter(typeof(StringListConverter)), StringListAttribute(new String[] { "��δ���£�" })]
        public String Device
        {
            get { return m_Device; }
            set
            {
                if (m_Row.t_deviceRow != m_devNameList[value])
                    m_Row.t_deviceRow = m_devNameList[value];
                m_Device = value;
            }
        }

        [CategoryAttribute("\t\t\t�豸����"), DisplayNameAttribute("�豸��ַ"), PropertyOrder(11), DescriptionAttribute("�豸��ַ��"), DefaultValue(0)]
        public String Address
        {
            get { return m_Row.address; }
            set { m_Row.address = value; }
        }

        [CategoryAttribute("\t\t\t�豸����"), DisplayNameAttribute("�ֽ���"), PropertyOrder(12), DescriptionAttribute("�ֽ���"), DefaultValue(0), ReadOnly(false)
            , TypeConverter(typeof(StringListConverter)), StringListAttribute(new String[] { "��δ���£�" })]        
        public String Order
        {
            get { return m_Order; }
            set {
                m_Order = value;
                if (value == "12" || value == "1234" || value == "12345678")
                    m_Row.param3 = "";
                else
                    m_Row.param3 = "{\"t\":\""+value+"\"}";
            }
        }

        [CategoryAttribute("\t\t��������"), DisplayNameAttribute("�Ƿ�ɿ�"), PropertyOrder(20), DescriptionAttribute("�Ƿ�ɿء�")
            , ReadOnly(false), DefaultValue(false), RefreshProperties(RefreshProperties.All)]
        public Boolean CtrlEnable
        {
            get { return m_Row.ctrl_enable == 1; }
            set 
            {
                _SetReadOnlyProperty("EvtCtrlEnable", !value);
                _SetReadOnlyProperty("EvtCtrlPriority", !value);
                m_Row.ctrl_enable = (short)(value ? 1 : 0); 
            }
        }

        [CategoryAttribute("\t\t��������"), DisplayNameAttribute("�Ƿ��¼"), PropertyOrder(21), DescriptionAttribute("�Ƿ��¼��"), DefaultValue(true), ReadOnly(true)]        
        public Boolean EvtCtrlEnable
        {
            get { return m_Row.evtctrl_enable == 1; }
            set { m_Row.evtctrl_enable = (short)(value ? 1 : 0); }
        }

        [CategoryAttribute("\t\t��������"), DisplayNameAttribute("�¼�����"), PropertyOrder(22), DescriptionAttribute("�¼����𣬷�ΧΪ0 - 255��"), DefaultValue(3), ReadOnly(true)]        
        public Int64 EvtCtrlPriority
        {
            get { return m_Row.evtctrl_priority; }
            set {
                if (!HelperRegex.IsRange(value, 0, 255))
                    throw new ArgumentException("���뷶Χ��0-255��");
                m_Row.evtctrl_priority = value; 
            }
        }

        [CategoryAttribute("\tɨ������"), DisplayNameAttribute("�Ƿ�ɨ��"), PropertyOrder(30), DescriptionAttribute("�Ƿ�ɨ�衣")
           , ReadOnly(false), DefaultValue(true), RefreshProperties(RefreshProperties.All)]
        public Boolean ScanEnable
        {
            get { return m_Row.scan_enable == 1; }
            set {
                _SetReadOnlyProperty("ScanIntv", !value);
                _SetReadOnlyProperty("ScanPhase", !value);
                m_Row.scan_enable = (short)(value ? 1 : 0); 
            }
        }

        [CategoryAttribute("\tɨ������"), DisplayNameAttribute("ɨ������"), PropertyOrder(31), DescriptionAttribute("ɨ�����ڡ�"), DefaultValue(1000), ReadOnly(false)]
        public Int64 ScanIntv
        {
            get { return m_Row.scan_intv; }
            set { m_Row.scan_intv = value; }
        }

        [CategoryAttribute("\tɨ������"), DisplayNameAttribute("ɨ����λ"), PropertyOrder(32), DescriptionAttribute("ɨ����λ�����÷�Χ��0 - ɨ������ ֮�䡣"), DefaultValue(0), ReadOnly(false)]
        public Int64 ScanPhase
        {
            get { return m_Row.scan_phs; }
            set {
                if (!HelperRegex.IsRange(value, 0, (int)m_Row.scan_intv))
                    throw new ArgumentException(String.Format("���뷶Χ��0-{0}��",m_Row.scan_intv));
                m_Row.scan_phs = value; 
            }
        }

        [CategoryAttribute("��չ����"), DisplayNameAttribute("��չ����0"), PropertyOrder(40), DescriptionAttribute("��չ����0��"), DefaultValue(0)]
        public String Param0
        {
            get { return m_Row.param0; }
            set { m_Row.param0 = value; }
        }

        [CategoryAttribute("��չ����"), DisplayNameAttribute("��չ����1"), PropertyOrder(41), DescriptionAttribute("��չ����1��"), DefaultValue(0)]
        public String Param1
        {
            get { return m_Row.param1; }
            set { m_Row.param1 = value; }
        }

        [CategoryAttribute("��չ����"), DisplayNameAttribute("��չ����2"), PropertyOrder(42), DescriptionAttribute("��չ����2��"), DefaultValue(0)]
        public String Param2
        {
            get { return m_Row.param2; }
            set { m_Row.param2 = value; }
        }
    }
}
