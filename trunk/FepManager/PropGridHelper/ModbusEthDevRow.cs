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
            try //若不符合规格，则重置！
            {
                ConvertFromRowConn(row.connparam);
            }
            catch(Exception ex)
            {
                if (row.connparam.Length != 0)
                    MessageBox.Show(ex.Message + "\r\n连接串重置！");
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
                    throw new ArgumentException(String.Format("连接串[{0}]与规格要求不匹配", s));

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

        [DescriptionAttribute("首字母为英文字符，其他为英文、数字或下划线，且同一驱动中不可重名。")
          , CategoryAttribute("基本属性"), DisplayNameAttribute("设备名称"), PropertyOrder(1), DefaultValue("modbus_Device?")]
        public String Name
	    {
		    get { return m_Row.name; }
		    set 
            {
                if (!HelperRegex.IsDevName(value))
                    throw new ArgumentException("请输入有效的【设备名】，首字母为英文字符，其他为英文、数字或下划线。");
                m_Row.name = value; 
            }
	    }


        [CategoryAttribute("基本属性"), DisplayNameAttribute("设备描述"), PropertyOrder(2),DescriptionAttribute("设备描述。"), DefaultValue("")]        
        public String Desc
        {
            get { return m_Row.desc; }
            set { m_Row.desc = value; }
        }

        [CategoryAttribute("连接属性"), DisplayNameAttribute("主设备地址"), PropertyOrder(3), DefaultValue("0.0.0.0"), DescriptionAttribute("有效IP地址或主机名。")]
        public String Address
        {
            get { return m_Address; }
            set 
            {
                if (!HelperRegex.IsHostName(value))
                    throw new ArgumentException("请输入有效的【设备名】，首字母为英文字符，其他为英文、数字或下划线。");
                m_Address = value; 
                ConvertToRowConn(); 
            }
        }

        [CategoryAttribute("连接属性"), DisplayNameAttribute("备设备地址"), PropertyOrder(4), DefaultValue(""), DescriptionAttribute("有效IP地址，若无冗余设备则不必填写。")]
        public String Address1
        {
            get { return m_Address1; }
            set 
            {
                if (value.Length > 0 && !HelperRegex.IsHostName(value))
                    throw new ArgumentException("请输入有效的【设备名】，首字母为英文字符，其他为英文、数字或下划线。");
                m_Address1 = value; 
                ConvertToRowConn(); 
            }
        }

        [CategoryAttribute("连接属性"), DisplayNameAttribute("端口号"), PropertyOrder(5), DefaultValue(502), DescriptionAttribute("设备的连接端口，1-65535。")]
        public Int32 Port
        {
            get { return m_Port; }
            set 
            { 
                if (!HelperRegex.IsRange(value, 1, 65535))
                    throw new ArgumentException("输入范围在1-65535。");
                m_Port = value;
                ConvertToRowConn(); 
            }
        }

        [CategoryAttribute("连接属性"), DisplayNameAttribute("支持多连接"), PropertyOrder(6), DefaultValue(true)
            , DescriptionAttribute("多连接设备是指在相同配置情况下，可由主备机各自与设备建立一个长连接。只有当前主机采集数据；"+
                "而当前备机只保持连接，当其成为主机时可迅速进行数据采集。一般来说，ModbusTCP均支持多连接，而ModbusRtu则为单连接。")]
        public Boolean IsMultilink
        {
            get { return m_IsMultilink; }
            set { m_IsMultilink = value; ConvertToRowConn(); }
        }

        [CategoryAttribute("基本属性"), DisplayNameAttribute("采集周期"), PropertyOrder(7), DefaultValue(1000), DescriptionAttribute("单位毫秒。")]
        public Int64 CycleRate
        {
            get { return m_Row.cyclerate; }
            set 
            { 
                if (!HelperRegex.IsRange(value, 200, 20000000))
                    throw new ArgumentException("输入范围在200-20000000。");
                m_Row.cyclerate = value;
            }
        }

        [CategoryAttribute("基本属性"), DisplayNameAttribute("响应超时"), PropertyOrder(8), DefaultValue(3000)
           , DescriptionAttribute("发送命令给设备后等待设备返回的超时时间，单位是毫秒。若响应超时，驱动会断开重连。超时时间设定越小，则检测重连越快。但设置时还需考虑网络的稳定性，因此并不建议设置过小。")]
        public Int64 RecvTimout
        {
            get { return m_Row.recvtimeout; }
            set 
            { 
                if (!HelperRegex.IsRange(value, 200, 20000000))
                    throw new ArgumentException("输入范围在200-20000000。");
                m_Row.recvtimeout = value;
            }
        }

        [CategoryAttribute("基本属性"), DisplayNameAttribute("任务号"), PropertyOrder(9), DefaultValue(1)
            ,DescriptionAttribute("不同任务号的设备是并行执行采集的且互不影响，同一任务号的设备是串行执行的，即一个设备采集完成后接着执行下一个设备的采集。")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 })]
        public Int64 Task
        {
            get { return m_Row.task; }
            set { m_Row.task = value; }
        }
    }
}
