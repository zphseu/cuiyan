using System;
using System.Collections.Generic;
using System.IO;

using NPOI.HSSF.UserModel;
using NPOI.HPSF;
using NPOI.SS.UserModel;

//using FepManager.DataSet.DataSetFepCfgTableAdapters;

namespace FepManager
{
    internal class HelperNPOI
    {
        #region Members
        private static readonly String[] DriverCfg_deviceColume = new String[] {"驱动名称", "设备名称(name)", "连接类型(conntype)", "连接参数(connparam)", "轮询周期[毫秒](cyclerate)",
            "响应超时[毫秒](recvtimeout)", "描述(desc)", "任务号(task)", "可选参数1(param1)", "可选参数2(param2)", "可选参数3(param3)"};
        private static readonly String[] DriverCfg_datablockeColume = new String[] { "驱动名称", "所属设备(device)", "名称(name)", "类型(type)", "地址(address)", "元素个数(elemcount)", 
            "元素大小[字节](elembytes)", "轮询周期[毫秒](cyclerate)", "相位(phase)", "任务号(task)", "描述(desc)", "可选参数1(param1)", "可选参数2(param2)", "可选参数3(param3)" };
        private static readonly String[] DriverCfg_SheetName = new String[] { "设备配置", "数据块配置" };
        private static readonly String[] Cfg_Version = new String[] { "版本号", "F.1.0.0" };

        private static readonly String TagCfg_SheetName = "变量配置";
        private static readonly String[] TagCfg_Colume = new String[] {"变量名称", "变量描述", "变量类型", "变量长度", 
            "设备名称", "设备地址", "是否可控", "是否记录", "事件级别", "是否扫描", "扫描周期", "扫描相位", "扩展属性0", "扩展属性1", "扩展属性2", "扩展属性3"};
        #endregion

        private static String GetCellString(IRow row, int index)
        {
            ICell cell = row.GetCell(index, MissingCellPolicy.CREATE_NULL_AS_BLANK);
            String val;
            if (cell.CellType == CellType.Numeric)
                val = cell.NumericCellValue.ToString();
            else if (cell.CellType == CellType.Boolean)
                val = cell.BooleanCellValue.ToString();
            else if (cell.CellType == CellType.String)
                val = cell.StringCellValue;
            else if (cell.CellType == CellType.Blank)
                val = "";
            else
                val = "NPOI Error";

            return val;
        }

        private static Int64 GetCellLong(IRow row, int index)
        {
            ICell cell = row.GetCell(index, MissingCellPolicy.CREATE_NULL_AS_BLANK);
            Int64 val;
            if (cell.CellType == CellType.Numeric)
                val = Convert.ToInt64(cell.NumericCellValue);
            else if (cell.CellType == CellType.Boolean)
                val = Convert.ToInt64(cell.BooleanCellValue);
            else if (cell.CellType == CellType.String)
                val = Convert.ToInt64(cell.StringCellValue);
            else if (cell.CellType == CellType.Blank)
                val = 0;
            else
                val = -1;

            return val;
        }

        public static void DriverCfgSaveTo(String filename, DataSet.FepCfg fepCfg)
        {
            if (fepCfg.t_device.Rows.Count <= 0)
                return;

            HSSFWorkbook hssfworkbook = new HSSFWorkbook();

            ////create a entry of DocumentSummaryInformation
            DocumentSummaryInformation dsi = PropertySetFactory.CreateDocumentSummaryInformation();
            dsi.Company = @"上海宝信软件股份有限公司";
            hssfworkbook.DocumentSummaryInformation = dsi;

            ////create a entry of SummaryInformation
            SummaryInformation si = PropertySetFactory.CreateSummaryInformation();
            si.Subject = @"BSFep驱动配置导出导入文件";
            hssfworkbook.SummaryInformation = si;

            //here, we must insert at least one sheet to the workbook. otherwise, Excel will say 'data lost in file'
            //So we insert three sheet just like what Excel does
            Int32 line = 0;
            ISheet sheet = hssfworkbook.CreateSheet(DriverCfg_SheetName[0]);
            // Line 1: 版本号	1.1.0
            IRow irow = sheet.CreateRow(line++);
            irow.CreateCell(0).SetCellValue(Cfg_Version[0]);
            irow.CreateCell(1).SetCellValue(Cfg_Version[1]);
            // Line 2: Empty
            sheet.CreateRow(line++);
            //Line 3: 驱动名称	设备名称(name)	连接类型(conntype)	连接参数(connparam)	轮询周期[毫秒](cyclerate) 响应超时[毫秒](recvtimeout)	描述(desc)	任务号(task)	可选参数1(param1)	可选参数2(param2)	可选参数3(param3)
            irow = sheet.CreateRow(line++);
            for (int j = 0; j < DriverCfg_deviceColume.Length; j++)
                irow.CreateCell(j).SetCellValue(DriverCfg_deviceColume[j]);
            // Line 4-: modbus	modbus_Device0	TCPClient	ip=iCV55-TEST-CY;port=502;multiLink=1;	1000 3000		1	1            
            foreach (DataSet.FepCfg.t_deviceRow row in fepCfg.t_device.Rows)
            {
                irow = sheet.CreateRow(line++);
                for (int i = 0; i < DriverCfg_deviceColume.Length; i++)
                    irow.CreateCell(i);

                irow.Cells[0].SetCellType(CellType.String);
                irow.Cells[0].SetCellValue(row.t_driverRow.name); //"驱动名称"
                irow.Cells[1].SetCellType(CellType.String);
                irow.Cells[1].SetCellValue(row.name); //"设备名称(name)"
                irow.Cells[2].SetCellType(CellType.String);
                irow.Cells[2].SetCellValue(row.conntype); //"连接类型(conntype)"
                irow.Cells[3].SetCellType(CellType.String);
                irow.Cells[3].SetCellValue(row.connparam); //"连接参数(connparam)"
                irow.Cells[4].SetCellType(CellType.String);
                irow.Cells[4].SetCellValue(row.cyclerate); //"轮询周期(cyclerate)"
                irow.Cells[5].SetCellType(CellType.Numeric);
                irow.Cells[5].SetCellValue(row.recvtimeout); //"响应超时[毫秒](recvtimeout)"
                irow.Cells[6].SetCellType(CellType.String);
                irow.Cells[6].SetCellValue(row.IsdescNull() ? "" : row.desc); //"描述(desc)"
                irow.Cells[7].SetCellType(CellType.Numeric);
                irow.Cells[7].SetCellValue(row.task); //"任务号(task)"
                irow.Cells[8].SetCellType(CellType.String);
                irow.Cells[8].SetCellValue(row.Isparam1Null() ? "" : row.param1); //"可选参数1(param1)"
                irow.Cells[9].SetCellType(CellType.String);
                irow.Cells[9].SetCellValue(row.Isparam2Null() ? "" : row.param2); //"可选参数2(param2)"
                irow.Cells[10].SetCellType(CellType.String);
                irow.Cells[10].SetCellValue(row.Isparam3Null() ? "" : row.param3); //"可选参数3(param3)"
            }

            line = 0;
            sheet = hssfworkbook.CreateSheet(DriverCfg_SheetName[1]);
            // Line 1: 版本号	1.1.0
            irow = sheet.CreateRow(line++);
            irow.CreateCell(0).SetCellValue(Cfg_Version[0]);
            irow.CreateCell(1).SetCellValue(Cfg_Version[1]);
            // Line 2: Empty
            sheet.CreateRow(line++);
            //Line 3: 驱动名称	设备名称(name)	连接类型(conntype)	连接参数(connparam)	响应超时[毫秒](recvtimeout)	描述(desc)	任务号(task)	可选参数1(param1)	可选参数2(param2)	可选参数3(param3)
            irow = sheet.CreateRow(line++);
            for (int j = 0; j < DriverCfg_datablockeColume.Length; j++)
                irow.CreateCell(j).SetCellValue(DriverCfg_datablockeColume[j]);
            // Line 4-: modbus	modbus_Device0	DB1	AO	400000	100	2	1000	0	1
            foreach (DataSet.FepCfg.t_datablockRow row in fepCfg.t_datablock.Rows)
            {
                irow = sheet.CreateRow(line++);
                if (row.t_deviceRow == null || row.t_deviceRow.t_driverRow == null)
                {
                    //cycy error;
                    continue;
                }
                for (int i = 0; i < DriverCfg_datablockeColume.Length; i++)
                    irow.CreateCell(i);
                irow.Cells[00].SetCellType(CellType.String);
                irow.Cells[00].SetCellValue(row.t_deviceRow.t_driverRow.name); //"驱动名称"
                irow.Cells[01].SetCellType(CellType.String);
                irow.Cells[01].SetCellValue(row.t_deviceRow.name); //"所属设备(device)"
                irow.Cells[02].SetCellType(CellType.String);
                irow.Cells[02].SetCellValue(row.name); //"名称(name)"
                irow.Cells[03].SetCellType(CellType.String);
                irow.Cells[03].SetCellValue(row.type); //"类型(type)"
                irow.Cells[04].SetCellType(CellType.String);
                irow.Cells[04].SetCellValue(row.address); //"地址(address)"
                irow.Cells[05].SetCellType(CellType.Numeric);
                irow.Cells[05].SetCellValue(row.elemcount); //"元素个数(elemcount)"
                irow.Cells[06].SetCellType(CellType.Numeric);
                irow.Cells[06].SetCellValue(row.elembytes); //"元素大小[字节](elembytes)"
                irow.Cells[07].SetCellType(CellType.Numeric);
                irow.Cells[07].SetCellValue(row.cyclerate); //"轮询周期[毫秒](cyclerate)"
                irow.Cells[08].SetCellType(CellType.Numeric);
                irow.Cells[08].SetCellValue(row.phase); //"相位(phase)"
                irow.Cells[09].SetCellType(CellType.Numeric);
                irow.Cells[09].SetCellValue(row.task); //"任务号(task)"
                irow.Cells[10].SetCellType(CellType.String);
                irow.Cells[10].SetCellValue(row.IsdescNull() ? "" : row.desc); //"描述(desc)"
                irow.Cells[11].SetCellType(CellType.String);
                irow.Cells[11].SetCellValue(row.Isparam1Null() ? "" : row.param1); //"可选参数1(param1)"
                irow.Cells[12].SetCellType(CellType.String);
                irow.Cells[12].SetCellValue(row.Isparam2Null() ? "" : row.param2); //"可选参数2(param2)"
                irow.Cells[13].SetCellType(CellType.String);
                irow.Cells[13].SetCellValue(row.Isparam3Null() ? "" : row.param3); //"可选参数3(param3)"
            }

            ((HSSFSheet)hssfworkbook.GetSheetAt(0)).AlternativeFormula = false;
            ((HSSFSheet)hssfworkbook.GetSheetAt(0)).AlternativeExpression = false;

            //Write the stream data of workbook to the root directory
            FileStream file = new FileStream(filename, FileMode.Create);
            hssfworkbook.Write(file);
            file.Close();
        }

        public static String DriverCfgLoadFrom(String filename, DataSet.FepCfg.t_driverRow drvRow, DataSet.FepCfg fepCfg)
        {
            Dictionary<String, DataSet.FepCfg.t_deviceRow> devDic = new Dictionary<String, DataSet.FepCfg.t_deviceRow>();
            Dictionary<String, DataSet.FepCfg.t_datablockRow> blockDic = new Dictionary<String, DataSet.FepCfg.t_datablockRow>();

            foreach (DataSet.FepCfg.t_deviceRow row in fepCfg.t_device)
                devDic[row.name] = row;

            foreach (DataSet.FepCfg.t_datablockRow row in fepCfg.t_datablock)
                blockDic[row.t_deviceRow.name + ":" + row.name] = row;

            // http://tonyqus.sinaapp.com/archives/270
            FileStream fileStream = new FileStream(filename, FileMode.Open);
            IWorkbook workbook = new HSSFWorkbook(fileStream);
            fileStream.Close();

            ISheet sheet1 = workbook.GetSheet(DriverCfg_SheetName[0]);
            ISheet sheet2 = workbook.GetSheet(DriverCfg_SheetName[1]);

            if (sheet1.GetRow(0).Cells[1].StringCellValue != Cfg_Version[1])
                throw new Exception(String.Format("表格[{0}]的版本[{1}]与本程序支持的[{2}]不匹配！", sheet1.SheetName, sheet1.GetRow(0).Cells[1].StringCellValue, Cfg_Version[1]));
            if (sheet2.GetRow(0).Cells[1].StringCellValue != Cfg_Version[1])
                throw new Exception(String.Format("表格[{0}]的版本[{1}]与本程序支持的[{2}]不匹配！", sheet2.SheetName, sheet2.GetRow(0).Cells[1].StringCellValue, Cfg_Version[1]));

            if (sheet1.GetRow(2).PhysicalNumberOfCells != DriverCfg_deviceColume.Length)
                throw new Exception(String.Format("表格[{0}]的数据列数为[{1}]，与本程序支持不匹配，请先确认导入文件版本！", sheet1.SheetName, sheet1.GetRow(2).PhysicalNumberOfCells));
            if (sheet2.GetRow(2).PhysicalNumberOfCells != DriverCfg_datablockeColume.Length)
                throw new Exception(String.Format("表格[{0}]的数据列数为[{1}]，与本程序支持不匹配，请先确认导入文件版本！", sheet2.SheetName, sheet2.GetRow(2).PhysicalNumberOfCells));

            String errList = "";
            for (Int32 line = 3; line < sheet1.PhysicalNumberOfRows; line++)
            {
                IRow irow = sheet1.GetRow(line);
                String TheDrvName = GetCellString(irow, 0);

                if (drvRow.name != TheDrvName)
                    continue;

                String name = GetCellString(irow, 1);
                String conntype = GetCellString(irow, 2);
                String connparam = GetCellString(irow, 3);
                Int64 cyclerate = GetCellLong(irow, 4);
                Int64 recvtimeout = GetCellLong(irow, 5);
                String desc = GetCellString(irow, 6);
                Int64 task = GetCellLong(irow, 7);
                String param1 = GetCellString(irow, 8);
                String param2 = GetCellString(irow, 9);
                String param3 = GetCellString(irow, 10);

                if (devDic.ContainsKey(name))
                {
                    DataSet.FepCfg.t_deviceRow row = devDic[name];
                    row.connparam = connparam;
                    row.conntype = conntype;
                    row.cyclerate = cyclerate;
                    row.recvtimeout = recvtimeout;
                    row.task = task;
                    row.desc = desc;
                    row.param1 = param1;
                    row.param2 = param2;
                    row.param3 = param3;
                }
                else
                {
                    if (fepCfg.t_device.Rows.Count < HelperConst.MAX_DEV_COUNT)
                    {
                        fepCfg.t_device.Addt_deviceRow(drvRow, name, connparam, conntype, cyclerate, recvtimeout, task, desc, param1, param2, param3);
                        devDic[name] = fepCfg.t_device.Rows[fepCfg.t_device.Rows.Count - 1] as DataSet.FepCfg.t_deviceRow;
                    }
                    if (fepCfg.t_device.Rows.Count == HelperConst.MAX_TAG_COUNT)
                    {
                        errList += String.Format("导入设备个数超过限制【{0}】，余下不在导入。", HelperConst.MAX_DEV_COUNT);
                    }
                }
            }

            for (Int32 line = 3; line < sheet2.PhysicalNumberOfRows; line++)
            {
                IRow irow = sheet2.GetRow(line);
                String TheDrvName = GetCellString(irow, 0);
                if (drvRow.name != TheDrvName)
                    continue;

                String devName = GetCellString(irow, 1);
                if (!devDic.ContainsKey(devName))
                    continue;

                //Addt_datablockRow(device, name2, type3, address4, cyclerate7, elembytes6, elemcount5, phase8, task9, desc10, param1 11, param2 12, param3 13)
                String name = GetCellString(irow, 2);
                String type = GetCellString(irow, 3);
                String address = GetCellString(irow, 4);
                Int64 elemcount = GetCellLong(irow, 5);
                Int64 elembytes = GetCellLong(irow, 6);
                Int64 cyclerate = GetCellLong(irow, 7);
                Int64 phase = GetCellLong(irow, 8);
                Int64 task = GetCellLong(irow, 9);
                String desc = GetCellString(irow, 10);
                String param1 = GetCellString(irow, 11);
                String param2 = GetCellString(irow, 12);
                String param3 = GetCellString(irow, 13);

                String key = devName + ":" + name;
                if (blockDic.ContainsKey(key))
                {
                    DataSet.FepCfg.t_datablockRow row = blockDic[key];
                    row.type = type;
                    row.address = address;
                    row.cyclerate = cyclerate;
                    row.elembytes = elembytes;
                    row.cyclerate = cyclerate;
                    row.phase = phase;
                    row.task = task;
                    row.desc = desc;
                    row.param1 = param1;
                    row.param2 = param2;
                    row.param3 = param3;
                }
                else
                {
                    fepCfg.t_datablock.Addt_datablockRow(devDic[devName],name, type, address, cyclerate,elembytes, elemcount, phase,
                        task, desc, param1, param2, param3);
                }
            }

            return errList;
        }

        public static void TagCfgSaveTo(String filename, DataSet.FepCfg.t_tagDataTable tagTable)
        {
            if (tagTable.Rows.Count <= 0)
                return;

            HSSFWorkbook hssfworkbook = new HSSFWorkbook();
            DocumentSummaryInformation dsi = PropertySetFactory.CreateDocumentSummaryInformation();
            dsi.Company = @"上海宝信软件股份有限公司";
            hssfworkbook.DocumentSummaryInformation = dsi;
            SummaryInformation si = PropertySetFactory.CreateSummaryInformation();
            si.Subject = @"BSFep驱动配置导出导入文件";
            hssfworkbook.SummaryInformation = si;

            Int32 line = 0;
            ISheet sheet = hssfworkbook.CreateSheet(TagCfg_SheetName);

            // Line 1: 版本号	1.1.0
            IRow irow = sheet.CreateRow(line++);
            irow.CreateCell(0).SetCellValue(Cfg_Version[0]);
            irow.CreateCell(1).SetCellValue(Cfg_Version[1]);

            // Line 2: Empty
            sheet.CreateRow(line++);

            //Line 3: TagCfg_Colume
            irow = sheet.CreateRow(line++);
            for (int j = 0; j < TagCfg_Colume.Length; j++)
                irow.CreateCell(j).SetCellValue(TagCfg_Colume[j]);

            // Line 4-:            
            foreach (DataSet.FepCfg.t_tagRow row in tagTable.Rows)
            {
                irow = sheet.CreateRow(line++);
                for (int i = 0; i < TagCfg_Colume.Length; i++)
                    irow.CreateCell(i);

                irow.Cells[00].SetCellType(CellType.String); //"变量名称"
                irow.Cells[00].SetCellValue(row.name); //"变量名称"
                irow.Cells[01].SetCellType(CellType.String);
                irow.Cells[01].SetCellValue(row.IsdescNull() ? "" : row.desc); //"变量描述"
                irow.Cells[02].SetCellType(CellType.Numeric);
                irow.Cells[02].SetCellValue(row.tagtype_id); //"变量类型"
                irow.Cells[03].SetCellType(CellType.Numeric);
                irow.Cells[03].SetCellValue(row.length); //"变量长度"
                irow.Cells[04].SetCellType(CellType.String);
                irow.Cells[04].SetCellValue(row.t_deviceRow.name); //"设备名称"
                irow.Cells[05].SetCellType(CellType.String);
                irow.Cells[05].SetCellValue(row.IsaddressNull() ? "" : row.address); //"设备地址"
                irow.Cells[06].SetCellType(CellType.Numeric);
                irow.Cells[06].SetCellValue(row.ctrl_enable); //"是否可控"
                irow.Cells[07].SetCellType(CellType.Numeric);
                irow.Cells[07].SetCellValue(row.evtctrl_enable); //"是否记录"
                irow.Cells[08].SetCellType(CellType.Numeric);
                irow.Cells[08].SetCellValue(row.evtctrl_priority); //"事件级别"
                irow.Cells[09].SetCellType(CellType.Numeric);
                irow.Cells[09].SetCellValue(row.scan_enable); //"是否扫描"
                irow.Cells[10].SetCellType(CellType.Numeric);
                irow.Cells[10].SetCellValue(row.scan_intv); //"扫描周期"
                irow.Cells[11].SetCellType(CellType.Numeric);
                irow.Cells[11].SetCellValue(row.scan_phs); //"扫描相位"
                irow.Cells[12].SetCellType(CellType.String);
                irow.Cells[12].SetCellValue(row.Isparam1Null() ? "" : row.param0); //"扩展属性0(param0)"
                irow.Cells[13].SetCellType(CellType.String);
                irow.Cells[13].SetCellValue(row.Isparam2Null() ? "" : row.param1); //"扩展属性1(param1)"
                irow.Cells[14].SetCellType(CellType.String);
                irow.Cells[14].SetCellValue(row.Isparam3Null() ? "" : row.param2); //"扩展属性2(param2)"
                irow.Cells[15].SetCellType(CellType.String);
                irow.Cells[15].SetCellValue(row.Isparam3Null() ? "" : row.param3); //"扩展属性3(param3)"
            }

            ((HSSFSheet)hssfworkbook.GetSheetAt(0)).AlternativeFormula = false;
            ((HSSFSheet)hssfworkbook.GetSheetAt(0)).AlternativeExpression = false;
            FileStream file = new FileStream(filename, FileMode.Create);
            hssfworkbook.Write(file);
            file.Close();
        }

        public static String TagCfgLoadFrom(String filename, DataSet.FepCfg fepCfg)
        {
            Dictionary<Int64, DataSet.FepCfg.t_tagtypeRow> typeDic = new Dictionary<Int64, DataSet.FepCfg.t_tagtypeRow>();
            Dictionary<String, DataSet.FepCfg.t_deviceRow> devDic = new Dictionary<String, DataSet.FepCfg.t_deviceRow>();

            foreach (DataSet.FepCfg.t_tagtypeRow row in fepCfg.t_tagtype)
                typeDic[row.id] = row;

            foreach (DataSet.FepCfg.t_deviceRow row in fepCfg.t_device)
                devDic[row.name] = row;

            FileStream fileStream = new FileStream(filename, FileMode.Open);
            IWorkbook workbook = new HSSFWorkbook(fileStream);
            fileStream.Close();

            ISheet sheet = workbook.GetSheet(TagCfg_SheetName);

            if (sheet.GetRow(0).Cells[1].StringCellValue != Cfg_Version[1])
                throw new Exception(String.Format("表格[{0}]的版本[{1}]与本程序支持的[{2}]不匹配！", sheet.SheetName, sheet.GetRow(0).Cells[1].StringCellValue, Cfg_Version[1]));
            if (sheet.GetRow(2).PhysicalNumberOfCells != TagCfg_Colume.Length)
                throw new Exception(String.Format("表格[{0}]的数据列数为[{1}]，与本程序支持不匹配，请先确认导入文件版本！", sheet.SheetName, sheet.GetRow(2).PhysicalNumberOfCells));

            fepCfg.t_tag.Clear();

            String errList = "";
            for (Int32 line = 3; line < sheet.PhysicalNumberOfRows; line++)
            {
                IRow irow = sheet.GetRow(line);
                String name = GetCellString(irow, 0); //"变量名称"
                String desc = GetCellString(irow, 1); //"变量描述"
                Int64 type = GetCellLong(irow, 2); //"变量类型"
                Int64 length = GetCellLong(irow, 3); //"变量长度"
                String devName = GetCellString(irow, 4); //"设备名称"                
                String address = GetCellString(irow, 5); //"设备地址"
                Int16 ctrl_enable = Convert.ToInt16(GetCellLong(irow, 6) != 0 ? 1 : 0); //"是否可控"
                Int16 evtctrl_eanble = Convert.ToInt16(GetCellLong(irow, 7) != 0 ? 1 : 0); //"是否记录"
                Int64 evtctrl_priority = GetCellLong(irow, 8); //"事件级别"
                Int16 scan_enable = Convert.ToInt16(GetCellLong(irow, 9) != 0 ? 1 : 0); //"是否扫描"
                Int64 scan_intv = GetCellLong(irow, 10); //"扫描周期"
                Int64 scan_phs = GetCellLong(irow, 11); //"扫描相位"
                String param0 = GetCellString(irow, 12); //"扩展属性0"
                String param1 = GetCellString(irow, 13); //"扩展属性1"
                String param2 = GetCellString(irow, 14); //"扩展属性2"
                String param3 = GetCellString(irow, 15); //"扩展属性3"

                if (!typeDic.ContainsKey(type))
                {
                    errList += String.Format("行{0}变量【{2}】中所给出类型【{1}】系统并不包含；\r\n", line, type, name);
                    continue;
                }
                else
                {
                    if (typeDic[type].length > 0) // 非TEXT BLOB
                    {
                        length = typeDic[type].length;
                    }
                    else if (!HelperRegex.IsRange(length, 0, 255))
                    {
                        errList += String.Format("行{0}变量【{2}】中所给出长度【{1}】超过该类型【{3}】的系统限制长度；\r\n", line, length, name, typeDic[type].name);
                        continue;
                    }
                }

                if (!devDic.ContainsKey(devName))
                {
                    errList += String.Format("行{0}变量【{2}】中所给出设备【{1}】系统尚未配置；\r\n", line, devName, name);
                    continue;
                }

                if (!HelperRegex.IsRange(evtctrl_priority, 0, 255))
                {
                    errList += String.Format("行{0}变量【{2}】中所给出事件级别【{1}】不在系统设定范围[0-255]内；\r\n", line, evtctrl_priority, name);
                    continue;
                }

                if (fepCfg.t_tag.Rows.Count < HelperConst.MAX_TAG_COUNT)
                {
                    //fepCfg.t_tag.Addt_tagRow(name, devRow, address, length, scan_enable, scan_intv, scan_phs, ctrl_enable,
                    //  evtctrl_eanble, evtctrl_priority, desc, param0, param1, param2, param3, typeRow);
                    fepCfg.t_tag.Addt_tagRow(name, devDic[devName], address, length, scan_enable, scan_intv, scan_phs,
                        ctrl_enable, evtctrl_eanble, evtctrl_priority, desc, param0, param1, param2, param3, typeDic[type]);
                }
                if (fepCfg.t_tag.Rows.Count == HelperConst.MAX_TAG_COUNT)
                {
                    errList += String.Format("导入系统变量个数超过限制【{0}】，余下不在导入。", HelperConst.MAX_TAG_COUNT);
                }
            }

            return errList;
        }
    }
}
