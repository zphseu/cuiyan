// STabDialog.h: interface for the CSTabDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STABDIALOG_H__2807BBE8_3C1D_4D93_855F_7EBC7B4C0E1C__INCLUDED_)
#define AFX_STABDIALOG_H__2807BBE8_3C1D_4D93_855F_7EBC7B4C0E1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "STabCtrl.h"

extern "C" BOOL Validate(LPCSTR szRes);

class CSTabDialog : public CDialog  
{
public:
	CSTabDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL)
		: CDialog(nIDTemplate, pParentWnd), m_csTitle(_T("请在构造函数中修改标题")), m_nIDD(nIDTemplate) {}
	
	virtual ~CSTabDialog() {}

	void InsertTo(CSTabCtrl &tabCtrl, CWnd* pParentWnd)
	{
		if (!Validate(m_csTitle))
			return;

		TC_ITEM tcItem;
		tcItem.mask = TCIF_TEXT;
		int nIndex = tabCtrl.GetItemCount();
		
		CDialog::Create(m_nIDD, pParentWnd);
		tcItem.pszText = GetTitle();
		tcItem.cchTextMax = strlen(GetTitle());
		tabCtrl.InsertItem(nIndex, &tcItem);
		tabCtrl.AttachControlToTab(this, nIndex);
	}
	LPSTR GetTitle() { return (LPSTR)(LPCSTR)m_csTitle; }
protected:
	int m_nIDD;
	CString	m_csTitle;
	//{{AFX_MSG(CSTabDialog)
		//Called after the size of CWnd has changed.
	//}}AFX_MSG

	//{{AFX_VIRTUAL(CSTabDialog)
	public:
	virtual void OnCancel() {};
	virtual void OnOK() {};
	//}}AFX_VIRTUAL
};

#endif // !defined(AFX_STABDIALOG_H__2807BBE8_3C1D_4D93_855F_7EBC7B4C0E1C__INCLUDED_)
