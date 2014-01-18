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
    class ModbusRtuComDevRow
    {
        private DataSet.FepCfg.t_deviceRow m_Row = null;
        private Int64 m_Port = 1;
        private Int64 m_BaudRate = 9600;
        private Int64 m_CRC = 0;
        private Int64 m_DataBit = 8;
        private Int64 m_StopBit = 1;

        public ModbusRtuComDevRow(DataSet.FepCfg.t_deviceRow row)
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
            row.conntype = "Serial";
            row.param1 = row.param2 = row.param3 = "";
            
            if (row.IsdescNull())
                row.desc = "";
        }

        private void ConvertToRowConn()
        {
            m_Row.connparam = String.Format("serialport=COM{0};baudrate={1};parity={2};databits={3};stopbits={4};",
                m_Port, m_BaudRate, m_CRC, m_DataBit, m_StopBit);
        }

        private void ConvertFromRowConn(String s)
        {
            try
            {
                string strPatten = @"^serialport=COM(\d+);baudrate=(\d+);parity=([0-2]);databits=([5-8]);stopbits=([1-2]);$";
                Regex rex = new Regex(strPatten, RegexOptions.Singleline);
                MatchCollection matches = rex.Matches(m_Row.connparam);
                if (matches.Count < 1 || matches[0].Groups.Count != 6)
                    throw new ArgumentException(String.Format("连接串[{0}]与规格要求不匹配", s));

                GroupCollection groups = matches[0].Groups;
                m_Port = HelperRegex.Str2Int(groups[1].Value, 1);
                m_BaudRate = HelperRegex.Str2Int(groups[2].Value, 9600);
                m_CRC = HelperRegex.Str2Int(groups[3].Value, 0);
                m_DataBit = HelperRegex.Str2Int(groups[4].Value, 8);
                m_StopBit = HelperRegex.Str2Int(groups[5].Value, 1);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        [DescriptionAttribute("首字母为英文字符，其他为英文、数字或下划线，且同一驱动中不可重名。")
         , CategoryAttribute("\t基本属性"), DisplayNameAttribute("设备名称"), PropertyOrder(1), DefaultValue("Device?")]
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


        [CategoryAttribute("\t基本属性"), DisplayNameAttribute("设备描述"), PropertyOrder(2), DescriptionAttribute("设备描述。"), DefaultValue("")]        
        public String Desc
        {
            get { return m_Row.desc; }
            set { m_Row.desc = value; }
        }

        [CategoryAttribute("\t基本属性"), DisplayNameAttribute("采集周期"), PropertyOrder(3), DefaultValue(1000), DescriptionAttribute("单位毫秒。")]
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

        [CategoryAttribute("\t基本属性"), DisplayNameAttribute("响应超时"), PropertyOrder(4), DefaultValue(3000)
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

        [CategoryAttribute("\t基本属性"), DisplayNameAttribute("任务号"), PropertyOrder(5), DefaultValue(1)
            , DescriptionAttribute("不同任务号的设备是并行执行采集的且互不影响，同一任务号的设备是串行执行的，即一个设备采集完成后接着执行下一个设备的采集。")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 1,2,3,4,5,6,7,8,9,10 })]
        public Int64 Task
        {
            get { return m_Row.task; }
            set 
            { 
                m_Row.task = value; 
            }
        }

        [CategoryAttribute("连接属性"), DisplayNameAttribute("串口号"), PropertyOrder(11), DefaultValue(1), DescriptionAttribute("设备的连接串口号，1-65535。")]
        public Int64 Port
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

        [CategoryAttribute("连接属性"), DisplayNameAttribute("波特率"), PropertyOrder(12), DefaultValue(9600), DescriptionAttribute("波特率。")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 2400,4800,9600,19200,38400,57600,115200,230400 })]
        public Int64 BaudRate
        {
            get { return m_BaudRate; }
            set
            {
                m_BaudRate = value;
                ConvertToRowConn();
            }
        }

        [CategoryAttribute("连接属性"), DisplayNameAttribute("奇偶校验"), PropertyOrder(13), DefaultValue(0), DescriptionAttribute("奇偶校验。\r\n* 0-无校验\r\n* 1-奇校验\r\n* 2-偶校验")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 0, 1, 2 })]
        public Int64 CRC
        {
            get { return m_CRC; }
            set
            {
                m_CRC = value;
                ConvertToRowConn();
            }
        }

        [CategoryAttribute("连接属性"), DisplayNameAttribute("数据位"), PropertyOrder(14), DefaultValue(8), DescriptionAttribute("数据位。")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 5, 6, 7, 8 })]
        public Int64 DataBit
        {
            get { return m_DataBit; }
            set
            {
                m_DataBit = value;
                ConvertToRowConn();
            }
        }

        [CategoryAttribute("连接属性"), DisplayNameAttribute("停止位"), PropertyOrder(14), DefaultValue(1), DescriptionAttribute("数据位。")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 1, 2 })]
        public Int64 StopBit
        {
            get { return m_StopBit; }
            set
            {
                m_StopBit = value;
                ConvertToRowConn();
            }
        }
    }
}
