'========================================================
' This is a VBScript file for Windows Scripting Host.

set grid = WScript.CreateObject( "EdComs.EdMtrData.1" )
'grid.ReadDB "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\EdDoc\Demo1.mdb", "SELECT * FROM DemoTable"

'grid.ReadFile "http://localhost/template.html", ""
'grid.ReadFile "ftp://168.2.4.55/htdocs/template.html", ""
grid.ReadFile "E:\EdWork\myproj\EdComs\scripts\template.html", ""

grid.SetParams "", "", "", "", "Times New Roman", "100:100:100:150", 1
grid.DoPrint ""