VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5640
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8355
   LinkTopic       =   "Form1"
   ScaleHeight     =   5640
   ScaleWidth      =   8355
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   495
      Left            =   120
      TabIndex        =   10
      Top             =   240
      Width           =   1455
   End
   Begin VB.TextBox Text2 
      Height          =   855
      Left            =   2280
      TabIndex        =   9
      Text            =   "Text2"
      Top             =   2280
      Width           =   5295
   End
   Begin VB.ListBox List1 
      Height          =   840
      Left            =   3000
      TabIndex        =   8
      Top             =   4200
      Width           =   5175
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      Left            =   360
      TabIndex        =   7
      Text            =   "Combo1"
      Top             =   4080
      Width           =   2415
   End
   Begin VB.TextBox Text1 
      Height          =   735
      Left            =   2160
      TabIndex        =   6
      Text            =   "Text1"
      Top             =   1200
      Width           =   5175
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Command4"
      Height          =   375
      Left            =   5040
      TabIndex        =   2
      Top             =   480
      Width           =   1695
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Command3"
      Height          =   375
      Left            =   3480
      TabIndex        =   1
      Top             =   360
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Command2"
      Height          =   495
      Left            =   1920
      TabIndex        =   0
      Top             =   360
      Width           =   1095
   End
   Begin VB.Label Label3 
      Caption         =   "Label3"
      Height          =   495
      Left            =   480
      TabIndex        =   5
      Top             =   3120
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Label2"
      Height          =   615
      Left            =   480
      TabIndex        =   4
      Top             =   2160
      Width           =   1335
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   495
      Left            =   480
      TabIndex        =   3
      Top             =   1320
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

  'persistent handle to the internet
  Private hInternet As Long

  'persistent handle internet connection
  Private hConnect As Long

  'default FTP login data
  Private Const sFtpUserName = "anonymous"
  Private Const sFtpPassword = "yourname@someplace.com"

  'constants are more efficient than literals
  'when used in several places
  Private Const sRootDots = ".."
  Private Const sSlash = "/"



Private Sub Command1_Click()
     
     Dim sServerName As String
     
    'Show the wait cursor
     Screen.MousePointer = vbHourglass
     
    'Begin the FTP process by obtaining a
    'handle to an internet session. This
    'handle will be used in subsequent calls,
    'so its declared as a form-wide variable.
     hInternet = InternetOpen("VBnet FTP Transfer", _
                               INTERNET_OPEN_TYPE_DIRECT, _
                               vbNullString, _
                               vbNullString, _
                               INTERNET_FLAG_NO_CACHE_WRITE)
     
    'If a handle was obtained, the next step is
    'to obtain a connection handle that will be
    'used for all operations except the FTP
    'directory navigation. The MSDN states that
    'the handle used by FtpFindFirstFile and subsequent
    'file calls can not be reused for additional
    'navigation or other operations. This handle
    'then will be used for all functions except
    'the directory listings.
     If hInternet Then
     
        sServerName = Combo1.Text
              
       'and get a connection handle
        hConnect = InternetConnect(hInternet, _
                                   sServerName, _
                                   INTERNET_DEFAULT_FTP_PORT, _
                                   sFtpUserName, _
                                   sFtpPassword, _
                                   INTERNET_SERVICE_FTP, _
                                   INTERNET_FLAG_EXISTING_CONNECT Or _
                                   INTERNET_FLAG_PASSIVE, _
                                   &H0)
     
       'if the connection handle is valid, get
       'the current FTP directory
        If hConnect <> 0 Then
        
          'reflect the current path in the
          'text box (it should be '\' )
           Text1.Text = GetFTPDirectory(hConnect)
           
        Else
        
          'show the error
           Text2.Text = TranslateErrorCode(Err.LastDllError)
          
        End If
        
     End If
     
    'display the session handles
     Label3.Caption = hConnect
     Label2.Caption = hInternet
     
    'If both handles are valid, disable the Open button
    'and enable the FTP button. If *either* handle is
    'valid, enable the close button.
     Command1.Enabled = (hInternet = 0) And (hConnect = 0)
     Command2.Enabled = (hInternet <> 0) And (hConnect <> 0)
     Command3.Enabled = (hInternet <> 0) Or (hConnect <> 0)
     Command4.Enabled = False
     
     Screen.MousePointer = vbDefault
End Sub

  Private Sub Command2_Click()

     Call GetFTPDirectoryContents
     
  End Sub


  Private Sub Command3_Click()

    'clean up
     Call InternetCloseHandle(hConnect)
     Call InternetCloseHandle(hInternet)
     
     hInternet = 0
     hConnect = 0

     Label2.Caption = "Closed"
     Label3.Caption = "No connection"
     
    'If both handles are valid, enable the Open button
    'and disable the FTP button. If *either* handle is
    'valid, disable the close button. The download
    'button is disabled.
     Command1.Enabled = (hInternet = 0) And (hConnect = 0)
     Command2.Enabled = (hInternet <> 0) And (hConnect <> 0)
     Command3.Enabled = (hInternet <> 0) Or (hConnect <> 0)
     Command4.Enabled = False
     
     List1.Clear
     
  End Sub

  Private Sub Form_Load()
     
     Label2.Caption = "Closed"
     Label3.Caption = "No connection"
     Text1.Text = ""
     Text2.Text = ""
     Command1.Caption = "Open"
     Command2.Caption = "FtpFindFirstFile"
     Command3.Caption = "Close"
     Command4.Caption = "Not used yet"
     Command2.Enabled = True
     Command2.Enabled = False
     Command3.Enabled = False
     Command4.Enabled = False
        
     With Combo1
        .AddItem "168.2.4.55"  'localhost
        .ListIndex = 0
     End With
     
  End Sub


  Private Sub Form_Unload(Cancel As Integer)

    'if the handle is still valid,
    'clean up before exiting
     If hInternet Or hConnect Then Command3.Value = True
     
  End Sub


  Private Sub List1_DblClick()

     Dim sNewPath As String
     Dim sPath As String
     
    'get the desired directory from the list
     sNewPath = List1.List(List1.ListIndex)
       
    'If a root item selected, exit; the routine
    'will navigate a level higher. If its
    'a file, we don't want to navigate.
     If sNewPath <> sRootDots And Right$(sNewPath, 1) <> sSlash Then
     
       'root or file selected
        Exit Sub
        
     Else
     
       'Show the wait cursor
        Screen.MousePointer = vbHourglass
        
       'clear the list in preparation for
       'retrieving the directory contents
        List1.Clear
     
       'retrieve the current FTP path
       'using GetFTPDirectory
        sPath = GetFTPDirectory(hConnect)
        
       'qualify it if necessary, and append
       'the new path to it
        If Right$(sPath, 1) <> sSlash Then
           sPath = sPath & sSlash & sNewPath
        Else
           sPath = sPath & sNewPath
        End If
        
       'set the new path using the API
        Call FtpSetCurrentDirectory(hConnect, sPath)
        
       'reflect the new path in the text box
        Text1.Text = GetFTPDirectory(hConnect)
        
       'reload the list with the current directory
        GetFTPDirectoryContents
        
        Screen.MousePointer = vbDefault
        
     End If
     
  End Sub


  Private Function GetFTPDirectory(hConnect As Long) As String

     Dim nCurrDir As Long
     Dim sCurrDir As String
     
    'FtpGetCurrentDirectory retrieves the current
    'directory for the connection. Using this API
    'means its not necessary to track the directory
    'hierarchy for navigation.
    
    'pad the requisite buffers
     sCurrDir = Space$(256)
     nCurrDir = Len(sCurrDir)
        
    'returns 1 if successful
     If FtpGetCurrentDirectory(hConnect, sCurrDir, nCurrDir) = 1 Then
        
       'return a properly qualified path
        sCurrDir = StripNull(sCurrDir)
        
        If Right$(sCurrDir, 1) <> sSlash Then
              GetFTPDirectory = sCurrDir & sSlash
        Else: GetFTPDirectory = sCurrDir
        End If
        
     End If

  End Function


  Private Sub GetFTPDirectoryContents()

     Dim WFD As WIN32_FIND_DATA
     Dim sPath As String
     Dim hFindConnect As Long
     Dim hFind As Long
     Dim sFileSize As String
     Dim tmp As String
     
    'Show the wait cursor
     Screen.MousePointer = vbHourglass

    'Obtain the current FTP path
     sPath = GetFTPDirectory(hConnect)
     
    'If the path is not the FTP base directory,
    'add ".." to provide a means of navigating
    'back up the directory structure. (Note: I added this
    'for use on a localhost test - in testing on some
    'sites I found that they returned '.' and '..' as
    'folders, so ideally a check would want to be made
    'in the GetFolders method to avoid loading duplicates.)
     If sPath <> sSlash Then List1.AddItem sRootDots
     
    'The search parameters .. here we'll list
    'all file types. Since GetFTPDirectory takes
    'care of qualifying the path, no terminating
    'slash is required.
     sPath = sPath & "*.*"
        
    'Conation handles used by the FtpFindFirstFile
    'API go out of scope once the all files are
    'listed, therefore it can not be reused.
    'This restriction is handled by obtaining
    'a fresh connection handle each time a call
    'to FtpFindFirstFile is required, and releasing
    'it once finished.
     hFindConnect = GetInternetConnectHandle()
     
    'If a good connection handle ...
     If hFindConnect Then
     
       '..obtain the handle to the files with
       'the FtpFindFirstFile API. Obtaining the
       'directory contents is essentially similar
       'to using the Win32 file system APIs
       'FindFirstFile and FindNextFile, with the
       'sole exception that there is no FtpFindNextFile
       'API. Instead, successive calls are made
       'to InternetFindNextFile. The data returned
       'is in the familiar WIN32_FIND_DATA structure.
        hFind = FtpFindFirstFile(hFindConnect, _
                                 sPath, WFD, _
                                 INTERNET_FLAG_RELOAD Or _
                                 INTERNET_FLAG_NO_CACHE_WRITE, 0&)
     
          'If a valid find handle returned,
          'loop through the directory listing
          'the contents. If the attributes of
          'the returned string indicate a folder,
          'append a slash to make it both visually
          'stand out in the list, and identifiable
          'in the list double-click routine for
          'navigation.
          '
          'hFile will be 0 if the navigated-to
          'folder is empty.
           If hFind Then

              Do
              
                 tmp = StripNull(WFD.cFileName)
                                
                 If Len(tmp) Then
                    If WFD.dwFileAttributes And vbDirectory Then
                          List1.AddItem tmp & sSlash
                    Else: List1.AddItem tmp
                    End If
                 End If
                 
              
             'continue while valid
              Loop While InternetFindNextFile(hFind, WFD)
        
           End If 'If hFind

     End If  'If hFindConnect
     
    'clean up by closing the handles used in this routine
     Call InternetCloseHandle(hFind)
     Call InternetCloseHandle(hFindConnect)

     Screen.MousePointer = vbDefault
     
  End Sub


  Private Function GetInternetConnectHandle() As Long

     Dim sServerName As String
     Dim tmp As Long

    'GetInternetConnectHandle obtains a new
    'handle expressly for use with the
    'FtpFindFirstFile and APIs.
    '
    'Care must be taken to close only the handle
    'returned by this function once the listing
    'of the directory has been obtained.
    '
    'A temporary variable is used here
    'to reduce line length
     If hInternet Then
     
       'Pass the same server as with other
       'calls, along with the requisite username
       'and password. The Microsoft FTP site
       'allows anonymous login, so the username
       'is 'anonymous' and the password is the
       'user's email address.
        sServerName = Combo1.Text

        tmp = InternetConnect(hInternet, _
                              sServerName, _
                              INTERNET_DEFAULT_FTP_PORT, _
                              sFtpUserName, _
                              sFtpPassword, _
                              INTERNET_SERVICE_FTP, _
                              INTERNET_FLAG_EXISTING_CONNECT Or _
                              INTERNET_FLAG_PASSIVE, _
                              &H0)
                                                   
     End If
    
    'return the connection handle
     GetInternetConnectHandle = tmp
        
  End Function



Private Sub List1_Click()

     Dim sNewPath As String
     Dim sPath As String
     
    'get the desired directory from the list
     sNewPath = List1.List(List1.ListIndex)
     
    'If a root item or directory is selected,
    'disable the download button
     Command4.Enabled = (Right$(sNewPath, 1) <> sSlash) And _
                        (sNewPath <> sRootDots)

  End Sub


  Private Sub Command4_Click()
     
     Dim sRemoteFile As String
     Dim sNewFile As String
     Dim sFile As String
     Dim sCurrDir As String
      
    'Show the wait cursor
     Screen.MousePointer = vbHourglass
     
    'Only if a valid connection...
     If hConnect Then
        
       'get the current directory and
       'selected list item
        sCurrDir = GetFTPDirectory(hConnect)
        sFile = (List1.List(List1.ListIndex))

       'build the necessary strings. The
       'directory is qualified, so contains
       'the terminating slash.
       '
       'Change sNewFile to a valid path
       'on your system!
        sRemoteFile = sCurrDir & sFile
        sNewFile = "e:\temp\" & sFile
        
       'just a message to tell what's happening
        Text2.Text = "attempting to downloaded " & sFile & sRootDots
        Text2.Refresh
        
       'download the file
        If FtpGetFile(hConnect, _
                      sRemoteFile, _
                      sNewFile, _
                      False, _
                      FILE_ATTRIBUTE_ARCHIVE, _
                      FTP_TRANSFER_TYPE_UNKNOWN, _
                      0&) Then
           
          'show the success message
           Text2.Text = sFile & " has been downloaded to " & sNewFile
                         
        Else:
        
          'show any error
           Text2.Text = TranslateErrorCode(Err.LastDllError)
        
        End If  'If FtpGetFile
     End If 'If hConnect

     Screen.MousePointer = vbDefault
     
  End Sub


