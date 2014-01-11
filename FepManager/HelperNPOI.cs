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
        private static String[] DataSetDrvCfgDef_deviceColume = new String[] {"��������", "�豸����(name)", "��������(conntype)", "���Ӳ���(connparam)", 
            "��Ӧ��ʱ[����](recvtimeout)", "����(desc)", "�����(task)", "��ѡ����1(param1)", "��ѡ����2(param2)", "��ѡ����3(param3)"};
        private static String[] DataSetDrvCfgDef_datablockeColume = new String[] { "��������", "�����豸(device)", "����(name)", "����(type)", "��ַ(address)", "Ԫ�ظ���(elemcount)", 
            "Ԫ�ش�С[�ֽ�](elembytes)", "��ѯ����[����](cyclerate)", "��λ(phase)", "�����(task)", "����(desc)", "��ѡ����1(param1)", "��ѡ����2(param2)", "��ѡ����3(param3)" };
        private static String[] DataSetDrvCfgDef_SheetName = new String[] { "�豸����", "���ݿ�����" };
        private static String[] DataSetDrvCfgDef_Version = new String[] { "�汾��", "F.1.0.0" };

        public static void DataSetDrvCfgDef_save(String filename, DataSetXml.DriverXml data)
        {
            if (data.Tables["driver"].Rows.Count <= 0)
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
            ISheet sheet = hssfworkbook.CreateSheet(DataSetDrvCfgDef_SheetName[0]);           
            // Line 1: �汾��	1.1.0
            IRow irow = sheet.CreateRow(line++);
            irow.CreateCell(0).SetCellValue(DataSetDrvCfgDef_Version[0]);
            irow.CreateCell(1).SetCellValue(DataSetDrvCfgDef_Version[1]);
            // Line 2: Empty
            sheet.CreateRow(line++);
            //Line 3: ��������	�豸����(name)	��������(conntype)	���Ӳ���(connparam)	��Ӧ��ʱ[����](recvtimeout)	����(desc)	�����(task)	��ѡ����1(param1)	��ѡ����2(param2)	��ѡ����3(param3)
            irow = sheet.CreateRow(line++);
            for (int j = 0; j < DataSetDrvCfgDef_deviceColume.Length; j++)
                irow.CreateCell(j).SetCellValue(DataSetDrvCfgDef_deviceColume[j]);
            // Line 4-: modbus	modbus_Device0	TCPClient	ip=iCV55-TEST-CY;port=502;multiLink=1;	1000		1	1            
            foreach (DataSetXml.DriverXml.deviceRow row in data.Tables["device"].Rows)
            {
                irow = sheet.CreateRow(line++);
                for(int i = 0; i < DataSetDrvCfgDef_deviceColume.Length; i++)
                    irow.CreateCell(i);

                irow.Cells[0].SetCellValue(row.driverRow.name); //"��������"
                if (!row.IsnameNull()) irow.Cells[1].SetCellValue(row.name); //"�豸����(name)"
                if (!row.IsconntypeNull()) irow.Cells[2].SetCellValue(row.conntype); //"��������(conntype)"
                if (!row.IsconnparamNull()) irow.Cells[3].SetCellValue(row.connparam); //"���Ӳ���(connparam)"
                if (!row.IsrecvtimeoutNull()) irow.Cells[4].SetCellValue(row.recvtimeout); //"��Ӧ��ʱ[����](recvtimeout)"
                if (!row.IsdescNull()) irow.Cells[5].SetCellValue(row.desc); //"����(desc)"
                if (!row.IstaskNull()) irow.Cells[6].SetCellValue(row.task); //"�����(task)"
                if (!row.Isparam1Null()) irow.Cells[7].SetCellValue(row.param1); //"��ѡ����1(param1)"
                if (!row.Isparam2Null()) irow.Cells[8].SetCellValue(row.param2); //"��ѡ����2(param2)"
                if (!row.Isparam3Null()) irow.Cells[9].SetCellValue(row.param3); //"��ѡ����3(param3)"
            }

            line = 0;
            sheet = hssfworkbook.CreateSheet(DataSetDrvCfgDef_SheetName[1]);
            // Line 1: �汾��	1.1.0
            irow = sheet.CreateRow(line++);
            irow.CreateCell(0).SetCellValue(DataSetDrvCfgDef_Version[0]);
            irow.CreateCell(1).SetCellValue(DataSetDrvCfgDef_Version[1]);
            // Line 2: Empty
            sheet.CreateRow(line++);
            //Line 3: ��������	�豸����(name)	��������(conntype)	���Ӳ���(connparam)	��Ӧ��ʱ[����](recvtimeout)	����(desc)	�����(task)	��ѡ����1(param1)	��ѡ����2(param2)	��ѡ����3(param3)
            irow = sheet.CreateRow(line++);
            for (int j = 0; j < DataSetDrvCfgDef_datablockeColume.Length; j++)
                irow.CreateCell(j).SetCellValue(DataSetDrvCfgDef_datablockeColume[j]);
            // Line 4-: modbus	modbus_Device0	DB1	AO	400000	100	2	1000	0	1
            foreach (DataSetXml.DriverXml.datablockRow row in data.Tables["datablock"].Rows)
            {
                irow = sheet.CreateRow(line++);
                for (int i = 0; i < DataSetDrvCfgDef_datablockeColume.Length; i++)
                    irow.CreateCell(i);
                irow.Cells[0].SetCellValue(row.deviceRow.driverRow.name); //"��������"
                irow.Cells[1].SetCellValue(row.deviceRow.name); //"�����豸(device)"
                if (!row.IsnameNull()) irow.Cells[2].SetCellValue(row.name); //"����(name)"
                if (!row.IstypeNull()) irow.Cells[3].SetCellValue(row.type); //"����(type)"
                if (!row.IsaddressNull()) irow.Cells[4].SetCellValue(row.address); //"��ַ(address)"
                if (!row.IselemcountNull()) irow.Cells[5].SetCellValue(row.elemcount); //"Ԫ�ظ���(elemcount)"
                if (!row.IselembytesNull()) irow.Cells[6].SetCellValue(row.elembytes); //"Ԫ�ش�С[�ֽ�](elembytes)"
                if (!row.IscyclerateNull()) irow.Cells[7].SetCellValue(row.cyclerate); //"��ѯ����[����](cyclerate)"
                if (!row.IsphaseNull()) irow.Cells[8].SetCellValue(row.phase); //"��λ(phase)"
                if (!row.IstaskNull()) irow.Cells[9].SetCellValue(row.task); //"�����(task)"
                if (!row.IsdescNull()) irow.Cells[10].SetCellValue(row.desc); //"����(desc)"
                if (!row.Isparam1Null()) irow.Cells[11].SetCellValue(row.param1); //"��ѡ����1(param1)"
                if (!row.Isparam2Null()) irow.Cells[12].SetCellValue(row.param2); //"��ѡ����2(param2)"
                if (!row.Isparam3Null()) irow.Cells[13].SetCellValue(row.param3); //"��ѡ����3(param3)"
            }

            ((HSSFSheet)hssfworkbook.GetSheetAt(0)).AlternativeFormula = false;
            ((HSSFSheet)hssfworkbook.GetSheetAt(0)).AlternativeExpression = false;

            //Write the stream data of workbook to the root directory
            FileStream file = new FileStream(filename, FileMode.Create);
            hssfworkbook.Write(file);
            file.Close();
        }

        public static void DataSetDrvCfgDef_read(String filename, DataSetXml.DriverXml data)
        {
            // http://tonyqus.sinaapp.com/archives/270

            FileStream fileStream = new FileStream(filename, FileMode.Open);
            IWorkbook workbook = new HSSFWorkbook(fileStream);
            fileStream.Close();

            ISheet sheet1 = workbook.GetSheet(DataSetDrvCfgDef_SheetName[0]);
            ISheet sheet2 = workbook.GetSheet(DataSetDrvCfgDef_SheetName[1]);

            if (sheet1.GetRow(0).Cells[1].StringCellValue != DataSetDrvCfgDef_Version[1])
                throw new Exception(String.Format("���[{0}]�İ汾[{1}]�뱾����֧�ֵ�[{2}]��ƥ�䣡", sheet1.SheetName, sheet1.GetRow(0).Cells[1].StringCellValue, DataSetDrvCfgDef_Version[1]));
            if (sheet2.GetRow(0).Cells[1].StringCellValue != DataSetDrvCfgDef_Version[1])
                throw new Exception(String.Format("���[{0}]�İ汾[{1}]�뱾����֧�ֵ�[{2}]��ƥ�䣡", sheet2.SheetName, sheet2.GetRow(0).Cells[1].StringCellValue, DataSetDrvCfgDef_Version[1]));

            if (sheet1.GetRow(2).PhysicalNumberOfCells != DataSetDrvCfgDef_deviceColume.Length)
                throw new Exception(String.Format("���[{0}]����������Ϊ[{1}]���뱾����֧�ֲ�ƥ�䣬����ȷ�ϵ����ļ��汾��", sheet1.SheetName, sheet1.GetRow(2).PhysicalNumberOfCells));
            if (sheet2.GetRow(2).PhysicalNumberOfCells != DataSetDrvCfgDef_datablockeColume.Length)
                throw new Exception(String.Format("���[{0}]����������Ϊ[{1}]���뱾����֧�ֲ�ƥ�䣬����ȷ�ϵ����ļ��汾��", sheet2.SheetName, sheet2.GetRow(2).PhysicalNumberOfCells));

            while (data.Tables["datablock"].Rows.Count > 0)
                data.Tables["datablock"].Rows.RemoveAt(0);
            while(data.Tables["device"].Rows.Count > 0)
                data.Tables["device"].Rows.RemoveAt(0);

            Dictionary<String, Int32> deviceNameId = new Dictionary<string,int>();
            for (Int32 line = 3; line <= sheet1.PhysicalNumberOfRows; line++)
            {
                DataSetXml.DriverXml.deviceRow row = (DataSetXml.DriverXml.deviceRow)data.Tables["device"].NewRow();
                IRow irow = sheet1.GetRow(line);
                row.driver_Id = 0;
                row.device_Id = line - 3;
                row.name = irow.Cells[1].StringCellValue;
                row.conntype = irow.Cells[2].StringCellValue;//"��������(conntype)"
                row.connparam = irow.Cells[3].StringCellValue;//"���Ӳ���(connparam)"
                row.recvtimeout = irow.Cells[4].StringCellValue;//"��Ӧ��ʱ[����](recvtimeout)"
                row.desc = irow.Cells[5].StringCellValue;//"����(desc)"
                row.task = irow.Cells[6].StringCellValue;//"�����(task)"
                row.param1 = irow.Cells[7].StringCellValue;//"��ѡ����1(param1)"
                row.param2 = irow.Cells[8].StringCellValue;//"��ѡ����2(param2)"
                row.param3 = irow.Cells[9].StringCellValue;//"��ѡ����3(param3)"
                data.Tables["device"].Rows.Add(row);
                deviceNameId.Add(row.name, row.device_Id);
            }

            for (Int32 line = 3; line <= sheet2.PhysicalNumberOfRows; line++)
            {
                DataSetXml.DriverXml.datablockRow row = (DataSetXml.DriverXml.datablockRow)data.Tables["datablock"].NewRow();
                IRow irow = sheet2.GetRow(line);
                row.device_Id = deviceNameId[irow.Cells[1].StringCellValue];
                row.name = irow.Cells[2].StringCellValue; //"����(name)"
                row.type = irow.Cells[3].StringCellValue; //"����(type)"
                row.address = irow.Cells[4].StringCellValue; //"��ַ(address)"
                row.elemcount = irow.Cells[5].StringCellValue; //"Ԫ�ظ���(elemcount)"
                row.elembytes = irow.Cells[6].StringCellValue; //"Ԫ�ش�С[�ֽ�](elembytes)"
                row.cyclerate = irow.Cells[7].StringCellValue; //"��ѯ����[����](cyclerate)"
                row.phase = irow.Cells[8].StringCellValue; //"��λ(phase)"
                row.task = irow.Cells[9].StringCellValue; //"�����(task)"
                row.desc = irow.Cells[10].StringCellValue; //"����(desc)"
                row.param1 = irow.Cells[11].StringCellValue; //"��ѡ����1(param1)"
                row.param2 = irow.Cells[12].StringCellValue; //"��ѡ����2(param2)"
                row.param3 = irow.Cells[13].StringCellValue; //"��ѡ����3(param3)"
                data.Tables["datablock"].Rows.Add(row);
            }
        }
    }
}
