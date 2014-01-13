using System;
using System.Data;
using System.Configuration;
using System.ComponentModel;
using System.Text.RegularExpressions;
using LuisRuiz;

namespace FepManager.PropGridHelper
{
    [TypeConverter(typeof(PropertySorter))]
    class ModbusBlockRow
    {
        private DataSet.FepCfg.t_datablockRow m_Row = null;
        
        private Int32 m_numBase = 0;
        private Int16 m_maxLength = 0;

        public enum ConnectType { AO, AI, DI, DO };
        private String[] ConnectTypeString = { "AO", "AI", "DI", "DO" };

        public ModbusBlockRow(DataSet.FepCfg.t_datablockRow row)
	    {
		    m_Row = row;

            if (row.IsdescNull()) row.desc = "";
            // ֱ��ʹ��
            // Phase row.phase;
            // Task row.task;
            // CycleRate row.cyclerate;
            // Name row.name;
            // Desc row.desc;
            // Count row.elemcount;

            // ��Ҫת��
            // Type row.type and row.elembytes;
            for (int i = 0; i < ConnectTypeString.Length; i++)
            {
                if (row.type != ConnectTypeString[i])
                    continue;
                MyType = (ConnectType)i; //ͬʱ������row.elembytes
                break;
            }
            // StartAddress row.address;
            m_StarAddress = m_numBase;
            if (HelperRegex.IsInt(row.address))
            {
                m_StarAddress = Convert.ToInt32(row.address);
                if (m_StarAddress < m_numBase)
                    m_StarAddress = m_numBase;
                if (m_StarAddress > m_numBase + 65534)
                    m_StarAddress = m_numBase + 65534;
            }
            StartAddress = m_StarAddress;

            //StationId row.param1;
            m_StationId = 1;
            if (!row.Isparam1Null() && row.param1.Length > 0 && HelperRegex.IsInt(row.param1))
            {
                m_StationId = Convert.ToInt16(row.param1);
                if (m_StationId < 1)
                    m_StationId = 1;
                if (m_StationId > 255)
                    m_StationId = 255;
            }
            StationId = m_StationId;

            // ����Ҫ��
            row.param2 = row.param3 = "";
        }

        [DescriptionAttribute("����ĸΪӢ���ַ�������ΪӢ�ġ����ֻ��»��ߣ���ͬ�豸���в���������")
         , CategoryAttribute("��������"), DisplayNameAttribute("����"), PropertyOrder(1), DefaultValue("DB?")]
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

        [CategoryAttribute("��������"), DisplayNameAttribute("����"), PropertyOrder(2), DescriptionAttribute("���ݿ�������"), DefaultValue("")]        
        public String Desc
        {
            get { return m_Row.desc; }
            set { m_Row.desc = value; }
        }

        private Int16 m_StationId;
        [CategoryAttribute("��������"), DisplayNameAttribute("վ��"), PropertyOrder(3), DefaultValue(1)
            , DescriptionAttribute("����վ�š�")]
        public Int16 StationId
        {
            get { return m_StationId; }
            set
            {
                if (!HelperRegex.IsRange(value, 1, 255))
                    throw new ArgumentException("���뷶Χ��1-255��");
                m_StationId = value;
                m_Row.param1 = value.ToString();
            }
        }

        private ConnectType m_Type = ConnectType.AO;

        [CategoryAttribute("��������"), DisplayNameAttribute("����"), PropertyOrder(4), DefaultValue("AO"), DescriptionAttribute("���ݿ����͡�")]
        public ConnectType MyType
        {
            get { return m_Type; }
            set 
            {
                m_Type = value;
                if (value == ConnectType.AO)
                    m_numBase = 400000;
                else if (value == ConnectType.AI)
                    m_numBase = 300000;
                else if (value == ConnectType.DO)
                    m_numBase = 100000;
                else if (value == ConnectType.DI)
                    m_numBase = 000000;

                if (value == ConnectType.AO || value == ConnectType.AI)
                {
                    m_maxLength = 125;
                    m_Row.elembytes = 2;
                }
                else
                {
                    m_maxLength = 1000;
                    m_Row.elembytes = 1;
                }

                if (m_StarAddress < m_numBase)
                    StartAddress = m_numBase;
                if (m_StarAddress > m_numBase + 65534)
                    StartAddress = m_numBase + 65534;


                int leftLen = m_numBase + 65535 - m_StarAddress;
                Count = (m_maxLength > leftLen) ? leftLen : m_maxLength;

                m_Row.type = ConnectTypeString[Convert.ToInt32(m_Type)];               
            }
        }

        private Int32 m_StarAddress = 0;
        [CategoryAttribute("��������"), DisplayNameAttribute("��ʼ��ַ"), PropertyOrder(5), DefaultValue(1000), DescriptionAttribute("��λ���롣")]
        public Int32 StartAddress
        {
            get { return m_StarAddress; }
            set
            {
                if (!HelperRegex.IsRange(value, m_numBase, m_numBase + 65534))
                    throw new ArgumentException(String.Format("���뷶Χ��{0}-{1}��", m_numBase, m_numBase + 65534));
                m_StarAddress = value;
                int leftLen = m_numBase + 65535 - m_StarAddress;
                int theLen = (m_maxLength > leftLen) ? leftLen : m_maxLength;
                if (Count > theLen)
                    Count = theLen;
                m_Row.address = value.ToString();
            }
        }

        [CategoryAttribute("��������"), DisplayNameAttribute("�Ĵ�����"), PropertyOrder(6), DefaultValue(1000), DescriptionAttribute("�Ĵ���������")]
        public Int64 Count
        {
            get { return m_Row.elemcount; }
            set
            {
                int leftLen = m_numBase + 65535 - m_StarAddress;
                int theLen = (m_maxLength > leftLen) ? leftLen : m_maxLength;
                if (!HelperRegex.IsRange(value, 1, theLen))
                    throw new ArgumentException(String.Format("���뷶Χ��1-{0}��", theLen));
                m_Row.elemcount = value;
            }
        }

        [CategoryAttribute("ɨ������"), DisplayNameAttribute("ɨ������"), PropertyOrder(7), DefaultValue(1000), DescriptionAttribute("��λ���롣")]
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

        [CategoryAttribute("ɨ������"), DisplayNameAttribute("ɨ����λ"), PropertyOrder(8), DefaultValue(1000), DescriptionAttribute("��λ���롣")]
        public Int64 Phase
        {
            get { return m_Row.phase; }
            set
            {
                if (!HelperRegex.IsRange(value, 0, (int)m_Row.cyclerate))
                    throw new ArgumentException(String.Format("���뷶Χ��0-{0}��", m_Row.cyclerate));
                m_Row.phase = value;
            }
        }
        
        [CategoryAttribute("ɨ������"), DisplayNameAttribute("�����"), PropertyOrder(9), DefaultValue(1)
            , DescriptionAttribute("��ͬ����ŵ��豸�ǲ���ִ�вɼ����һ���Ӱ�죬ͬһ����ŵ��豸�Ǵ���ִ�еģ���һ���豸�ɼ���ɺ����ִ����һ���豸�Ĳɼ���")]
        public Int64 Task
        {
            get { return m_Row.task; }
            set
            {
                if (!HelperRegex.IsRange(value, 1, 10))
                    throw new ArgumentException("���뷶Χ��1-10��");
                m_Row.task = value;
            }
        }
    }
}
