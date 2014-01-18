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
                    throw new ArgumentException(String.Format("���Ӵ�[{0}]����Ҫ��ƥ��", s));

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

        [DescriptionAttribute("����ĸΪӢ���ַ�������ΪӢ�ġ����ֻ��»��ߣ���ͬһ�����в���������")
         , CategoryAttribute("\t��������"), DisplayNameAttribute("�豸����"), PropertyOrder(1), DefaultValue("Device?")]
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


        [CategoryAttribute("\t��������"), DisplayNameAttribute("�豸����"), PropertyOrder(2), DescriptionAttribute("�豸������"), DefaultValue("")]        
        public String Desc
        {
            get { return m_Row.desc; }
            set { m_Row.desc = value; }
        }

        [CategoryAttribute("\t��������"), DisplayNameAttribute("�ɼ�����"), PropertyOrder(3), DefaultValue(1000), DescriptionAttribute("��λ���롣")]
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

        [CategoryAttribute("\t��������"), DisplayNameAttribute("��Ӧ��ʱ"), PropertyOrder(4), DefaultValue(3000)
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

        [CategoryAttribute("\t��������"), DisplayNameAttribute("�����"), PropertyOrder(5), DefaultValue(1)
            , DescriptionAttribute("��ͬ����ŵ��豸�ǲ���ִ�вɼ����һ���Ӱ�죬ͬһ����ŵ��豸�Ǵ���ִ�еģ���һ���豸�ɼ���ɺ����ִ����һ���豸�Ĳɼ���")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 1,2,3,4,5,6,7,8,9,10 })]
        public Int64 Task
        {
            get { return m_Row.task; }
            set 
            { 
                m_Row.task = value; 
            }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("���ں�"), PropertyOrder(11), DefaultValue(1), DescriptionAttribute("�豸�����Ӵ��ںţ�1-65535��")]
        public Int64 Port
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

        [CategoryAttribute("��������"), DisplayNameAttribute("������"), PropertyOrder(12), DefaultValue(9600), DescriptionAttribute("�����ʡ�")
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

        [CategoryAttribute("��������"), DisplayNameAttribute("��żУ��"), PropertyOrder(13), DefaultValue(0), DescriptionAttribute("��żУ�顣\r\n* 0-��У��\r\n* 1-��У��\r\n* 2-żУ��")
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

        [CategoryAttribute("��������"), DisplayNameAttribute("����λ"), PropertyOrder(14), DefaultValue(8), DescriptionAttribute("����λ��")
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

        [CategoryAttribute("��������"), DisplayNameAttribute("ֹͣλ"), PropertyOrder(14), DefaultValue(1), DescriptionAttribute("����λ��")
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
