// OraSQLDoc.h : interface of the COraSQLDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORASQLDOC_H__4532B17F_5500_4B20_B4FB_8F30EAA0A1E9__INCLUDED_)
#define AFX_ORASQLDOC_H__4532B17F_5500_4B20_B4FB_8F30EAA0A1E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COraSQLDoc : public CDocument
{
protected: // create from serialization only
	COraSQLDoc();
	DECLARE_DYNCREATE(COraSQLDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COraSQLDoc)
	public:
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COraSQLDoc();
#ifdef _DEBUG
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COraSQLDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORASQLDOC_H__4532B17F_5500_4B20_B4FB_8F30EAA0A1E9__INCLUDED_)
