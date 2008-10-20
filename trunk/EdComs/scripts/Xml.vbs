'========================================================
' This is a VBScript file for Windows Scripting Host.

set grid = WScript.CreateObject( "Msxml.DOMDocument" )
if grid.load("http://localhost/template.html") then
	msgbox  grid.childNodes.length
end if

set grid = Nothing