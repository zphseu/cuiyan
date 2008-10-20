// DynDialogItemEx.h: interface for the CDynDialogItemEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNDIALOGITEMEX_H__CF5AF5E9_BD00_11D3_AA7C_0008C7083CA9__INCLUDED_)
#define AFX_DYNDIALOGITEMEX_H__CF5AF5E9_BD00_11D3_AA7C_0008C7083CA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum {
	NOCONTROL		= 0,
	BUTTON			= 0x0080,
	EDITCONTROL		= 0x0081,
	STATICTEXT		= 0x0082,
	LISTBOX			= 0x0083,
	HSCROLL			= 0x0084,
	COMBOBOX		= 0x0085,
	SPIN,
	PROGRES,
	SLIDER,
	HOTKEY,
	LISTCTRL,
	TREECTRL,
	TABCTRL,
	ANIMATE,
	RICHEDIT,
	DATETIMEPICKER,
	MONTHCALENDER,
	IPADRESS,
	COMBOBOXEX
} DLGITEMTEMPLATECONTROLS;

class CDynDialogItemEx : public CWnd
{
// Construction
public:
	CDynDialogItemEx();
	
// Operations
public:
	UINT InitDialogItem(DLGITEMTEMPLATECONTROLS TypeControl, DWORD dwStyle,
			DWORD dwExtendedStyle, LPRECT pRect, LPCTSTR lpszCaption,  
			UINT nID = 0, BOOL bSubclassed = FALSE, VOID *pData = NULL);

	UINT InitDialogItem(LPCSTR lpszClassName, DWORD dwStyle,
			DWORD dwExtendedStyle, LPRECT pRect, LPCTSTR lpszCaption, 
			UINT nID = 0, BOOL bSubclassed = FALSE, VOID *pData = NULL);

	BOOL CreateEx(CWnd *pParent);
	void SetFont(CFont* pFont, BOOL bRedraw = TRUE);

// Operations
public:
	virtual void DoDataExchange(CDataExchange* pDX);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynDialogItemEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	//virtual ~CDynDialogItemEx();
	BOOL SetWindowPos(CWnd *pParent);
	PBYTE FillBufferWithItemTemplate(BYTE* pdest);

	UINT GetControlID()								{return m_ControlID;}
	DLGITEMTEMPLATECONTROLS GetControlType()		{return m_eTypeControl;}
	long GetCaptionLength()							{return m_strCaption.GetLength();}
	BOOL IsDlgItemSubclassed()						{return m_bSubclassed;}
	CString GetClassName()							{return m_strClassName;}		

protected:
	DLGITEMTEMPLATECONTROLS GetClassTypeByName(LPCSTR lpszClassName);

	DLGITEMTEMPLATECONTROLS	m_eTypeControl;
	CString		m_strClassName;
	UINT		m_ControlID;
	UINT		m_dwStyle;
	UINT		m_dwStyleEx;
	CRect		m_Rect;
	CString		m_strCaption;
	VOID		*m_pData;
	BOOL		m_bSubclassed;
	static UINT	m_nNextID;
	// Generated message map functions
protected:
	UINT	GetNewUniqueID();
	BOOL	IsDataMemberPointerToWnd();
	BSTR	GetRuntimeLicense(CString &strControlName);
	LPTSTR	GetClassNameByType(DLGITEMTEMPLATECONTROLS TypeControl);
	
	//{{AFX_MSG(CDynDialogItemEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static struct RuntimeLicense {
		LPCTSTR lpszRegisteredControlName;
		WCHAR *wchLicenseKey;
		long lLicenseLength;
	} m_RuntimeLicenses[];

};

#endif // !defined(AFX_DYNDIALOGITEMEX_H__CF5AF5E9_BD00_11D3_AA7C_0008C7083CA9__INCLUDED_)
