using System;
using System.Data;
using System.ComponentModel;
using System.Globalization;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using LuisRuiz;

namespace FepManager.PropGridHelper
{
    [TypeConverter(typeof(PropertySorter))]
    internal class ModbusTcpDevRow : _ModbusEthDevRow
    {
        public ModbusTcpDevRow(DataSet.FepCfg.t_deviceRow row)
            : base(row)
        {
            row.param1 = "1";
        }
    }

    [TypeConverter(typeof(PropertySorter))]
    internal class ModbusRtuEthDevRow : _ModbusEthDevRow
    {
        public ModbusRtuEthDevRow(DataSet.FepCfg.t_deviceRow row)
            : base(row)
        {
            row.param1 = "";
        }
    }

    [TypeConverter(typeof(PropertySorter))]
    class _ModbusEthDevRow
    {
        protected DataSet.FepCfg.t_deviceRow m_Row = null;
        protected String m_Address = "0.0.0.0";
        protected String m_Address1 = "";
        protected Int32 m_Port = 502;
        protected Boolean m_IsMultilink = true;

        public _ModbusEthDevRow(DataSet.FepCfg.t_deviceRow row)
	    {
		    m_Row = row;
            try //�������Ϲ�������ã�
            {
                ConvertFromRowConn(row.connparam);
            }
            catch(Exception ex)
            {
                if (row.connparam.Length != 0)
                    MessageBox.Show(ex.Message + "\r\n���Ӵ����ã�");
                ConvertToRowConn();
            }
            row.conntype = "TCPClient";
            row.param1 = "1";
            row.param2 = "";
            row.param3 = "";
            
            if (row.IsdescNull())
                row.desc = "";
        }

        private void ConvertToRowConn()
        {
            m_Row.connparam = String.Format("ip={0}{1};port={2};multiLink={3};", m_Address, (m_Address1.Length > 0) ? "/" + m_Address1 : "", m_Port, m_IsMultilink ? "1" : "0");
        }

        private void ConvertFromRowConn(String s)
        {
            try
            {
                string strPatten = @"^ip=(\S[^/]+)(/*)(\S*);port=(\d+);multiLink=([01]);$";
                Regex rex = new Regex(strPatten, RegexOptions.Singleline);
                MatchCollection matches = rex.Matches(s);
                if (matches.Count < 1 || matches[0].Groups.Count != 6)
                    throw new ArgumentException(String.Format("���Ӵ�[{0}]����Ҫ��ƥ��", s));

                GroupCollection groups = matches[0].Groups;
                m_Address = groups[1].Value;
                m_Address1 = groups[3].Value;
                m_Port = HelperRegex.Str2Int(groups[4].Value, 502);
                m_IsMultilink = Int32.Parse(groups[5].Value) == 1;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        [DescriptionAttribute("����ĸΪӢ���ַ�������ΪӢ�ġ����ֻ��»��ߣ���ͬһ�����в���������")
          , CategoryAttribute("��������"), DisplayNameAttribute("�豸����"), PropertyOrder(1), DefaultValue("modbus_Device?")]
        public String Name
	    {
		    get { return m_Row.name; }
		    set 
            {
                if (!HelperRegex.IsDevName(value))
                    throw new ArgumentException("��������Ч�ġ��豸����������ĸΪӢ���ַ�������ΪӢ�ġ����ֻ��»��ߡ�");
                m_Row.name = value; 
            }
	    }


        [CategoryAttribute("��������"), DisplayNameAttribute("�豸����"), PropertyOrder(2),DescriptionAttribute("�豸������"), DefaultValue("")]        
        public String Desc
        {
            get { return m_Row.desc; }
            set { m_Row.desc = value; }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("���豸��ַ"), PropertyOrder(3), DefaultValue("0.0.0.0"), DescriptionAttribute("��ЧIP��ַ����������")]
        public String Address
        {
            get { return m_Address; }
            set 
            {
                if (!HelperRegex.IsHostName(value))
                    throw new ArgumentException("��������Ч�ġ��豸����������ĸΪӢ���ַ�������ΪӢ�ġ����ֻ��»��ߡ�");
                m_Address = value; 
                ConvertToRowConn(); 
            }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("���豸��ַ"), PropertyOrder(4), DefaultValue(""), DescriptionAttribute("��ЧIP��ַ�����������豸�򲻱���д��")]
        public String Address1
        {
            get { return m_Address1; }
            set 
            {
                if (value.Length > 0 && !HelperRegex.IsHostName(value))
                    throw new ArgumentException("��������Ч�ġ��豸����������ĸΪӢ���ַ�������ΪӢ�ġ����ֻ��»��ߡ�");
                m_Address1 = value; 
                ConvertToRowConn(); 
            }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("�˿ں�"), PropertyOrder(5), DefaultValue(502), DescriptionAttribute("�豸�����Ӷ˿ڣ�1-65535��")]
        public Int32 Port
        {
            get { return m_Port; }
            set 
            { 
                if (!HelperRegex.IsRange(value, 1, 65535))
                    throw new ArgumentException("���뷶Χ��1-65535��");
                m_Port = value;
                ConvertToRowConn(); 
            }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("֧�ֶ�����"), PropertyOrder(6), DefaultValue(true)
            , DescriptionAttribute("�������豸��ָ����ͬ��������£������������������豸����һ�������ӡ�ֻ�е�ǰ�����ɼ����ݣ�"+
                "����ǰ����ֻ�������ӣ������Ϊ����ʱ��Ѹ�ٽ������ݲɼ���һ����˵��ModbusTCP��֧�ֶ����ӣ���ModbusRtu��Ϊ�����ӡ�")]
        public Boolean IsMultilink
        {
            get { return m_IsMultilink; }
            set { m_IsMultilink = value; ConvertToRowConn(); }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("�ɼ�����"), PropertyOrder(7), DefaultValue(1000), DescriptionAttribute("��λ���롣")]
        public Int64 CycleRate
        {
            get { return m_Row.cyclerate; }
            set 
            { 
                if (!HelperRegex.IsRange(value, 200, 20000000))
                    throw new ArgumentException("���뷶Χ��200-20000000��");
                m_Row.cyclerate = value;
            }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("��Ӧ��ʱ"), PropertyOrder(8), DefaultValue(3000)
           , DescriptionAttribute("����������豸��ȴ��豸���صĳ�ʱʱ�䣬��λ�Ǻ��롣����Ӧ��ʱ��������Ͽ���������ʱʱ���趨ԽС����������Խ�졣������ʱ���迼��������ȶ��ԣ���˲����������ù�С��")]
        public Int64 RecvTimout
        {
            get { return m_Row.recvtimeout; }
            set 
            { 
                if (!HelperRegex.IsRange(value, 200, 20000000))
                    throw new ArgumentException("���뷶Χ��200-20000000��");
                m_Row.recvtimeout = value;
            }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("�����"), PropertyOrder(9), DefaultValue(1)
            ,DescriptionAttribute("��ͬ����ŵ��豸�ǲ���ִ�вɼ����һ���Ӱ�죬ͬһ����ŵ��豸�Ǵ���ִ�еģ���һ���豸�ɼ���ɺ����ִ����һ���豸�Ĳɼ���")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 })]
        public Int64 Task
        {
            get { return m_Row.task; }
            set { m_Row.task = value; }
        }
    }
}
