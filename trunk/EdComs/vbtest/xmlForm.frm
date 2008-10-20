VERSION 5.00
Object = "{48E59290-9880-11CF-9754-00AA00C00908}#1.0#0"; "MSINET.OCX"
Begin VB.Form Form1 
   BackColor       =   &H80000005&
   Caption         =   "Form1"
   ClientHeight    =   3135
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3135
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin InetCtlsObjects.Inet Inet1 
      Left            =   3600
      Top             =   2040
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   3135
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4695
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    Dim xDoc As New MSXML.DOMDocument
    Dim xNodeList As MSXML.IXMLDOMNodeList
    Dim strURL As String
    
    strURL = "http://localhost/template.html"
    strURL = Inet1.OpenURL(strURL, icString)
    
    If xDoc.loadXML(strURL) Then
        Set xNodeList = xDoc.childNodes
        Label1.Caption = xNodeList.length
    Else
        Dim xPE As MSXML.IXMLDOMParseError
        Set xPE = xDoc.parseError
        With xPE
            Label1.Caption = "你的XML Document 不能调入原因是." & vbCrLf & _
                "错误 #: " & .errorCode & ": " & .reason & _
                "Line #: " & .Line & vbCrLf & _
                "Line Position: " & .linepos & vbCrLf & _
                "Position In File: " & .filepos & vbCrLf & _
                "Source Text: " & .srcText & vbCrLf & _
                "Document URL: " & .url
        End With
        Set xPE = Nothing
    End If
    
    
End Sub
