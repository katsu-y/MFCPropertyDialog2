
// MFCPropertyDialogWindow.h : header file
//

#pragma once

#include "PropertyBase.h"

// CMFCPropertyDialog dialog
class CMFCPropertyDialog : public CDialogEx
{
// Construction
public:
	CMFCPropertyDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCPROPERTYDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CPropertyBase m_propBase;

	CMFCPropertyGridCtrl m_wndPropList;
	void InitPropList();
	void SetPropListFont();
	CFont m_fntPropList;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
