'========================================================
' This is a VBScript file for Windows Scripting Host.

set grid = WScript.CreateObject( "EdComs.EdMtrNums.1" )

'Method 1
'grid.ReadFile "http://localhost/template.html", ""
'grid.ReadFile "ftp://168.2.4.55/htdocs/template.html", ""
grid.ReadFile "E:\EdWork\myproj\EdComs\scripts\template.html", ""

'Method 2
'grid.SetSize 3, 1
'grid.ColName(0) = "Col"
'grid.RowName(0) = "Row0"
'grid.RowName(1) = "Row1"
'grid.RowName(2) = "Row2"
'grid.Data(0, 0) = 10
'grid.Data(1, 0) = 11
'grid.Data(2, 0) = 12

'Method 3
'grid.SetColNames "Col"
'grid.SetRowNames "Row0;Row1;Row2"
'grid.Data(0, 0) = 20
'grid.Data(1, 0) = 21
'grid.Data(2, 0) = 22

grid.Save "E:\EdWork\myproj\EdComs\scripts\Result.txt"
set grid = Nothing