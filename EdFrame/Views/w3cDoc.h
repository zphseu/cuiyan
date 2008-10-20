// w3cDoc.h : interface of the CW3CDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_W3CDOC_H__34D3CD33_545F_4DB1_8D59_67A1D6F86B2E__INCLUDED_)
#define AFX_W3CDOC_H__34D3CD33_545F_4DB1_8D59_67A1D6F86B2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CW3CDoc : public CDocument
{
protected: // create from serialization only
	CW3CDoc();
	DECLARE_DYNCREATE(CW3CDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CW3CDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CW3CDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CW3CDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_W3CDOC_H__34D3CD33_545F_4DB1_8D59_67A1D6F86B2E__INCLUDED_)
