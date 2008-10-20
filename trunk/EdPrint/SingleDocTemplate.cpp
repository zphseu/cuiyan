// SingleDocTemplate.cpp: implementation of the CSingleDocTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _AFXDLL

#ifdef AFX_CORE2_SEG
#pragma code_seg(AFX_CORE2_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

//IMPLEMENT_DYNAMIC(CDocTemplate, CCmdTarget)
//IMPLEMENT_DYNAMIC(CSingleDocTemplate, CDocTemplate)

#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)
BOOL AFXAPI AfxComparePath(LPCTSTR lpszPath1, LPCTSTR lpszPath2);
/////////////////////////////////////////////////////////////////////////////
// CDocTemplate construction/destruction

BOOL CDocManager::bStaticInit = TRUE;
CDocManager* CDocManager::pStaticDocManager = NULL;
CPtrList* CDocManager::pStaticList = NULL;

CDocTemplate::CDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
	CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
{
	ASSERT_VALID_IDR(nIDResource);
	ASSERT(pDocClass == NULL ||
		pDocClass->IsDerivedFrom(RUNTIME_CLASS(CDocument)));
	ASSERT(pFrameClass == NULL ||
		pFrameClass->IsDerivedFrom(RUNTIME_CLASS(CFrameWnd)));
	ASSERT(pViewClass == NULL ||
		pViewClass->IsDerivedFrom(RUNTIME_CLASS(CView)));

	m_nIDResource = nIDResource;
	m_nIDServerResource = NULL;
	m_nIDEmbeddingResource = NULL;
	m_nIDContainerResource = NULL;

	m_pDocClass = pDocClass;
	m_pFrameClass = pFrameClass;
	m_pViewClass = pViewClass;
	m_pOleFrameClass = NULL;
	m_pOleViewClass = NULL;

	m_pAttachedFactory = NULL;
	m_hMenuInPlace = NULL;
	m_hAccelInPlace = NULL;
	m_hMenuEmbedding = NULL;
	m_hAccelEmbedding = NULL;
	m_hMenuInPlaceServer = NULL;
	m_hAccelInPlaceServer = NULL;

	// add to pStaticList if constructed as static instead of on heap
	if (CDocManager::bStaticInit)
	{
		m_bAutoDelete = FALSE;
		if (CDocManager::pStaticList == NULL)
			CDocManager::pStaticList = new CPtrList;
		if (CDocManager::pStaticDocManager == NULL)
			CDocManager::pStaticDocManager = new CDocManager;
		CDocManager::pStaticList->AddTail(this);
	}
	else
	{
		m_bAutoDelete = TRUE;   // usually allocated on the heap
		LoadTemplate();
	}
}

void CDocTemplate::LoadTemplate()
{
	if (m_strDocStrings.IsEmpty() && !m_strDocStrings.LoadString(m_nIDResource))
	{
		TRACE1("Warning: no document names in string for template #%d.\n",
			m_nIDResource);
	}

	if (m_nIDEmbeddingResource != 0 && m_hMenuEmbedding == NULL)
	{
		// load menu to be used while editing an embedding (as a server)
		HINSTANCE hInst = AfxFindResourceHandle(
			MAKEINTRESOURCE(m_nIDEmbeddingResource), RT_MENU);
		m_hMenuEmbedding =
			::LoadMenu(hInst, MAKEINTRESOURCE(m_nIDEmbeddingResource));
		m_hAccelEmbedding =
			::LoadAccelerators(hInst, MAKEINTRESOURCE(m_nIDEmbeddingResource));
	}
	if (m_nIDServerResource != 0 && m_hMenuInPlaceServer == NULL)
	{
		// load menu to be used while editing in-place (as a server)
		HINSTANCE hInst = AfxFindResourceHandle(
			MAKEINTRESOURCE(m_nIDServerResource), RT_MENU);
		m_hMenuInPlaceServer = ::LoadMenu(hInst,
			MAKEINTRESOURCE(m_nIDServerResource));
		m_hAccelInPlaceServer = ::LoadAccelerators(hInst,
			MAKEINTRESOURCE(m_nIDServerResource));
	}

	if (m_nIDContainerResource != 0 && m_hMenuInPlace == NULL)
	{
		// load menu to be used while in-place editing session (as a container)
		HINSTANCE hInst = AfxFindResourceHandle(
			MAKEINTRESOURCE(m_nIDContainerResource), RT_MENU);
		m_hMenuInPlace = ::LoadMenu(hInst,
			MAKEINTRESOURCE(m_nIDContainerResource));
		m_hAccelInPlace = ::LoadAccelerators(hInst,
			MAKEINTRESOURCE(m_nIDContainerResource));
	}
}

void CDocTemplate::SetServerInfo(UINT nIDOleEmbedding, UINT nIDOleInPlaceServer,
	CRuntimeClass* pOleFrameClass, CRuntimeClass* pOleViewClass)
{
	ASSERT_VALID_IDR(nIDOleEmbedding);
	if (nIDOleInPlaceServer != 0)
		ASSERT_VALID_IDR(nIDOleInPlaceServer);
	ASSERT(pOleFrameClass == NULL ||
		pOleFrameClass->IsDerivedFrom(RUNTIME_CLASS(CFrameWnd)));
	ASSERT(pOleViewClass == NULL ||
		pOleViewClass->IsDerivedFrom(RUNTIME_CLASS(CView)));

	m_pOleFrameClass = pOleFrameClass;
	m_pOleViewClass = pOleViewClass;

	m_nIDEmbeddingResource = nIDOleEmbedding;
	m_nIDServerResource = nIDOleInPlaceServer;
	if (!CDocManager::bStaticInit)
		LoadTemplate();
}

void CDocTemplate::SetContainerInfo(UINT nIDOleInPlaceContainer)
{
	ASSERT(nIDOleInPlaceContainer != 0);

	m_nIDContainerResource = nIDOleInPlaceContainer;
	if (!CDocManager::bStaticInit)
		LoadTemplate();
}

CDocTemplate::~CDocTemplate()
{
	// delete OLE resources
	if (m_hMenuInPlace != NULL)
		::DestroyMenu(m_hMenuInPlace);
	if (m_hAccelInPlace != NULL)
		::FreeResource(m_hAccelInPlace);
	if (m_hMenuEmbedding != NULL)
		::DestroyMenu(m_hMenuEmbedding);
	if (m_hAccelEmbedding != NULL)
		::FreeResource(m_hAccelEmbedding);
	if (m_hMenuInPlaceServer != NULL)
		::DestroyMenu(m_hMenuInPlaceServer);
	if (m_hAccelInPlaceServer != NULL)
		::FreeResource(m_hAccelInPlaceServer);
}

/////////////////////////////////////////////////////////////////////////////
// CDocTemplate attributes

BOOL CDocTemplate::GetDocString(CString& rString, enum DocStringIndex i) const
{
	return AfxExtractSubString(rString, m_strDocStrings, (int)i);
}

/////////////////////////////////////////////////////////////////////////////
// Document management

void CDocTemplate::AddDocument(CDocument* pDoc)
{
	ASSERT_VALID(pDoc);
	ASSERT(pDoc->m_pDocTemplate == NULL);   // no template attached yet
	pDoc->m_pDocTemplate = this;
}

void CDocTemplate::RemoveDocument(CDocument* pDoc)
{
	ASSERT_VALID(pDoc);
	ASSERT(pDoc->m_pDocTemplate == this);   // must be attached to us
	pDoc->m_pDocTemplate = NULL;
}

CDocTemplate::Confidence CDocTemplate::MatchDocType(LPCTSTR lpszPathName,
	CDocument*& rpDocMatch)
{
	ASSERT(lpszPathName != NULL);
	rpDocMatch = NULL;

	// go through all documents
	POSITION pos = GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = GetNextDoc(pos);
		if (AfxComparePath(pDoc->GetPathName(), lpszPathName))
		{
			// already open
			rpDocMatch = pDoc;
			return yesAlreadyOpen;
		}
	}

	// see if it matches our default suffix
	CString strFilterExt;
	if (GetDocString(strFilterExt, CDocTemplate::filterExt) &&
	  !strFilterExt.IsEmpty())
	{
		// see if extension matches
		ASSERT(strFilterExt[0] == '.');
		LPCTSTR lpszDot = _tcsrchr(lpszPathName, '.');
		if (lpszDot != NULL && lstrcmpi(lpszDot, strFilterExt) == 0)
			return yesAttemptNative; // extension matches, looks like ours
	}

	// otherwise we will guess it may work
	return yesAttemptForeign;
}

CDocument* CDocTemplate::CreateNewDocument()
{
	// default implementation constructs one from CRuntimeClass
	if (m_pDocClass == NULL)
	{
		TRACE0("Error: you must override CDocTemplate::CreateNewDocument.\n");
		ASSERT(FALSE);
		return NULL;
	}
	CDocument* pDocument = (CDocument*)m_pDocClass->CreateObject();
	if (pDocument == NULL)
	{
		TRACE1("Warning: Dynamic create of document type %hs failed.\n",
			m_pDocClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CDocument, pDocument);
	AddDocument(pDocument);
	return pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// Default frame creation

CFrameWnd* CDocTemplate::CreateNewFrame(CDocument* pDoc, CFrameWnd* pOther)
{
	if (pDoc != NULL)
		ASSERT_VALID(pDoc);
	// create a frame wired to the specified document

	ASSERT(m_nIDResource != 0); // must have a resource ID to load from
	CCreateContext context;
	context.m_pCurrentFrame = pOther;
	context.m_pCurrentDoc = pDoc;
	context.m_pNewViewClass = m_pViewClass;
	context.m_pNewDocTemplate = this;

	if (m_pFrameClass == NULL)
	{
		TRACE0("Error: you must override CDocTemplate::CreateNewFrame.\n");
		ASSERT(FALSE);
		return NULL;
	}
	CFrameWnd* pFrame = (CFrameWnd*)m_pFrameClass->CreateObject();
	if (pFrame == NULL)
	{
		TRACE1("Warning: Dynamic create of frame %hs failed.\n",
			m_pFrameClass->m_lpszClassName);
		return NULL;
	}
	ASSERT_KINDOF(CFrameWnd, pFrame);

	if (context.m_pNewViewClass == NULL)
		TRACE0("Warning: creating frame with no default view.\n");

	// create new from resource
	if (!pFrame->LoadFrame(m_nIDResource,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,   // default frame styles
			NULL, &context))
	{
		TRACE0("Warning: CDocTemplate couldn't create a frame.\n");
		// frame will be deleted in PostNcDestroy cleanup
		return NULL;
	}

	// it worked !
	return pFrame;
}

CFrameWnd* CDocTemplate::CreateOleFrame(CWnd* pParentWnd, CDocument* pDoc,
	BOOL bCreateView)
{
	CCreateContext context;
	context.m_pCurrentFrame = NULL;
	context.m_pCurrentDoc = pDoc;
	context.m_pNewViewClass = bCreateView ? m_pOleViewClass : NULL;
	context.m_pNewDocTemplate = this;

	if (m_pOleFrameClass == NULL)
	{
		TRACE0("Warning: pOleFrameClass not specified for doc template.\n");
		return NULL;
	}

	ASSERT(m_nIDServerResource != 0); // must have a resource ID to load from
	CFrameWnd* pFrame = (CFrameWnd*)m_pOleFrameClass->CreateObject();
	if (pFrame == NULL)
	{
		TRACE1("Warning: Dynamic create of frame %hs failed.\n",
			m_pOleFrameClass->m_lpszClassName);
		return NULL;
	}

	// create new from resource (OLE frames are created as child windows)
	if (!pFrame->LoadFrame(m_nIDServerResource,
		WS_CHILD|WS_CLIPSIBLINGS, pParentWnd, &context))
	{
		TRACE0("Warning: CDocTemplate couldn't create an OLE frame.\n");
		// frame will be deleted in PostNcDestroy cleanup
		return NULL;
	}

	// it worked !
	return pFrame;
}

void CDocTemplate::InitialUpdateFrame(CFrameWnd* pFrame, CDocument* pDoc,
	BOOL bMakeVisible)
{
	// just delagate to implementation in CFrameWnd
	pFrame->InitialUpdateFrame(pDoc, bMakeVisible);
}

/////////////////////////////////////////////////////////////////////////////
// CDocTemplate commands and command helpers

BOOL CDocTemplate::SaveAllModified()
{
	POSITION pos = GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = GetNextDoc(pos);
		if (!pDoc->SaveModified())
			return FALSE;
	}
	return TRUE;
}


void CDocTemplate::CloseAllDocuments(BOOL)
{
	POSITION pos = GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = GetNextDoc(pos);
		pDoc->OnCloseDocument();
	}
}

void CDocTemplate::OnIdle()
{
	POSITION pos = GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = GetNextDoc(pos);
		ASSERT_VALID(pDoc);
		ASSERT_KINDOF(CDocument, pDoc);
		pDoc->OnIdle();
	}
}

BOOL CDocTemplate::OnCmdMsg(UINT nID, int nCode, void* pExtra,
	AFX_CMDHANDLERINFO* pHandlerInfo)
{
	BOOL bReturn;
	CCmdTarget* pFactory = DYNAMIC_DOWNCAST(CCmdTarget, m_pAttachedFactory);

	if (nCode == CN_OLE_UNREGISTER && pFactory != NULL)
		bReturn = pFactory->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	else
		bReturn = CCmdTarget::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);

	return bReturn;
}

/////////////////////////////////////////////////////////////////////////////
// CDocTemplate diagnostics

#ifdef _DEBUG
void CDocTemplate::Dump(CDumpContext& dc) const
{
	CCmdTarget::Dump(dc);

	dc << "m_nIDResource = " << m_nIDResource;
	dc << "\nm_strDocStrings: " << m_strDocStrings;

	if (m_pDocClass)
		dc << "\nm_pDocClass = " << m_pDocClass->m_lpszClassName;
	else
		dc << "\nm_pDocClass = NULL";

	if (dc.GetDepth() > 0)
	{
		dc << "\ndocument list = {";
		POSITION pos = GetFirstDocPosition();
		while (pos != NULL)
		{
			CDocument* pDoc = GetNextDoc(pos);
			dc << "\ndocument " << pDoc;
		}
		dc << "\n}";
	}

	dc << "\n";
}

void CDocTemplate::AssertValid() const
{
	CCmdTarget::AssertValid();

	POSITION pos = GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = GetNextDoc(pos);
		ASSERT_VALID(pDoc);
	}
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CSingleDocTemplate construction/destruction

CSingleDocTemplate::CSingleDocTemplate(UINT nIDResource,
	CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass,
	CRuntimeClass* pViewClass)
		: CDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
	m_pOnlyDoc = NULL;
}

CSingleDocTemplate::~CSingleDocTemplate()
{
#ifdef _DEBUG
	if (m_pOnlyDoc != NULL)
		TRACE0("Warning: destroying CSingleDocTemplate with live document.\n");
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDocTemplate attributes

POSITION CSingleDocTemplate::GetFirstDocPosition() const
{
	return (m_pOnlyDoc == NULL) ? NULL : BEFORE_START_POSITION;
}

CDocument* CSingleDocTemplate::GetNextDoc(POSITION& rPos) const
{
	CDocument* pDoc = NULL;
	if (rPos == BEFORE_START_POSITION)
	{
		// first time through, return a real document
		ASSERT(m_pOnlyDoc != NULL);
		pDoc = m_pOnlyDoc;
	}
	rPos = NULL;        // no more
	return pDoc;
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDocTemplate document management (a list of currently open documents)

void CSingleDocTemplate::AddDocument(CDocument* pDoc)
{
	ASSERT(m_pOnlyDoc == NULL);     // one at a time please
	ASSERT_VALID(pDoc);

	CDocTemplate::AddDocument(pDoc);
	m_pOnlyDoc = pDoc;
}

void CSingleDocTemplate::RemoveDocument(CDocument* pDoc)
{
	ASSERT(m_pOnlyDoc == pDoc);     // must be this one
	ASSERT_VALID(pDoc);

	CDocTemplate::RemoveDocument(pDoc);
	m_pOnlyDoc = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDocTemplate commands

CDocument* CSingleDocTemplate::OpenDocumentFile(LPCTSTR lpszPathName,
	BOOL bMakeVisible)
	// if lpszPathName == NULL => create new file of this type
{
	CDocument* pDocument = NULL;
	CFrameWnd* pFrame = NULL;
	BOOL bCreated = FALSE;      // => doc and frame created
	BOOL bWasModified = FALSE;

	if (m_pOnlyDoc != NULL)
	{
		// already have a document - reinit it
		pDocument = m_pOnlyDoc;
		if (!pDocument->SaveModified())
			return NULL;        // leave the original one

		pFrame = (CFrameWnd*)AfxGetMainWnd();
		ASSERT(pFrame != NULL);
		ASSERT_KINDOF(CFrameWnd, pFrame);
		ASSERT_VALID(pFrame);
	}
	else
	{
		// create a new document
		pDocument = CreateNewDocument();
		ASSERT(pFrame == NULL);     // will be created below
		bCreated = TRUE;
	}

	if (pDocument == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	ASSERT(pDocument == m_pOnlyDoc);

	if (pFrame == NULL)
	{
		ASSERT(bCreated);

		// create frame - set as main document frame
		BOOL bAutoDelete = pDocument->m_bAutoDelete;
		pDocument->m_bAutoDelete = FALSE;
					// don't destroy if something goes wrong
		pFrame = CreateNewFrame(pDocument, NULL);
		pDocument->m_bAutoDelete = bAutoDelete;
		if (pFrame == NULL)
		{
			AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
			delete pDocument;       // explicit delete on error
			return NULL;
		}
	}

	if (lpszPathName == NULL)
	{
		// create a new document
		SetDefaultTitle(pDocument);

		// avoid creating temporary compound file when starting up invisible
		if (!bMakeVisible)
			pDocument->m_bEmbedded = TRUE;

		if (!pDocument->OnNewDocument())
		{
			// user has been alerted to what failed in OnNewDocument
			TRACE0("CDocument::OnNewDocument returned FALSE.\n");
			if (bCreated)
				pFrame->DestroyWindow();    // will destroy document
			return NULL;
		}
	}
	else
	{
		CWaitCursor wait;

		// open an existing document
		bWasModified = pDocument->IsModified();
		pDocument->SetModifiedFlag(FALSE);  // not dirty for open

		if (!pDocument->OnOpenDocument(lpszPathName))
		{
			// user has been alerted to what failed in OnOpenDocument
			TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
			if (bCreated)
			{
				pFrame->DestroyWindow();    // will destroy document
			}
			else if (!pDocument->IsModified())
			{
				// original document is untouched
				pDocument->SetModifiedFlag(bWasModified);
			}
			else
			{
				// we corrupted the original document
				SetDefaultTitle(pDocument);

				if (!pDocument->OnNewDocument())
				{
					TRACE0("Error: OnNewDocument failed after trying to open a document - trying to continue.\n");
					// assume we can continue
				}
			}
			return NULL;        // open failed
		}
		pDocument->SetPathName(lpszPathName);
	}

	CWinThread* pThread = AfxGetThread();
	if (bCreated && pThread->m_pMainWnd == NULL)
	{
		// set as main frame (InitialUpdateFrame will show the window)
		pThread->m_pMainWnd = pFrame;
	}
	InitialUpdateFrame(pFrame, pDocument, bMakeVisible);

	return pDocument;
}

void CSingleDocTemplate::SetDefaultTitle(CDocument* pDocument)
{
	CString strDocName;
	if (!GetDocString(strDocName, CDocTemplate::docName) ||
		strDocName.IsEmpty())
	{
		// use generic 'untitled'
		VERIFY(strDocName.LoadString(AFX_IDS_UNTITLED));
	}
	pDocument->SetTitle(strDocName);
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDocTemplate diagnostics

#ifdef _DEBUG
void CSingleDocTemplate::Dump(CDumpContext& dc) const
{
	CDocTemplate::Dump(dc);

	if (m_pOnlyDoc)
		dc << "with document: " << (void*)m_pOnlyDoc;
	else
		dc << "with no document";

	dc << "\n";
}

void CSingleDocTemplate::AssertValid() const
{
	CDocTemplate::AssertValid();
	if (m_pOnlyDoc)
		ASSERT_VALID(m_pOnlyDoc);
}
#endif //_DEBUG

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

#endif //_AFXDLL

/////////////////////////////////////////////////////////////////////////////

