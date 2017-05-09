// MFCPropertyDialogWindow.cpp : implementation file
//

#include "stdafx.h"
#include "MFCPropertyDialog.h"
#include "MFCPropertyDialogWindow.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCPropertyDialog dialog

CMFCPropertyDialog::CMFCPropertyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCPropertyDialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCPropertyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCPROPERTYGRID, m_wndPropList);
}

BEGIN_MESSAGE_MAP(CMFCPropertyDialog, CDialogEx)
END_MESSAGE_MAP()

// CMFCPropertyDialog message handlers

BOOL CMFCPropertyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
#if 1
	// create base window
	m_propBase.CreateEx(WS_EX_CONTROLPARENT, NULL, NULL, AFX_WS_DEFAULT_VIEW, 
			CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL);

	// adjust window size to the same as m_wndPropList.
	CWnd *pPlaceHolder = GetDlgItem( IDC_MFCPROPERTYGRID );
	CRect rc;
	pPlaceHolder->GetWindowRect(&rc);
	GetDesktopWindow()->MapWindowPoints(this,&rc);
	m_propBase.SetWindowPos(NULL,rc.left,rc.top,rc.Width(),rc.Height(),0);

	// move window position
	m_propBase.SetChildCtrl( &m_wndPropList );

	InitPropList();
#else
	// Why does the problem occur if CMFCPropertyGridCtrl is a child window of the dialog?
	// For some reason, the below of the m_wndPropList is drawn black line or rectangle.
	InitPropList();

	// Give a chance for recalc left column width.
	CRect rc;
	m_wndPropList.GetClientRect(&rc);
	m_wndPropList.SendMessage(WM_SIZE,0,MAKELPARAM(rc.Width(),rc.Height()));
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCPropertyDialog::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
}

void CMFCPropertyDialog::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea(FALSE);
	m_wndPropList.SetDescriptionRows(1);
	m_wndPropList.SetVSDotNetLook(TRUE);
	m_wndPropList.MarkModifiedProperties(TRUE);

	//m_wndPropList.SetCustomColors(RGB(228, 243, 254), RGB(46, 70, 165), RGB(200, 236, 209), RGB(33, 102, 49), RGB(255, 229, 216), RGB(128, 0, 0), RGB(159, 159, 255));

	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("My Property"));
	CMFCPropertyGridProperty* pProp;
	int i;
	WCHAR szPropText[MAX_PATH];
	WCHAR szPropTitle[MAX_PATH];
	for(i = 0; i < 17; i++)
	{
		StringCchPrintf(szPropText,MAX_PATH,L"%d",2001+i);
		StringCchPrintf(szPropTitle,MAX_PATH,L"Item%d",i+1);
		pProp = new CMFCPropertyGridProperty( szPropTitle, (_variant_t) szPropText, L"");
		pGroup->AddSubItem(pProp);
	}

	m_wndPropList.AddProperty(pGroup);

#if 1 // from Visual Studio Wizard Generated code
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Window Size"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("Height"), (_variant_t) 250l, _T("Specifies the window's height"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Width"), (_variant_t) 150l, _T("Specifies the window's width"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Font"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	_tcscpy_s(lf.lfFaceName,_countof(lf.lfFaceName), _T("Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the window")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Use System Font"), (_variant_t) true, _T("Specifies that the window uses MS Shell Dlg font")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("Misc"));
	pProp = new CMFCPropertyGridProperty(_T("(Name)"), _T("Application"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("Window Color"), RGB(210, 192, 254), NULL, _T("Specifies the default window color"));
	pColorProp->EnableOtherButton(_T("Other..."));
	pColorProp->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("Icon Files(*.ico)|*.ico|All Files(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Icon"), TRUE, _T("my icon.ico"), _T("ico"), 0, szFilter, _T("Specifies the window icon")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Folder"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("Hierarchy"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("First sub-level"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("Second sub-level"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 1"), (_variant_t) _T("Value 1"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 2"), (_variant_t) _T("Value 2"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 3"), (_variant_t) _T("Value 3"), _T("This is a description")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);
#endif

}
