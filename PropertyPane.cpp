#include "stdafx.h"
#include "MFCPropertyDialog.h"
#include "PropertyBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPropertyBase::CPropertyBase()
{
	m_pWnd = NULL;
}

CPropertyBase::~CPropertyBase()
{
}

BEGIN_MESSAGE_MAP(CPropertyBase, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CPropertyBase::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

int CPropertyBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CPropertyBase::OnPaint() 
{
	CPaintDC dc(this);
}

void CPropertyBase::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if( m_pWnd )
	{
		m_pWnd->SetWindowPos(NULL,0,0,cx,cy,SWP_NOZORDER);
	}
}

void CPropertyBase::SetChildCtrl( CWnd *pWnd )
{
	pWnd->SetParent(this);

	// To give a chance of adjust for window size by size reset.
	CRect rc;
	GetClientRect(&rc);
	pWnd->SetWindowPos(NULL,0,0,0,0,0);
	m_pWnd = pWnd;

	pWnd->SetWindowPos(NULL,0,0,rc.Width(),rc.Height(),0);
}
