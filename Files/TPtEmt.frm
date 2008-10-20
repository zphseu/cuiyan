VERSION 5.00
Object = "{5123D834-1AA3-486A-B944-655AD6052BD7}#1.0#0"; "PtEmt.ocx"
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "PtEmt测试程序"
   ClientHeight    =   8130
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   9495
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   8130
   ScaleWidth      =   9495
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox Text4 
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0.0000"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   2052
         SubFormatType   =   1
      EndProperty
      Height          =   285
      Left            =   5640
      TabIndex        =   12
      Text            =   " 0.1"
      Top             =   7440
      Width           =   855
   End
   Begin VB.TextBox Text3 
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0.0000"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   2052
         SubFormatType   =   1
      EndProperty
      Height          =   285
      Left            =   3480
      TabIndex        =   10
      Text            =   " 0.01"
      Top             =   7440
      Width           =   855
   End
   Begin VB.TextBox Text2 
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   2052
         SubFormatType   =   1
      EndProperty
      Height          =   285
      Left            =   1320
      TabIndex        =   8
      Text            =   "100"
      Top             =   7440
      Width           =   855
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      Left            =   3600
      TabIndex        =   5
      Top             =   6840
      Width           =   1455
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Text            =   "Text1"
      Top             =   6240
      Width           =   7215
   End
   Begin VB.CheckBox Check1 
      Caption         =   "平行场Y/似平行场N"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   6840
      Width           =   2415
   End
   Begin VB.CommandButton Command2 
      Caption         =   "电势文件"
      Height          =   375
      Left            =   7800
      TabIndex        =   2
      Top             =   6720
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "灰度文件"
      Height          =   375
      Left            =   7800
      TabIndex        =   1
      Top             =   6240
      Width           =   1455
   End
   Begin PTEMTLib.PtEmtDyt PtEmtDyt 
      Height          =   5895
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   9135
      _Version        =   65536
      _ExtentX        =   16113
      _ExtentY        =   10398
      _StockProps     =   0
   End
   Begin VB.Label Label4 
      Caption         =   "修正因子"
      Height          =   255
      Left            =   4680
      TabIndex        =   11
      Top             =   7440
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "误差"
      Height          =   255
      Left            =   2640
      TabIndex        =   9
      Top             =   7440
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "迭代次数"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   7440
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   " 方法"
      Height          =   255
      Left            =   2880
      TabIndex        =   6
      Top             =   6840
      Width           =   735
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
    'Check2.Value = 0, LDWB; OTHER, LBP
    'Check1.Value = 0, QUA-PAL; OTHER, PAL
    'LPCTSTR sPFileName, SHORT iType, SHORT iMethodType, SHORT dParam1, FLOAT dParam2, FLOAT dParam3
    '文件名，平行场0/似平行场1，方法（LDWB=0，MNR=1，LBP=2）,循环次数，误差极限，修正因子
    PtEmtDyt.PFile2Picture Text1.Text, Check1.Value, Combo1.ListIndex, Text2.Text, Text3.Text, Text4.Text
End Sub

Private Sub Form_Load()
    Text1.Text = "E:\hemin\working\PtEmt\Files\Gray.dat"
    Combo1.AddItem "LDWB"
    Combo1.AddItem "MNR"
    Combo1.AddItem "LBP"
    Combo1.ListIndex = 0
End Sub
