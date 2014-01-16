using System;
using System.Data;
using System.Configuration;
using System.ComponentModel;
using System.Text.RegularExpressions;
using LuisRuiz;

namespace FepManager.PropGridHelper
{
    [TypeConverter(typeof(PropertySorter))]
    internal class ModbusTcpBlockRow : _ModbusBlockRow
    {
        public ModbusTcpBlockRow(DataSet.FepCfg.t_datablockRow row)
            : base(row)
        {
        }
    }

    [TypeConverter(typeof(PropertySorter))]
    internal class ModbusRtuEthBlockRow : _ModbusBlockRow
    {
        public ModbusRtuEthBlockRow(DataSet.FepCfg.t_datablockRow row)
            : base(row)
        {
        }
    }

    [TypeConverter(typeof(PropertySorter))]
    internal class ModbusRtuComBlockRow : _ModbusBlockRow
    {
        public ModbusRtuComBlockRow(DataSet.FepCfg.t_datablockRow row)
            : base(row)
        {
        }
    }

    [TypeConverter(typeof(PropertySorter))]
    class _ModbusBlockRow
    {
        private DataSet.FepCfg.t_datablockRow m_Row = null;

        private Int32 m_numBase = 400000;
        private Int16 m_maxLength = 125;
        private String m_Type = "AO";
        private Int32 m_StarAddress = 400000;
        private Int16 m_StationId = 1;

        public _ModbusBlockRow(DataSet.FepCfg.t_datablockRow row)
	    {
		    m_Row = row;

            if (row.IsdescNull()) row.desc = "";
            // 直接使用
            // Phase row.phase; // Task row.task; // CycleRate row.cyclerate; // Name row.name;
            // Desc row.desc; // Count row.elemcount;

            // 需要转换
            // row.type row.elemcount;
            if (row.type == "AO" || row.type == "AI" || row.type == "DI" || row.type == "DO") 
                m_Type = row.type;

            // StartAddress row.address;
            if (HelperRegex.IsInt(row.address))
                m_StarAddress = Convert.ToInt32(row.address);
            
            //StationId row.param1;
            if (!row.Isparam1Null() && row.param1.Length > 0 && HelperRegex.IsInt(row.param1))
                m_StationId = Convert.ToInt16(row.param1);

            TheType = m_Type;

            // 不需要的
            row.param2 = row.param3 = "";
        }

        [DescriptionAttribute("首字母为英文字符，其他为英文、数字或下划线，且同设备动中不可重名。")
         , CategoryAttribute("基本属性"), DisplayNameAttribute("名称"), PropertyOrder(1), DefaultValue("DB?")]
        public String Name
	    {
		    get { return m_Row.name; }
		    set 
            {
                if (!HelperRegex.IsDevName(value))
                    throw new ArgumentException("请输入有效的【数据块名】，首字母为英文字符，其他为英文、数字或下划线。");
                m_Row.name = value; 
            }
	    }

        [CategoryAttribute("基本属性"), DisplayNameAttribute("描述"), PropertyOrder(2), DescriptionAttribute("数据块描述。"), DefaultValue("")]        
        public String Desc
        {
            get { return m_Row.desc; }
            set { m_Row.desc = value; }
        }

        [CategoryAttribute("数据属性"), DisplayNameAttribute("站号"), PropertyOrder(3), DefaultValue(1)
            , DescriptionAttribute("所属站号。")]
        public Int16 StationId
        {
            get { return m_StationId; }
            set
            {
                if (!HelperRegex.IsRange(value, 1, 255))
                    throw new ArgumentException("输入范围在1-255。");
                m_StationId = value;
                m_Row.param1 = value.ToString();
            }
        }

        [CategoryAttribute("数据属性"), DisplayNameAttribute("类型"), PropertyOrder(4), DefaultValue("AO"), DescriptionAttribute("数据块类型。")
          , TypeConverter(typeof(StringListConverter)), StringListAttribute(new String[] { "AO", "AI", "DI", "DO" })]
        public String TheType
        {
            get { return m_Type; }
            set
            {
                m_Type = value;
                m_Row.type = m_Type;

                if (value == "AO" || value == "AI")
                {
                    m_maxLength = 125;
                    m_Row.elembytes = 2;
                    Count = 120;
                }
                else
                {
                    m_maxLength = 1000;
                    m_Row.elembytes = 1;
                    Count = 1000;
                }

                if (value == "AO")
                    StartAddress = m_numBase = 400000;
                else if (value == "AI")
                    StartAddress = m_numBase = 300000;
                else if (value == "DO")
                    StartAddress = m_numBase = 100000;
                else if (value == "DI")
                    StartAddress = m_numBase = 000000;
            }
        }

        [CategoryAttribute("数据属性"), DisplayNameAttribute("起始地址"), PropertyOrder(5), DefaultValue(1000), DescriptionAttribute("单位毫秒。")]
        public Int32 StartAddress
        {
            get { return m_StarAddress; }
            set
            {
                if (!HelperRegex.IsRange(value, m_numBase, m_numBase + 65534))
                    throw new ArgumentException(String.Format("输入范围在{0}-{1}。", m_numBase, m_numBase + 65534));
                m_StarAddress = value;
                m_Row.address = value.ToString();
            }
        }

        [CategoryAttribute("数据属性"), DisplayNameAttribute("寄存器数"), PropertyOrder(6), DefaultValue(1000), DescriptionAttribute("寄存器个数。")]
        public Int64 Count
        {
            get { return m_Row.elemcount; }
            set
            {
                int leftLen = m_numBase + 65535 - m_StarAddress;
                int theLen = (m_maxLength > leftLen) ? leftLen : m_maxLength;
                if (!HelperRegex.IsRange(value, 1, theLen))
                    throw new ArgumentException(String.Format("输入范围在1-{0}。", theLen));
                m_Row.elemcount = value;
            }
        }

        [CategoryAttribute("扫描属性"), DisplayNameAttribute("扫描周期"), PropertyOrder(7), DefaultValue(1000), DescriptionAttribute("单位毫秒。")]
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

        [CategoryAttribute("扫描属性"), DisplayNameAttribute("扫描相位"), PropertyOrder(8), DefaultValue(1000), DescriptionAttribute("单位毫秒。")]
        public Int64 Phase
        {
            get { return m_Row.phase; }
            set
            {
                if (!HelperRegex.IsRange(value, 0, (int)m_Row.cyclerate))
                    throw new ArgumentException(String.Format("输入范围在0-{0}。", m_Row.cyclerate));
                m_Row.phase = value;
            }
        }
        
        [CategoryAttribute("扫描属性"), DisplayNameAttribute("任务号"), PropertyOrder(9), DefaultValue(1)
            , DescriptionAttribute("不同任务号的设备是并行执行采集的且互不影响，同一任务号的设备是串行执行的，即一个设备采集完成后接着执行下一个设备的采集。")
            , TypeConverter(typeof(LongListConverter)), LongListAttribute(new Int64[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 })]
        public Int64 Task
        {
            get { return m_Row.task; }
            set { m_Row.task = value; }
        }
    }
}
