// T1Doc.h : interface of the CT1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_T1DOC_H__7FE733BE_2668_427E_8952_B015C43DF8E1__INCLUDED_)
#define AFX_T1DOC_H__7FE733BE_2668_427E_8952_B015C43DF8E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CT1Doc : public CDocument
{
protected: // create from serialization only
	CT1Doc();
	DECLARE_DYNCREATE(CT1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CT1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CT1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T1DOC_H__7FE733BE_2668_427E_8952_B015C43DF8E1__INCLUDED_)
