#pragma once

class CPropertyBase : public CWnd
{
	CWnd *m_pWnd;

// Construction
public:
	CPropertyBase();

// Attributes
public:

// Operations
public:
	VOID SetChildCtrl( CWnd *pWnd );


// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CPropertyBase();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
