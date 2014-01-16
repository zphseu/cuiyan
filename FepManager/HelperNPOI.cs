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
        private static String[] DriverCfg_deviceColume = new String[] {"驱动名称", "设备名称(name)", "连接类型(conntype)", "连接参数(connparam)", 
            "响应超时[毫秒](recvtimeout)", "描述(desc)", "任务号(task)", "可选参数1(param1)", "可选参数2(param2)", "可选参数3(param3)"};
        private static String[] DriverCfg_datablockeColume = new String[] { "驱动名称", "所属设备(device)", "名称(name)", "类型(type)", "地址(address)", "元素个数(elemcount)", 
            "元素大小[字节](elembytes)", "轮询周期[毫秒](cyclerate)", "相位(phase)", "任务号(task)", "描述(desc)", "可选参数1(param1)", "可选参数2(param2)", "可选参数3(param3)" };
        private static String[] DriverCfg_SheetName = new String[] { "设备配置", "数据块配置" };
        private static String[] DriverCfg_Version = new String[] { "版本号", "F.1.0.0" };

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
            irow.CreateCell(0).SetCellValue(DriverCfg_Version[0]);
            irow.CreateCell(1).SetCellValue(DriverCfg_Version[1]);
            // Line 2: Empty
            sheet.CreateRow(line++);
            //Line 3: 驱动名称	设备名称(name)	连接类型(conntype)	连接参数(connparam)	响应超时[毫秒](recvtimeout)	描述(desc)	任务号(task)	可选参数1(param1)	可选参数2(param2)	可选参数3(param3)
            irow = sheet.CreateRow(line++);
            for (int j = 0; j < DriverCfg_deviceColume.Length; j++)
                irow.CreateCell(j).SetCellValue(DriverCfg_deviceColume[j]);
            // Line 4-: modbus	modbus_Device0	TCPClient	ip=iCV55-TEST-CY;port=502;multiLink=1;	1000		1	1            
            foreach (DataSet.FepCfg.t_deviceRow row in fepCfg.t_device.Rows)
            {
                irow = sheet.CreateRow(line++);
                for(int i = 0; i < DriverCfg_deviceColume.Length; i++)
                    irow.CreateCell(i);

                irow.Cells[0].SetCellValue(row.t_driverRow.name); //"驱动名称"
                irow.Cells[1].SetCellValue(row.name); //"设备名称(name)"
                irow.Cells[2].SetCellValue(row.conntype); //"连接类型(conntype)"
                irow.Cells[3].SetCellValue(row.connparam); //"连接参数(connparam)"
                irow.Cells[4].SetCellValue(row.recvtimeout); //"响应超时[毫秒](recvtimeout)"
                irow.Cells[5].SetCellValue(row.IsdescNull() ? "" : row.desc); //"描述(desc)"
                irow.Cells[6].SetCellValue(row.task); //"任务号(task)"
                irow.Cells[7].SetCellValue(row.Isparam1Null() ? "" : row.param1); //"可选参数1(param1)"
                irow.Cells[8].SetCellValue(row.Isparam2Null() ? "" : row.param2); //"可选参数2(param2)"
                irow.Cells[9].SetCellValue(row.Isparam3Null() ? "" : row.param3); //"可选参数3(param3)"
            }

            line = 0;
            sheet = hssfworkbook.CreateSheet(DriverCfg_SheetName[1]);
            // Line 1: 版本号	1.1.0
            irow = sheet.CreateRow(line++);
            irow.CreateCell(0).SetCellValue(DriverCfg_Version[0]);
            irow.CreateCell(1).SetCellValue(DriverCfg_Version[1]);
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
                for (int i = 0; i < DriverCfg_datablockeColume.Length; i++)
                    irow.CreateCell(i);
                irow.Cells[0].SetCellValue(row.t_deviceRow.t_driverRow.name); //"驱动名称"
                irow.Cells[1].SetCellValue(row.t_deviceRow.name); //"所属设备(device)"
                irow.Cells[2].SetCellValue(row.name); //"名称(name)"
                irow.Cells[3].SetCellValue(row.type); //"类型(type)"
                irow.Cells[4].SetCellValue(row.address); //"地址(address)"
                irow.Cells[5].SetCellValue(row.elemcount); //"元素个数(elemcount)"
                irow.Cells[6].SetCellValue(row.elembytes); //"元素大小[字节](elembytes)"
                irow.Cells[7].SetCellValue(row.cyclerate); //"轮询周期[毫秒](cyclerate)"
                irow.Cells[8].SetCellValue(row.phase); //"相位(phase)"
                irow.Cells[9].SetCellValue(row.task); //"任务号(task)"
                irow.Cells[10].SetCellValue(row.IsdescNull() ? "" : row.desc); //"描述(desc)"
                irow.Cells[11].SetCellValue(row.Isparam1Null() ? "" : row.param1); //"可选参数1(param1)"
                irow.Cells[12].SetCellValue(row.Isparam2Null() ? "" : row.param2); //"可选参数2(param2)"
                irow.Cells[13].SetCellValue(row.Isparam3Null() ? "" : row.param3); //"可选参数3(param3)"
            }

            ((HSSFSheet)hssfworkbook.GetSheetAt(0)).AlternativeFormula = false;
            ((HSSFSheet)hssfworkbook.GetSheetAt(0)).AlternativeExpression = false;

            //Write the stream data of workbook to the root directory
            FileStream file = new FileStream(filename, FileMode.Create);
            hssfworkbook.Write(file);
            file.Close();
        }

        public static void DriverCfgLoadFrom(String filename, DataSet.FepCfg fepCfg)
        {
            DataSet.FepCfg.t_driverRow drvRow;
            if (fepCfg.t_driver.Count == 1)
                drvRow = fepCfg.t_driver.Rows[0] as DataSet.FepCfg.t_driverRow;
            else
                throw new Exception("无法找到驱动信息！");

            // http://tonyqus.sinaapp.com/archives/270
            FileStream fileStream = new FileStream(filename, FileMode.Open);
            IWorkbook workbook = new HSSFWorkbook(fileStream);
            fileStream.Close();

            ISheet sheet1 = workbook.GetSheet(DriverCfg_SheetName[0]);
            ISheet sheet2 = workbook.GetSheet(DriverCfg_SheetName[1]);

            if (sheet1.GetRow(0).Cells[1].StringCellValue != DriverCfg_Version[1])
                throw new Exception(String.Format("表格[{0}]的版本[{1}]与本程序支持的[{2}]不匹配！", sheet1.SheetName, sheet1.GetRow(0).Cells[1].StringCellValue, DriverCfg_Version[1]));
            if (sheet2.GetRow(0).Cells[1].StringCellValue != DriverCfg_Version[1])
                throw new Exception(String.Format("表格[{0}]的版本[{1}]与本程序支持的[{2}]不匹配！", sheet2.SheetName, sheet2.GetRow(0).Cells[1].StringCellValue, DriverCfg_Version[1]));

            if (sheet1.GetRow(2).PhysicalNumberOfCells != DriverCfg_deviceColume.Length)
                throw new Exception(String.Format("表格[{0}]的数据列数为[{1}]，与本程序支持不匹配，请先确认导入文件版本！", sheet1.SheetName, sheet1.GetRow(2).PhysicalNumberOfCells));
            if (sheet2.GetRow(2).PhysicalNumberOfCells != DriverCfg_datablockeColume.Length)
                throw new Exception(String.Format("表格[{0}]的数据列数为[{1}]，与本程序支持不匹配，请先确认导入文件版本！", sheet2.SheetName, sheet2.GetRow(2).PhysicalNumberOfCells));

            fepCfg.t_device.Clear();
            fepCfg.t_datablock.Clear();

            Dictionary<String, DataSet.FepCfg.t_deviceRow> devNameRow = new Dictionary<string,DataSet.FepCfg.t_deviceRow>();
            for (Int32 line = 3; line < sheet1.PhysicalNumberOfRows; line++)
            {
                IRow irow = sheet1.GetRow(line);
                //Addt_deviceRow(_driver, name1, connparam3, conntype2, cyclerate7, recvtimeout4, task6, desc5, param1 7, param2 8, param3 9)
                fepCfg.t_device.Addt_deviceRow(drvRow, irow.Cells[1].StringCellValue, irow.Cells[3].StringCellValue, irow.Cells[2].StringCellValue,
                    1000, Convert.ToInt64(irow.Cells[4].NumericCellValue),Convert.ToInt64(irow.Cells[6].NumericCellValue),
                    irow.Cells[5].StringCellValue,irow.Cells[7].StringCellValue,irow.Cells[8].StringCellValue, irow.Cells[9].StringCellValue);
                
                devNameRow[irow.Cells[1].StringCellValue] = fepCfg.t_device.Rows[fepCfg.t_device.Rows.Count - 1] as DataSet.FepCfg.t_deviceRow;
            }

            for (Int32 line = 3; line < sheet2.PhysicalNumberOfRows; line++)
            {
                IRow irow = sheet2.GetRow(line);
                //Addt_datablockRow(device, name2, type3, address4, cyclerate7, elembytes6, elemcount5, phase8, task9, desc10, param1 11, param2 12, param3 13)
                fepCfg.t_datablock.Addt_datablockRow(devNameRow[irow.Cells[1].StringCellValue], irow.Cells[2].StringCellValue,
                    irow.Cells[3].StringCellValue, irow.Cells[4].StringCellValue, Convert.ToInt64(irow.Cells[7].NumericCellValue),
                    Convert.ToInt64(irow.Cells[6].NumericCellValue), Convert.ToInt64(irow.Cells[5].NumericCellValue), Convert.ToInt64(irow.Cells[8].NumericCellValue),
                    Convert.ToInt64(irow.Cells[9].NumericCellValue), irow.Cells[10].StringCellValue, 
                    irow.Cells[11].StringCellValue, irow.Cells[12].StringCellValue, irow.Cells[13].StringCellValue);
            }
        }
    }
}
