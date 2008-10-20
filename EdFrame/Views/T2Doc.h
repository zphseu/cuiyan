#if !defined(AFX_T2DOC_H__0A6AC922_14BA_4721_BF2B_DD06181EEFB9__INCLUDED_)
#define AFX_T2DOC_H__0A6AC922_14BA_4721_BF2B_DD06181EEFB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T2Doc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CT2Doc document

class CT2Doc : public CDocument
{
protected:
	CT2Doc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CT2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT2Doc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CT2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CT2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T2DOC_H__0A6AC922_14BA_4721_BF2B_DD06181EEFB9__INCLUDED_)
