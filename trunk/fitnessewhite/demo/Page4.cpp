/**************************************************************
 *  Filename:    Page4.cpp
 *  Copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  Description: 控件介绍以及基本使用
 *
 *  @author:     wangyi
 *  @version     09/08/2004  wangyi  Initial Version
**************************************************************/


#include "stdafx.h"
#include "Controls_Demo.h"
#include "Page4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_RANGE 100  //控件范围最大值
#define MIN_RANGE 0    //控件范围最小值
#define PER_RANGE 1    //变化量
#define PER_TIME  100  //时间间隔(毫秒)
#define SLIDE_LINESIZE 5  //键盘移动拖动条的增量
#define PAGE_LINESIZE  5  //鼠标移动拖动条的增量
/////////////////////////////////////////////////////////////////////////////
// CPage4 property page

IMPLEMENT_DYNCREATE(CPage4, CPropertyPage)

CPage4::CPage4() : CPropertyPage(CPage4::IDD)
{
	//{{AFX_DATA_INIT(CPage4)
	m_strEdit3 = _T("");
	//}}AFX_DATA_INIT
	AfxInitRichEdit();
}

CPage4::~CPage4()
{
}

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage4)
	DDX_Control(pDX, IDC_STATIC4, m_csp4);
	DDX_Control(pDX, IDC_STATIC3, m_csp3);
	DDX_Control(pDX, IDC_STATIC2, m_csp2);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_cScrollBar);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlCombo);
	DDX_Control(pDX, IDC_TREE, m_cTree);
	DDX_Control(pDX, IDC_STATIC1, m_csp1);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_cbStop);
	DDX_Control(pDX, IDC_BUTTON_START, m_cbStart);
	DDX_Control(pDX, IDC_STATIC_DISP, m_csDisp);
	DDX_Control(pDX, IDC_SPIN1, m_cs1);
	DDX_Control(pDX, IDC_SLIDER1, m_csld);
	DDX_Control(pDX, IDC_RICHEDIT, m_cRichEdit);
	DDX_Control(pDX, IDC_PROGRESS1, m_cp1);
	DDX_Control(pDX, IDC_MONTHCALENDAR, m_cMonth);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDC_IPADDRESS2, m_cIp);
	DDX_Control(pDX, IDC_EDIT1, m_ce1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_cDt);
	DDX_Text(pDX, IDC_EDIT3, m_strEdit3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CPage4)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_BOLD, OnButtonBold)
	ON_BN_CLICKED(IDC_BUTTON_ULINE, OnButtonUline)
	ON_BN_CLICKED(IDC_BUTTON_ITALIC, OnButtonItalic)
	ON_BN_CLICKED(IDC_BUTTON_LAGE, OnButtonLage)
	ON_BN_CLICKED(IDC_BUTTON_SMALL, OnButtonSmall)
	ON_BN_CLICKED(IDC_BUTTON_LIST, OnButtonList)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnButtonReport)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS2, OnFieldchangedIpaddress2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, OnDatetimechangeDatetimepicker2)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR, OnSelchangeMonthcalendar)
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage4 message handlers


/**
 *  对话框初始化函数.
 *
 *  控件初始化代码写在这个函数  如果类成员变量需要初始化也可以放这里(或者放构造函数中)
 *  @version  09/08/2004  wangyi  Initial Version.
 */
BOOL CPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	//////////////////////                   数据初始化  可以放入构造函数里面设置
	m_b1 = m_b2 = m_b3 = m_bInAction = m_bMenu = FALSE;
	m_nInt = MIN_RANGE;
	////////////////////////////////////////////////////////////初始化控件属性
	m_cDt.SetFormat("yyyy'年'MM'月'dd'日 'HH':'mm':'ss");     //日期时间控件设置风格
	////////////////////////////////////////////////////////////组合框控件初始化
	m_ctrlCombo.AddString("选项内容1");                       //组合框控件添加选项内容1
	m_ctrlCombo.AddString("选项内容2");                       //组合框控件添加选项内容2                      
	m_ctrlCombo.AddString("选项内容3");                       //组合框控件添加选项内容3
	m_ctrlCombo.AddString("选项内容4");                       //组合框控件添加选项内容4
	m_ctrlCombo.SetCurSel(0);                                 //组合框设置初始选项为第一项
	////////////////////////////////////////////////////////////SPIN初始化
	m_cs1.SetRange(MIN_RANGE,MAX_RANGE);                      //设置范围
	m_cs1.SetPos(MIN_RANGE);                                  //设置初始数值
	////////////////////////////////////////////////////////////进度条 拖动条 滚动条控件初始化
	m_cp1.SetRange(MIN_RANGE,MAX_RANGE);                      //进度条范围
	m_csld.SetRange(MIN_RANGE,MAX_RANGE);                     //拖动条范围
	m_cScrollBar.SetScrollRange(MIN_RANGE,MAX_RANGE);         //滚动条范围
	m_cp1.SetPos(MIN_RANGE);                                  //进度条初始位置
	m_csld.SetPos(MIN_RANGE);                                 //拖动条初始位置
	m_cScrollBar.SetScrollPos(MIN_RANGE);                     //滚动条初始位置
	m_csld.SetLineSize(SLIDE_LINESIZE);                       //拖动条设置键盘移动的增量
	m_csld.SetPageSize(PAGE_LINESIZE);                        //拖动条设置点击的增量
	m_cbStop.EnableWindow(m_bInAction);                       //开始按钮设置使能
	m_cbStart.EnableWindow(!m_bInAction);                     //结束按钮设置使能
	m_csp1.SetWindowText("0");                                //文本控件复位
	m_csp2.SetWindowText("0");                                //文本控件复位
	m_csp3.SetWindowText("0");                                //文本控件复位
	m_csp4.SetWindowText("0");                                //文本控件复位	
	////////////////////////////////////////////////////////////列表控件初始化
	m_ImgLargeList.Create(32, 32, ILC_COLOR, 1, 0);	          //建立链表
	m_ImgSmallList.Create(16, 16, ILC_COLOR, 1, 0);           //建立链表
	m_hIcon1 = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_LARGE));//获得ico
	m_ImgLargeList.Add(m_hIcon1);                             //加入图片链表m_ImgLargeList                          
	m_hIcon1 = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_SMALL));//获得ico
	m_ImgSmallList.Add(m_hIcon1);                             //加入图片链表m_ImgSmallList
	LV_COLUMN Column;                                        
	Column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Column.fmt = LVCFMT_LEFT;
	Column.cx = 60;
	Column.iSubItem = 0;
	Column.pszText = "File";
	m_cList.InsertColumn(0, &Column);
	Column.pszText = "Size";
	m_cList.InsertColumn(1, &Column);                          //列表控件的标题和列宽设置
	LV_ITEM item_;                                             //声明临时LV_ITEM结构变量
	item_.state = 0;                                           //变量赋值
	item_.stateMask = 0;
	item_.iImage = 0;
	item_.iItem = 0;
	item_.iSubItem = 0;
	item_.pszText = "Hello";
	m_cList.InsertItem(&item_);                                //利用变量添加记录
	m_cList.SetItemText(0, 1, "50k");                          //按列添加
	item_.iItem = 1;                                           //更新结构变量里的变量
	item_.iSubItem = 0;                                        //变量赋值
	item_.pszText = "Music";                                   //更新结构变量里的变量
	m_cList.InsertItem(&item_);                                //利用变量添加记录
	m_cList.SetItemText(1, 1, "1,000k");
	item_.iItem = 2;
	item_.iSubItem = 0;
	item_.pszText = "Book";
	m_cList.InsertItem(&item_);
	m_cList.SetItemText(2, 1, "100k");
	m_cList.SetImageList(&m_ImgSmallList, LVSIL_SMALL);         //设置图片链表
	m_cList.SetImageList(&m_ImgLargeList, LVSIL_NORMAL);        //设置图片链表
	//////////////////////////////////////////////////////////////树控件初始化
	m_imgTree.Create(16, 16, ILC_COLOR, 2, 0);                  //树控件图片链表建立
	m_imgTree.Add(m_hIcon1);
	m_hIcon1 = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_LIST2));
	m_imgTree.Add(m_hIcon1);
	m_cTree.SetImageList(&m_imgTree, TVSIL_NORMAL);
	TV_ITEM item1;                                              //声明临时TV_ITEM结构变量
	item1.mask = TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE;       //变量赋值
	item1.pszText = "Family";
	item1.cchTextMax = 8;
	item1.iImage = 0;
	item1.iSelectedImage = 0;
	TV_INSERTSTRUCT	ins_str;                                     //声明临时TV_INSERTSTRUCT结构变量
	ins_str.hParent = TVI_ROOT;                                  //变量赋值
	ins_str.hInsertAfter = TVI_FIRST;
	ins_str.item = item1;
	HTREEITEM hRoot = m_cTree.InsertItem(&ins_str);              //利用变量添加项
	item1.pszText = "mummy";                                     //变量赋值
	item1.cchTextMax = 8;
	item1.iImage = 1;
	item1.iSelectedImage = 1;
	ins_str.hParent = hRoot;
	ins_str.hInsertAfter = TVI_FIRST;
	ins_str.item = item1;
	HTREEITEM hChildItem = m_cTree.InsertItem(&ins_str);         //利用变量添加项
	item1.pszText = "daddy";                                     //变量赋值
	item1.cchTextMax = 8;
	item1.iImage = 1;
	item1.iSelectedImage = 1;
	ins_str.hParent = hRoot;
	ins_str.hInsertAfter = TVI_LAST;
	ins_str.item = item1;
	m_cTree.InsertItem(&ins_str);	                             //利用变量添加项
	///////////////////////////////////////////////////////////////结束
	return TRUE;  
}


void CPage4::OnButtonStart() 
{
	m_ntimer = SetTimer(1,PER_TIME,NULL);          //打开定时器 每100毫秒触发一次定时器 直到定时器被关闭		
	m_bInAction = TRUE;                            //变量更新
	m_cbStop.EnableWindow(m_bInAction);            //设置停止按钮使能
	m_cbStart.EnableWindow(!m_bInAction);          //设置开始按钮disable
}

void CPage4::OnButtonStop()    
{
	if (m_bInAction)                               //是否进度条使能
	{
		KillTimer(1);                              //关闭定时器1
		m_bInAction = FALSE;                       //进度条使能
		m_cbStop.EnableWindow(m_bInAction);        //停止按钮使能
		m_cbStart.EnableWindow(!m_bInAction);      //开始按钮disable
	}	
}

void CPage4::OnButtonBold() 
{
	CHARFORMAT charformat;                            //定时临时CHARFORMAT结构变量
	charformat.cbSize = sizeof(CHARFORMAT);           //设置结构变量里变量参数
	charformat.dwMask = CFM_BOLD;
	m_cRichEdit.GetSelectionCharFormat(charformat);   //获得RichEdit选择文本的格式
	if (charformat.dwEffects & CFM_BOLD)              //比较  如果相同
		charformat.dwEffects = 0;
	else                                              //不相同
		charformat.dwEffects = CFM_BOLD;
	m_cRichEdit.SetSelectionCharFormat(charformat);   //设置RichEdit选择文本的格式
	m_cRichEdit.SetFocus();	                          //聚焦文本
	
}

void CPage4::OnButtonUline()                          //参照OnButtonBold()
{
	CHARFORMAT charformat;
	charformat.cbSize = sizeof(CHARFORMAT);
	charformat.dwMask = CFM_UNDERLINE;
	m_cRichEdit.GetSelectionCharFormat(charformat);
	if (charformat.dwEffects & CFM_UNDERLINE)
		charformat.dwEffects = 0;
	else
		charformat.dwEffects = CFM_UNDERLINE;
	m_cRichEdit.SetSelectionCharFormat(charformat);
	m_cRichEdit.SetFocus();			
}

void CPage4::OnButtonItalic()                        //参照OnButtonBold()
{
	CHARFORMAT charformat;
	charformat.cbSize = sizeof(CHARFORMAT);
	charformat.dwMask = CFM_ITALIC;
	m_cRichEdit.GetSelectionCharFormat(charformat);
	if (charformat.dwEffects & CFM_ITALIC)
		charformat.dwEffects = 0;
	else
		charformat.dwEffects = CFM_ITALIC;
	m_cRichEdit.SetSelectionCharFormat(charformat);
	m_cRichEdit.SetFocus();		
}


void CPage4::OnButtonLage() 
{
	//设置列表控件风格为大图标风格
	SetWindowLong(m_cList.m_hWnd, GWL_STYLE, WS_VISIBLE|WS_CHILD|
		WS_BORDER|LVS_ICON|LVS_EDITLABELS);		
}

void CPage4::OnButtonSmall() 
{
	//设置列表控件风格为小图标风格
	SetWindowLong(m_cList.m_hWnd, GWL_STYLE, WS_VISIBLE|WS_CHILD|
		WS_BORDER|LVS_SMALLICON|LVS_EDITLABELS);	
}

void CPage4::OnButtonList() 
{
	//设置列表控件风格为列表风格
	SetWindowLong(m_cList.m_hWnd, GWL_STYLE, WS_VISIBLE|WS_CHILD|
		WS_BORDER|LVS_LIST|LVS_EDITLABELS);	
}

void CPage4::OnButtonReport() 
{
	//设置列表控件风格为报表风格
	SetWindowLong(m_cList.m_hWnd, GWL_STYLE, WS_VISIBLE|WS_CHILD|
		WS_BORDER|LVS_REPORT|LVS_EDITLABELS);	
}


/**
 *  获得IP地址控件的输入值 显示出来.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  该函数在跳转IP地址域时候被触发
 *  @version  09/08/2004  wangyi  Initial Version.
 */
void CPage4::OnFieldchangedIpaddress2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	BYTE nField0, nField1,nField2,nField3;                        //设置BYTE临时变量
	m_cIp.GetAddress(nField0, nField1,nField2,nField3);           //获得IP区域四个数值
	CString s;                                                    //声明cstring临时变量
	s.Format("%d.%d.%d.%d",nField0, nField1,nField2,nField3);     //组合数值成可供显示的字符串
	m_csDisp.SetWindowText(s);                                    //显示出来
	*pResult = 0;
	//  可以获得IP地址控件里面的方法2
	//	DWORD dwAddress;                                   //声明DWORD临时变量
	//	m_ctrlIP.GetAddress(dwAddress);                    //IP地址转换成变量
	//	int n1 = dwAddress/(256*256*256);                  //用整型读取DWORD 获得区域变量
	//	int n2 = (dwAddress%(256*256*256))/(256*256);
	//	int n3 = (dwAddress%(256*256))/256;
	//	int n4 = dwAddress%256;                            //最后可以用同样方法组合成IP地址字符串
}

/**
 *  获得日期时间控件的数值 显示出来.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  该函数在更改控件数值后被触发
 *  @version  09/08/2004  wangyi  Initial Version.
 */
void CPage4::OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTime tm;                                                    //声明CTime变量
	m_cDt.GetTime(tm);                                           //从控件里面获得该变量数值
	m_csDisp.SetWindowText(tm.Format("%A, %B %d, %Y  %H:%M:%S"));//显示出来 CTime自己提供了转换字符串的函数
}

/**
 *  获得日期控件的数值 显示出来.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  该函数在更改控件数值后被触发
 *  @version  09/08/2004  wangyi  Initial Version.
 */
void CPage4::OnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTime tm1;                           //参考OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult) 
	m_cMonth.GetCurSel(tm1);
	//tm1 -= CTimeSpan(83841868);	         //修正数值 数值现在不正确
	m_csDisp.SetWindowText(tm1.Format("%A, %B %d, %Y"));//显示出来 CTime自己提供了转换字符串的函数
}

/**
 *  获得拖动条控件的数值 显示出来.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  该函数在拖动该控件被触发
 *  @version  09/08/2004  wangyi  Initial Version.
 */void CPage4::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CString s;                                            //定义cstring 变量
	s.Format("%d", m_csld.GetPos());                      //从控件获得变量数值
	m_csp3.SetWindowText(s);		                          //显示
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar); 
}

//定时器函数
void CPage4::OnTimer(UINT nIDEvent) 
{
	if (m_nInt<MAX_RANGE)                            //控件还没有到最后
	{
		m_nInt += PER_RANGE;                         //位置变量更新
		m_strInfo.Format("%d%%", m_nInt);              //获得数值
		m_csp2.SetWindowText(m_strInfo);            //显示
		if(m_b1)
		{
			m_cp1.SetPos(m_nInt);                    //更新进度条位置
			m_strInfo.Format("%d", m_cp1.GetPos());  //从控件获得变量数值
			m_csp1.SetWindowText(m_strInfo);         //显示
		}
		if(m_b2)
		{
			m_csld.SetPos(m_nInt);                   //更新拖动条位置
			m_strInfo.Format("%d", m_csld.GetPos()); //从控件获得变量数值
			m_csp3.SetWindowText(m_strInfo);         //显示
		}
		if(m_b3)
		{
			m_cScrollBar.SetScrollPos(m_nInt);       //更新滚动条位置
			m_strInfo.Format("%d", m_cScrollBar.GetScrollPos()); //从控件获得变量数值
			m_csp4.SetWindowText(m_strInfo);         //显示
		}
		UpdateData(FALSE);
	}
	else
	{
		KillTimer(1);                              //关闭定时器1
		m_cp1.SetPos(MIN_RANGE);                   //进度条控件参数复位
		m_csld.SetPos(MIN_RANGE);                  //拖动条控件参数复位
		m_cScrollBar.SetScrollPos(MIN_RANGE);      //滚动条控件参数复位
		m_nInt = MIN_RANGE;                        //增量值复位
		m_csp1.SetWindowText("0");                 //文本控件复位
		m_csp2.SetWindowText("0");                 //文本控件复位
		m_csp3.SetWindowText("0");                 //文本控件复位
		m_csp4.SetWindowText("0");                 //文本控件复位
		m_bInAction = FALSE;                       //变量更新
		m_cbStop.EnableWindow(m_bInAction);        //设置停止按钮disable
		m_cbStart.EnableWindow(!m_bInAction);      //设置开始按钮使能
		UpdateData(FALSE);                         //确定
	}
}

/**
 *  显示在组合框选择的选项.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  该函数在选择组合框选项后触发
 *  @version  09/08/2004  wangyi  Initial Version.
 */
void CPage4::OnSelchangeCombo1() 
{
	UpdateData();                            //读入
	m_ctrlCombo.GetWindowText(m_strEdit3);   //获得选择的字符串到文本控件绑定的变量
	UpdateData(FALSE);                       //显示
}


void CPage4::OnRadio7() 
{
	m_b2 = m_b3 = FALSE;  //拖动条 和 滚动条  Disable
	m_b1 = TRUE;        //进度条Enable
}

void CPage4::OnRadio8() 
{
	m_b1 = m_b3 = FALSE;  //进度条 和 滚动条 Disable
	m_b2 = TRUE;        //拖动条 Enable
}

void CPage4::OnRadio9() 
{
	m_b1 = m_b2 = FALSE;  //进度条 和 拖动条 Disable
	m_b3 = TRUE;        //滚动条 Enable
}

void CPage4::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_bMenu)                                                          //创建动态菜单
	{
		POSITION pt = m_cList.GetFirstSelectedItemPosition();            //是否鼠标选中列表控件记录
		if (pt == NULL)
		{
			return;                                                      //没选中则不创建动态菜单
		}
		CPoint point;
		::GetCursorPos(&point);                                          //获得鼠标坐标位置
		CMenu DynaMenu;                                                  //动态菜单临时变量
		DynaMenu.CreatePopupMenu();                                      //调用创建函数
		DynaMenu.AppendMenu(MF_STRING,IDM_EVENT1,"自定义菜单选项1");     //增加菜单项
		DynaMenu.AppendMenu(MF_STRING,IDM_EVENT2,"自定义菜单选项2");     //增加菜单项
		DynaMenu.AppendMenu(MF_STRING,IDM_EVENT3,"自定义菜单选项3");     ///增加菜单项
		DynaMenu.TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);//动态弹出菜单项
	}
	*pResult = 0;
}

void CPage4::OnCheck() 
{
	m_bMenu = !m_bMenu;  //FALSE -> TRUE -> FALSE		
}
