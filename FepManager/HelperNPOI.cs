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
        private static readonly String[] DriverCfg_deviceColume = new String[] {"��������", "�豸����(name)", "��������(conntype)", "���Ӳ���(connparam)", "��ѯ����[����](cyclerate)",
            "��Ӧ��ʱ[����](recvtimeout)", "����(desc)", "�����(task)", "��ѡ����1(param1)", "��ѡ����2(param2)", "��ѡ����3(param3)"};
        private static readonly String[] DriverCfg_datablockeColume = new String[] { "��������", "�����豸(device)", "����(name)", "����(type)", "��ַ(address)", "Ԫ�ظ���(elemcount)", 
            "Ԫ�ش�С[�ֽ�](elembytes)", "��ѯ����[����](cyclerate)", "��λ(phase)", "�����(task)", "����(desc)", "��ѡ����1(param1)", "��ѡ����2(param2)", "��ѡ����3(param3)" };
        private static readonly String[] DriverCfg_SheetName = new String[] { "�豸����", "���ݿ�����" };
        private static readonly String[] Cfg_Version = new String[] { "�汾��", "F.1.0.0" };

        private static readonly String TagCfg_SheetName = "��������";
        private static readonly String[] TagCfg_Colume = new String[] {"��������", "��������", "��������", "��������", 
            "�豸����", "�豸��ַ", "�Ƿ�ɿ�", "�Ƿ��¼", "�¼�����", "�Ƿ�ɨ��", "ɨ������", "ɨ����λ", "��չ����0", "��չ����1", "��չ����2", "��չ����3"};
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
            dsi.Company = @"�Ϻ���������ɷ����޹�˾";
            hssfworkbook.DocumentSummaryInformation = dsi;

            ////create a entry of SummaryInformation
            SummaryInformation si = PropertySetFactory.CreateSummaryInformation();
            si.Subject = @"BSFep�������õ��������ļ�";
            hssfworkbook.SummaryInformation = si;

            //here, we must insert at least one sheet to the workbook. otherwise, Excel will say 'data lost in file'
            //So we insert three sheet just like what Excel does
            Int32 line = 0;
            ISheet sheet = hssfworkbook.CreateSheet(DriverCfg_SheetName[0]);
            // Line 1: �汾��	1.1.0
            IRow irow = sheet.CreateRow(line++);
            irow.CreateCell(0).SetCellValue(Cfg_Version[0]);
            irow.CreateCell(1).SetCellValue(Cfg_Version[1]);
            // Line 2: Empty
            sheet.CreateRow(line++);
            //Line 3: ��������	�豸����(name)	��������(conntype)	���Ӳ���(connparam)	��ѯ����[����](cyclerate) ��Ӧ��ʱ[����](recvtimeout)	����(desc)	�����(task)	��ѡ����1(param1)	��ѡ����2(param2)	��ѡ����3(param3)
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
                irow.Cells[0].SetCellValue(row.t_driverRow.name); //"��������"
                irow.Cells[1].SetCellType(CellType.String);
                irow.Cells[1].SetCellValue(row.name); //"�豸����(name)"
                irow.Cells[2].SetCellType(CellType.String);
                irow.Cells[2].SetCellValue(row.conntype); //"��������(conntype)"
                irow.Cells[3].SetCellType(CellType.String);
                irow.Cells[3].SetCellValue(row.connparam); //"���Ӳ���(connparam)"
                irow.Cells[4].SetCellType(CellType.String);
                irow.Cells[4].SetCellValue(row.cyclerate); //"��ѯ����(cyclerate)"
                irow.Cells[5].SetCellType(CellType.Numeric);
                irow.Cells[5].SetCellValue(row.recvtimeout); //"��Ӧ��ʱ[����](recvtimeout)"
                irow.Cells[6].SetCellType(CellType.String);
                irow.Cells[6].SetCellValue(row.IsdescNull() ? "" : row.desc); //"����(desc)"
                irow.Cells[7].SetCellType(CellType.Numeric);
                irow.Cells[7].SetCellValue(row.task); //"�����(task)"
                irow.Cells[8].SetCellType(CellType.String);
                irow.Cells[8].SetCellValue(row.Isparam1Null() ? "" : row.param1); //"��ѡ����1(param1)"
                irow.Cells[9].SetCellType(CellType.String);
                irow.Cells[9].SetCellValue(row.Isparam2Null() ? "" : row.param2); //"��ѡ����2(param2)"
                irow.Cells[10].SetCellType(CellType.String);
                irow.Cells[10].SetCellValue(row.Isparam3Null() ? "" : row.param3); //"��ѡ����3(param3)"
            }

            line = 0;
            sheet = hssfworkbook.CreateSheet(DriverCfg_SheetName[1]);
            // Line 1: �汾��	1.1.0
            irow = sheet.CreateRow(line++);
            irow.CreateCell(0).SetCellValue(Cfg_Version[0]);
            irow.CreateCell(1).SetCellValue(Cfg_Version[1]);
            // Line 2: Empty
            sheet.CreateRow(line++);
            //Line 3: ��������	�豸����(name)	��������(conntype)	���Ӳ���(connparam)	��Ӧ��ʱ[����](recvtimeout)	����(desc)	�����(task)	��ѡ����1(param1)	��ѡ����2(param2)	��ѡ����3(param3)
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
                irow.Cells[00].SetCellValue(row.t_deviceRow.t_driverRow.name); //"��������"
                irow.Cells[01].SetCellType(CellType.String);
                irow.Cells[01].SetCellValue(row.t_deviceRow.name); //"�����豸(device)"
                irow.Cells[02].SetCellType(CellType.String);
                irow.Cells[02].SetCellValue(row.name); //"����(name)"
                irow.Cells[03].SetCellType(CellType.String);
                irow.Cells[03].SetCellValue(row.type); //"����(type)"
                irow.Cells[04].SetCellType(CellType.String);
                irow.Cells[04].SetCellValue(row.address); //"��ַ(address)"
                irow.Cells[05].SetCellType(CellType.Numeric);
                irow.Cells[05].SetCellValue(row.elemcount); //"Ԫ�ظ���(elemcount)"
                irow.Cells[06].SetCellType(CellType.Numeric);
                irow.Cells[06].SetCellValue(row.elembytes); //"Ԫ�ش�С[�ֽ�](elembytes)"
                irow.Cells[07].SetCellType(CellType.Numeric);
                irow.Cells[07].SetCellValue(row.cyclerate); //"��ѯ����[����](cyclerate)"
                irow.Cells[08].SetCellType(CellType.Numeric);
                irow.Cells[08].SetCellValue(row.phase); //"��λ(phase)"
                irow.Cells[09].SetCellType(CellType.Numeric);
                irow.Cells[09].SetCellValue(row.task); //"�����(task)"
                irow.Cells[10].SetCellType(CellType.String);
                irow.Cells[10].SetCellValue(row.IsdescNull() ? "" : row.desc); //"����(desc)"
                irow.Cells[11].SetCellType(CellType.String);
                irow.Cells[11].SetCellValue(row.Isparam1Null() ? "" : row.param1); //"��ѡ����1(param1)"
                irow.Cells[12].SetCellType(CellType.String);
                irow.Cells[12].SetCellValue(row.Isparam2Null() ? "" : row.param2); //"��ѡ����2(param2)"
                irow.Cells[13].SetCellType(CellType.String);
                irow.Cells[13].SetCellValue(row.Isparam3Null() ? "" : row.param3); //"��ѡ����3(param3)"
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
                throw new Exception(String.Format("���[{0}]�İ汾[{1}]�뱾����֧�ֵ�[{2}]��ƥ�䣡", sheet1.SheetName, sheet1.GetRow(0).Cells[1].StringCellValue, Cfg_Version[1]));
            if (sheet2.GetRow(0).Cells[1].StringCellValue != Cfg_Version[1])
                throw new Exception(String.Format("���[{0}]�İ汾[{1}]�뱾����֧�ֵ�[{2}]��ƥ�䣡", sheet2.SheetName, sheet2.GetRow(0).Cells[1].StringCellValue, Cfg_Version[1]));

            if (sheet1.GetRow(2).PhysicalNumberOfCells != DriverCfg_deviceColume.Length)
                throw new Exception(String.Format("���[{0}]����������Ϊ[{1}]���뱾����֧�ֲ�ƥ�䣬����ȷ�ϵ����ļ��汾��", sheet1.SheetName, sheet1.GetRow(2).PhysicalNumberOfCells));
            if (sheet2.GetRow(2).PhysicalNumberOfCells != DriverCfg_datablockeColume.Length)
                throw new Exception(String.Format("���[{0}]����������Ϊ[{1}]���뱾����֧�ֲ�ƥ�䣬����ȷ�ϵ����ļ��汾��", sheet2.SheetName, sheet2.GetRow(2).PhysicalNumberOfCells));

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
                        errList += String.Format("�����豸�����������ơ�{0}�������²��ڵ��롣", HelperConst.MAX_DEV_COUNT);
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
            dsi.Company = @"�Ϻ���������ɷ����޹�˾";
            hssfworkbook.DocumentSummaryInformation = dsi;
            SummaryInformation si = PropertySetFactory.CreateSummaryInformation();
            si.Subject = @"BSFep�������õ��������ļ�";
            hssfworkbook.SummaryInformation = si;

            Int32 line = 0;
            ISheet sheet = hssfworkbook.CreateSheet(TagCfg_SheetName);

            // Line 1: �汾��	1.1.0
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

                irow.Cells[00].SetCellType(CellType.String); //"��������"
                irow.Cells[00].SetCellValue(row.name); //"��������"
                irow.Cells[01].SetCellType(CellType.String);
                irow.Cells[01].SetCellValue(row.IsdescNull() ? "" : row.desc); //"��������"
                irow.Cells[02].SetCellType(CellType.Numeric);
                irow.Cells[02].SetCellValue(row.tagtype_id); //"��������"
                irow.Cells[03].SetCellType(CellType.Numeric);
                irow.Cells[03].SetCellValue(row.length); //"��������"
                irow.Cells[04].SetCellType(CellType.String);
                irow.Cells[04].SetCellValue(row.t_deviceRow.name); //"�豸����"
                irow.Cells[05].SetCellType(CellType.String);
                irow.Cells[05].SetCellValue(row.IsaddressNull() ? "" : row.address); //"�豸��ַ"
                irow.Cells[06].SetCellType(CellType.Numeric);
                irow.Cells[06].SetCellValue(row.ctrl_enable); //"�Ƿ�ɿ�"
                irow.Cells[07].SetCellType(CellType.Numeric);
                irow.Cells[07].SetCellValue(row.evtctrl_enable); //"�Ƿ��¼"
                irow.Cells[08].SetCellType(CellType.Numeric);
                irow.Cells[08].SetCellValue(row.evtctrl_priority); //"�¼�����"
                irow.Cells[09].SetCellType(CellType.Numeric);
                irow.Cells[09].SetCellValue(row.scan_enable); //"�Ƿ�ɨ��"
                irow.Cells[10].SetCellType(CellType.Numeric);
                irow.Cells[10].SetCellValue(row.scan_intv); //"ɨ������"
                irow.Cells[11].SetCellType(CellType.Numeric);
                irow.Cells[11].SetCellValue(row.scan_phs); //"ɨ����λ"
                irow.Cells[12].SetCellType(CellType.String);
                irow.Cells[12].SetCellValue(row.Isparam1Null() ? "" : row.param0); //"��չ����0(param0)"
                irow.Cells[13].SetCellType(CellType.String);
                irow.Cells[13].SetCellValue(row.Isparam2Null() ? "" : row.param1); //"��չ����1(param1)"
                irow.Cells[14].SetCellType(CellType.String);
                irow.Cells[14].SetCellValue(row.Isparam3Null() ? "" : row.param2); //"��չ����2(param2)"
                irow.Cells[15].SetCellType(CellType.String);
                irow.Cells[15].SetCellValue(row.Isparam3Null() ? "" : row.param3); //"��չ����3(param3)"
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
                throw new Exception(String.Format("���[{0}]�İ汾[{1}]�뱾����֧�ֵ�[{2}]��ƥ�䣡", sheet.SheetName, sheet.GetRow(0).Cells[1].StringCellValue, Cfg_Version[1]));
            if (sheet.GetRow(2).PhysicalNumberOfCells != TagCfg_Colume.Length)
                throw new Exception(String.Format("���[{0}]����������Ϊ[{1}]���뱾����֧�ֲ�ƥ�䣬����ȷ�ϵ����ļ��汾��", sheet.SheetName, sheet.GetRow(2).PhysicalNumberOfCells));

            fepCfg.t_tag.Clear();

            String errList = "";
            for (Int32 line = 3; line < sheet.PhysicalNumberOfRows; line++)
            {
                IRow irow = sheet.GetRow(line);
                String name = GetCellString(irow, 0); //"��������"
                String desc = GetCellString(irow, 1); //"��������"
                Int64 type = GetCellLong(irow, 2); //"��������"
                Int64 length = GetCellLong(irow, 3); //"��������"
                String devName = GetCellString(irow, 4); //"�豸����"                
                String address = GetCellString(irow, 5); //"�豸��ַ"
                Int16 ctrl_enable = Convert.ToInt16(GetCellLong(irow, 6) != 0 ? 1 : 0); //"�Ƿ�ɿ�"
                Int16 evtctrl_eanble = Convert.ToInt16(GetCellLong(irow, 7) != 0 ? 1 : 0); //"�Ƿ��¼"
                Int64 evtctrl_priority = GetCellLong(irow, 8); //"�¼�����"
                Int16 scan_enable = Convert.ToInt16(GetCellLong(irow, 9) != 0 ? 1 : 0); //"�Ƿ�ɨ��"
                Int64 scan_intv = GetCellLong(irow, 10); //"ɨ������"
                Int64 scan_phs = GetCellLong(irow, 11); //"ɨ����λ"
                String param0 = GetCellString(irow, 12); //"��չ����0"
                String param1 = GetCellString(irow, 13); //"��չ����1"
                String param2 = GetCellString(irow, 14); //"��չ����2"
                String param3 = GetCellString(irow, 15); //"��չ����3"

                if (!typeDic.ContainsKey(type))
                {
                    errList += String.Format("��{0}������{2}�������������͡�{1}��ϵͳ����������\r\n", line, type, name);
                    continue;
                }
                else
                {
                    if (typeDic[type].length > 0) // ��TEXT BLOB
                    {
                        length = typeDic[type].length;
                    }
                    else if (!HelperRegex.IsRange(length, 0, 255))
                    {
                        errList += String.Format("��{0}������{2}�������������ȡ�{1}�����������͡�{3}����ϵͳ���Ƴ��ȣ�\r\n", line, length, name, typeDic[type].name);
                        continue;
                    }
                }

                if (!devDic.ContainsKey(devName))
                {
                    errList += String.Format("��{0}������{2}�����������豸��{1}��ϵͳ��δ���ã�\r\n", line, devName, name);
                    continue;
                }

                if (!HelperRegex.IsRange(evtctrl_priority, 0, 255))
                {
                    errList += String.Format("��{0}������{2}�����������¼�����{1}������ϵͳ�趨��Χ[0-255]�ڣ�\r\n", line, evtctrl_priority, name);
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
                    errList += String.Format("����ϵͳ���������������ơ�{0}�������²��ڵ��롣", HelperConst.MAX_TAG_COUNT);
                }
            }

            return errList;
        }
    }
}
