/**************************************************************
 *  Filename:    Page4.cpp
 *  Copyright:   Shanghai Baosight Software Co., Ltd.
 *
 *  Description: �ؼ������Լ�����ʹ��
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

#define MAX_RANGE 100  //�ؼ���Χ���ֵ
#define MIN_RANGE 0    //�ؼ���Χ��Сֵ
#define PER_RANGE 1    //�仯��
#define PER_TIME  100  //ʱ����(����)
#define SLIDE_LINESIZE 5  //�����ƶ��϶���������
#define PAGE_LINESIZE  5  //����ƶ��϶���������
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
 *  �Ի����ʼ������.
 *
 *  �ؼ���ʼ������д���������  ������Ա������Ҫ��ʼ��Ҳ���Է�����(���߷Ź��캯����)
 *  @version  09/08/2004  wangyi  Initial Version.
 */
BOOL CPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	//////////////////////                   ���ݳ�ʼ��  ���Է��빹�캯����������
	m_b1 = m_b2 = m_b3 = m_bInAction = m_bMenu = FALSE;
	m_nInt = MIN_RANGE;
	////////////////////////////////////////////////////////////��ʼ���ؼ�����
	m_cDt.SetFormat("yyyy'��'MM'��'dd'�� 'HH':'mm':'ss");     //����ʱ��ؼ����÷��
	////////////////////////////////////////////////////////////��Ͽ�ؼ���ʼ��
	m_ctrlCombo.AddString("ѡ������1");                       //��Ͽ�ؼ����ѡ������1
	m_ctrlCombo.AddString("ѡ������2");                       //��Ͽ�ؼ����ѡ������2                      
	m_ctrlCombo.AddString("ѡ������3");                       //��Ͽ�ؼ����ѡ������3
	m_ctrlCombo.AddString("ѡ������4");                       //��Ͽ�ؼ����ѡ������4
	m_ctrlCombo.SetCurSel(0);                                 //��Ͽ����ó�ʼѡ��Ϊ��һ��
	////////////////////////////////////////////////////////////SPIN��ʼ��
	m_cs1.SetRange(MIN_RANGE,MAX_RANGE);                      //���÷�Χ
	m_cs1.SetPos(MIN_RANGE);                                  //���ó�ʼ��ֵ
	////////////////////////////////////////////////////////////������ �϶��� �������ؼ���ʼ��
	m_cp1.SetRange(MIN_RANGE,MAX_RANGE);                      //��������Χ
	m_csld.SetRange(MIN_RANGE,MAX_RANGE);                     //�϶�����Χ
	m_cScrollBar.SetScrollRange(MIN_RANGE,MAX_RANGE);         //��������Χ
	m_cp1.SetPos(MIN_RANGE);                                  //��������ʼλ��
	m_csld.SetPos(MIN_RANGE);                                 //�϶�����ʼλ��
	m_cScrollBar.SetScrollPos(MIN_RANGE);                     //��������ʼλ��
	m_csld.SetLineSize(SLIDE_LINESIZE);                       //�϶������ü����ƶ�������
	m_csld.SetPageSize(PAGE_LINESIZE);                        //�϶������õ��������
	m_cbStop.EnableWindow(m_bInAction);                       //��ʼ��ť����ʹ��
	m_cbStart.EnableWindow(!m_bInAction);                     //������ť����ʹ��
	m_csp1.SetWindowText("0");                                //�ı��ؼ���λ
	m_csp2.SetWindowText("0");                                //�ı��ؼ���λ
	m_csp3.SetWindowText("0");                                //�ı��ؼ���λ
	m_csp4.SetWindowText("0");                                //�ı��ؼ���λ	
	////////////////////////////////////////////////////////////�б�ؼ���ʼ��
	m_ImgLargeList.Create(32, 32, ILC_COLOR, 1, 0);	          //��������
	m_ImgSmallList.Create(16, 16, ILC_COLOR, 1, 0);           //��������
	m_hIcon1 = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_LARGE));//���ico
	m_ImgLargeList.Add(m_hIcon1);                             //����ͼƬ����m_ImgLargeList                          
	m_hIcon1 = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_SMALL));//���ico
	m_ImgSmallList.Add(m_hIcon1);                             //����ͼƬ����m_ImgSmallList
	LV_COLUMN Column;                                        
	Column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Column.fmt = LVCFMT_LEFT;
	Column.cx = 60;
	Column.iSubItem = 0;
	Column.pszText = "File";
	m_cList.InsertColumn(0, &Column);
	Column.pszText = "Size";
	m_cList.InsertColumn(1, &Column);                          //�б�ؼ��ı�����п�����
	LV_ITEM item_;                                             //������ʱLV_ITEM�ṹ����
	item_.state = 0;                                           //������ֵ
	item_.stateMask = 0;
	item_.iImage = 0;
	item_.iItem = 0;
	item_.iSubItem = 0;
	item_.pszText = "Hello";
	m_cList.InsertItem(&item_);                                //���ñ�����Ӽ�¼
	m_cList.SetItemText(0, 1, "50k");                          //�������
	item_.iItem = 1;                                           //���½ṹ������ı���
	item_.iSubItem = 0;                                        //������ֵ
	item_.pszText = "Music";                                   //���½ṹ������ı���
	m_cList.InsertItem(&item_);                                //���ñ�����Ӽ�¼
	m_cList.SetItemText(1, 1, "1,000k");
	item_.iItem = 2;
	item_.iSubItem = 0;
	item_.pszText = "Book";
	m_cList.InsertItem(&item_);
	m_cList.SetItemText(2, 1, "100k");
	m_cList.SetImageList(&m_ImgSmallList, LVSIL_SMALL);         //����ͼƬ����
	m_cList.SetImageList(&m_ImgLargeList, LVSIL_NORMAL);        //����ͼƬ����
	//////////////////////////////////////////////////////////////���ؼ���ʼ��
	m_imgTree.Create(16, 16, ILC_COLOR, 2, 0);                  //���ؼ�ͼƬ������
	m_imgTree.Add(m_hIcon1);
	m_hIcon1 = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_LIST2));
	m_imgTree.Add(m_hIcon1);
	m_cTree.SetImageList(&m_imgTree, TVSIL_NORMAL);
	TV_ITEM item1;                                              //������ʱTV_ITEM�ṹ����
	item1.mask = TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE;       //������ֵ
	item1.pszText = "Family";
	item1.cchTextMax = 8;
	item1.iImage = 0;
	item1.iSelectedImage = 0;
	TV_INSERTSTRUCT	ins_str;                                     //������ʱTV_INSERTSTRUCT�ṹ����
	ins_str.hParent = TVI_ROOT;                                  //������ֵ
	ins_str.hInsertAfter = TVI_FIRST;
	ins_str.item = item1;
	HTREEITEM hRoot = m_cTree.InsertItem(&ins_str);              //���ñ��������
	item1.pszText = "mummy";                                     //������ֵ
	item1.cchTextMax = 8;
	item1.iImage = 1;
	item1.iSelectedImage = 1;
	ins_str.hParent = hRoot;
	ins_str.hInsertAfter = TVI_FIRST;
	ins_str.item = item1;
	HTREEITEM hChildItem = m_cTree.InsertItem(&ins_str);         //���ñ��������
	item1.pszText = "daddy";                                     //������ֵ
	item1.cchTextMax = 8;
	item1.iImage = 1;
	item1.iSelectedImage = 1;
	ins_str.hParent = hRoot;
	ins_str.hInsertAfter = TVI_LAST;
	ins_str.item = item1;
	m_cTree.InsertItem(&ins_str);	                             //���ñ��������
	///////////////////////////////////////////////////////////////����
	return TRUE;  
}


void CPage4::OnButtonStart() 
{
	m_ntimer = SetTimer(1,PER_TIME,NULL);          //�򿪶�ʱ�� ÿ100���봥��һ�ζ�ʱ�� ֱ����ʱ�����ر�		
	m_bInAction = TRUE;                            //��������
	m_cbStop.EnableWindow(m_bInAction);            //����ֹͣ��ťʹ��
	m_cbStart.EnableWindow(!m_bInAction);          //���ÿ�ʼ��ťdisable
}

void CPage4::OnButtonStop()    
{
	if (m_bInAction)                               //�Ƿ������ʹ��
	{
		KillTimer(1);                              //�رն�ʱ��1
		m_bInAction = FALSE;                       //������ʹ��
		m_cbStop.EnableWindow(m_bInAction);        //ֹͣ��ťʹ��
		m_cbStart.EnableWindow(!m_bInAction);      //��ʼ��ťdisable
	}	
}

void CPage4::OnButtonBold() 
{
	CHARFORMAT charformat;                            //��ʱ��ʱCHARFORMAT�ṹ����
	charformat.cbSize = sizeof(CHARFORMAT);           //���ýṹ�������������
	charformat.dwMask = CFM_BOLD;
	m_cRichEdit.GetSelectionCharFormat(charformat);   //���RichEditѡ���ı��ĸ�ʽ
	if (charformat.dwEffects & CFM_BOLD)              //�Ƚ�  �����ͬ
		charformat.dwEffects = 0;
	else                                              //����ͬ
		charformat.dwEffects = CFM_BOLD;
	m_cRichEdit.SetSelectionCharFormat(charformat);   //����RichEditѡ���ı��ĸ�ʽ
	m_cRichEdit.SetFocus();	                          //�۽��ı�
	
}

void CPage4::OnButtonUline()                          //����OnButtonBold()
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

void CPage4::OnButtonItalic()                        //����OnButtonBold()
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
	//�����б�ؼ����Ϊ��ͼ����
	SetWindowLong(m_cList.m_hWnd, GWL_STYLE, WS_VISIBLE|WS_CHILD|
		WS_BORDER|LVS_ICON|LVS_EDITLABELS);		
}

void CPage4::OnButtonSmall() 
{
	//�����б�ؼ����ΪСͼ����
	SetWindowLong(m_cList.m_hWnd, GWL_STYLE, WS_VISIBLE|WS_CHILD|
		WS_BORDER|LVS_SMALLICON|LVS_EDITLABELS);	
}

void CPage4::OnButtonList() 
{
	//�����б�ؼ����Ϊ�б���
	SetWindowLong(m_cList.m_hWnd, GWL_STYLE, WS_VISIBLE|WS_CHILD|
		WS_BORDER|LVS_LIST|LVS_EDITLABELS);	
}

void CPage4::OnButtonReport() 
{
	//�����б�ؼ����Ϊ������
	SetWindowLong(m_cList.m_hWnd, GWL_STYLE, WS_VISIBLE|WS_CHILD|
		WS_BORDER|LVS_REPORT|LVS_EDITLABELS);	
}


/**
 *  ���IP��ַ�ؼ�������ֵ ��ʾ����.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  �ú�������תIP��ַ��ʱ�򱻴���
 *  @version  09/08/2004  wangyi  Initial Version.
 */
void CPage4::OnFieldchangedIpaddress2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	BYTE nField0, nField1,nField2,nField3;                        //����BYTE��ʱ����
	m_cIp.GetAddress(nField0, nField1,nField2,nField3);           //���IP�����ĸ���ֵ
	CString s;                                                    //����cstring��ʱ����
	s.Format("%d.%d.%d.%d",nField0, nField1,nField2,nField3);     //�����ֵ�ɿɹ���ʾ���ַ���
	m_csDisp.SetWindowText(s);                                    //��ʾ����
	*pResult = 0;
	//  ���Ի��IP��ַ�ؼ�����ķ���2
	//	DWORD dwAddress;                                   //����DWORD��ʱ����
	//	m_ctrlIP.GetAddress(dwAddress);                    //IP��ַת���ɱ���
	//	int n1 = dwAddress/(256*256*256);                  //�����Ͷ�ȡDWORD ����������
	//	int n2 = (dwAddress%(256*256*256))/(256*256);
	//	int n3 = (dwAddress%(256*256))/256;
	//	int n4 = dwAddress%256;                            //��������ͬ��������ϳ�IP��ַ�ַ���
}

/**
 *  �������ʱ��ؼ�����ֵ ��ʾ����.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  �ú����ڸ��Ŀؼ���ֵ�󱻴���
 *  @version  09/08/2004  wangyi  Initial Version.
 */
void CPage4::OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTime tm;                                                    //����CTime����
	m_cDt.GetTime(tm);                                           //�ӿؼ������øñ�����ֵ
	m_csDisp.SetWindowText(tm.Format("%A, %B %d, %Y  %H:%M:%S"));//��ʾ���� CTime�Լ��ṩ��ת���ַ����ĺ���
}

/**
 *  ������ڿؼ�����ֵ ��ʾ����.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  �ú����ڸ��Ŀؼ���ֵ�󱻴���
 *  @version  09/08/2004  wangyi  Initial Version.
 */
void CPage4::OnSelchangeMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTime tm1;                           //�ο�OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult) 
	m_cMonth.GetCurSel(tm1);
	//tm1 -= CTimeSpan(83841868);	         //������ֵ ��ֵ���ڲ���ȷ
	m_csDisp.SetWindowText(tm1.Format("%A, %B %d, %Y"));//��ʾ���� CTime�Լ��ṩ��ת���ַ����ĺ���
}

/**
 *  ����϶����ؼ�����ֵ ��ʾ����.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  �ú������϶��ÿؼ�������
 *  @version  09/08/2004  wangyi  Initial Version.
 */void CPage4::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CString s;                                            //����cstring ����
	s.Format("%d", m_csld.GetPos());                      //�ӿؼ���ñ�����ֵ
	m_csp3.SetWindowText(s);		                          //��ʾ
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar); 
}

//��ʱ������
void CPage4::OnTimer(UINT nIDEvent) 
{
	if (m_nInt<MAX_RANGE)                            //�ؼ���û�е����
	{
		m_nInt += PER_RANGE;                         //λ�ñ�������
		m_strInfo.Format("%d%%", m_nInt);              //�����ֵ
		m_csp2.SetWindowText(m_strInfo);            //��ʾ
		if(m_b1)
		{
			m_cp1.SetPos(m_nInt);                    //���½�����λ��
			m_strInfo.Format("%d", m_cp1.GetPos());  //�ӿؼ���ñ�����ֵ
			m_csp1.SetWindowText(m_strInfo);         //��ʾ
		}
		if(m_b2)
		{
			m_csld.SetPos(m_nInt);                   //�����϶���λ��
			m_strInfo.Format("%d", m_csld.GetPos()); //�ӿؼ���ñ�����ֵ
			m_csp3.SetWindowText(m_strInfo);         //��ʾ
		}
		if(m_b3)
		{
			m_cScrollBar.SetScrollPos(m_nInt);       //���¹�����λ��
			m_strInfo.Format("%d", m_cScrollBar.GetScrollPos()); //�ӿؼ���ñ�����ֵ
			m_csp4.SetWindowText(m_strInfo);         //��ʾ
		}
		UpdateData(FALSE);
	}
	else
	{
		KillTimer(1);                              //�رն�ʱ��1
		m_cp1.SetPos(MIN_RANGE);                   //�������ؼ�������λ
		m_csld.SetPos(MIN_RANGE);                  //�϶����ؼ�������λ
		m_cScrollBar.SetScrollPos(MIN_RANGE);      //�������ؼ�������λ
		m_nInt = MIN_RANGE;                        //����ֵ��λ
		m_csp1.SetWindowText("0");                 //�ı��ؼ���λ
		m_csp2.SetWindowText("0");                 //�ı��ؼ���λ
		m_csp3.SetWindowText("0");                 //�ı��ؼ���λ
		m_csp4.SetWindowText("0");                 //�ı��ؼ���λ
		m_bInAction = FALSE;                       //��������
		m_cbStop.EnableWindow(m_bInAction);        //����ֹͣ��ťdisable
		m_cbStart.EnableWindow(!m_bInAction);      //���ÿ�ʼ��ťʹ��
		UpdateData(FALSE);                         //ȷ��
	}
}

/**
 *  ��ʾ����Ͽ�ѡ���ѡ��.
 *
 *  @param  -[in,out]  NMHDR*  pNMHDR: [comment]
 *  @param  -[in,out]  LRESULT*  pResult: [comment]
 *  �ú�����ѡ����Ͽ�ѡ��󴥷�
 *  @version  09/08/2004  wangyi  Initial Version.
 */
void CPage4::OnSelchangeCombo1() 
{
	UpdateData();                            //����
	m_ctrlCombo.GetWindowText(m_strEdit3);   //���ѡ����ַ������ı��ؼ��󶨵ı���
	UpdateData(FALSE);                       //��ʾ
}


void CPage4::OnRadio7() 
{
	m_b2 = m_b3 = FALSE;  //�϶��� �� ������  Disable
	m_b1 = TRUE;        //������Enable
}

void CPage4::OnRadio8() 
{
	m_b1 = m_b3 = FALSE;  //������ �� ������ Disable
	m_b2 = TRUE;        //�϶��� Enable
}

void CPage4::OnRadio9() 
{
	m_b1 = m_b2 = FALSE;  //������ �� �϶��� Disable
	m_b3 = TRUE;        //������ Enable
}

void CPage4::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_bMenu)                                                          //������̬�˵�
	{
		POSITION pt = m_cList.GetFirstSelectedItemPosition();            //�Ƿ����ѡ���б�ؼ���¼
		if (pt == NULL)
		{
			return;                                                      //ûѡ���򲻴�����̬�˵�
		}
		CPoint point;
		::GetCursorPos(&point);                                          //����������λ��
		CMenu DynaMenu;                                                  //��̬�˵���ʱ����
		DynaMenu.CreatePopupMenu();                                      //���ô�������
		DynaMenu.AppendMenu(MF_STRING,IDM_EVENT1,"�Զ���˵�ѡ��1");     //���Ӳ˵���
		DynaMenu.AppendMenu(MF_STRING,IDM_EVENT2,"�Զ���˵�ѡ��2");     //���Ӳ˵���
		DynaMenu.AppendMenu(MF_STRING,IDM_EVENT3,"�Զ���˵�ѡ��3");     ///���Ӳ˵���
		DynaMenu.TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);//��̬�����˵���
	}
	*pResult = 0;
}

void CPage4::OnCheck() 
{
	m_bMenu = !m_bMenu;  //FALSE -> TRUE -> FALSE		
}
