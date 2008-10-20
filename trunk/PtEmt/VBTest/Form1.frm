VERSION 5.00
Object = "{5123D834-1AA3-486A-B944-655AD6052BD7}#1.0#0"; "PtEmt.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   9045
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   12090
   LinkTopic       =   "Form1"
   ScaleHeight     =   9045
   ScaleWidth      =   12090
   StartUpPosition =   3  'Windows Default
   Begin PTEMTLib.PtEmtDyt PtEmtDyt 
      Height          =   7935
      Left            =   240
      TabIndex        =   5
      Top             =   120
      Width           =   9255
      _Version        =   65536
      _ExtentX        =   16325
      _ExtentY        =   13996
      _StockProps     =   0
   End
   Begin VB.CheckBox Check1 
      Caption         =   "平行场"
      Height          =   255
      Left            =   9840
      TabIndex        =   4
      Top             =   4080
      Value           =   1  'Checked
      Width           =   1455
   End
   Begin VB.ListBox List1 
      Height          =   1815
      Left            =   9840
      TabIndex        =   3
      Top             =   2040
      Width           =   1695
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   360
      TabIndex        =   2
      Text            =   "E:\hemin\working\PtEmt\Files\p_rd1.dat"
      Top             =   8280
      Width           =   7095
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Command2"
      Height          =   495
      Left            =   9840
      TabIndex        =   1
      Top             =   1200
      Width           =   1815
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   495
      Left            =   9840
      TabIndex        =   0
      Top             =   360
      Width           =   1815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    If PtEmtDyt.GFile2Picture(Text1.Text) <> 0 Then
        MsgBox Text1.Text & "不存在！"
    End If
End Sub

Private Sub Command2_Click()
    PtEmtDyt.PFile2Picture Text1.Text, Check1.Value, List1.ListIndex, 0, 0, 0
End Sub

Private Sub Form_Load()
    List1.AddItem "LDWB"
    List1.AddItem "MNR"
    List1.AddItem "LBP"
    List1.ListIndex = 2
End Sub
