﻿
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

class CMainToolBar : public CToolBar
{
public:
	CButton		m_wndCheckBox;
};


class CMainFrame : public CFrameWnd
{
private:
	BOOL		m_bModeFlag;

protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	CString lastStr = L"";	// digit & , Only CString value
// 작업입니다.
public:
	CMainToolBar* GetToolBarPtr() { return &m_wndToolBar; }
	bool IsModeInsert() { return m_bModeFlag; }
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CMainToolBar      m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CDialogBar		  m_wndDialogBar;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAddNode();
	afx_msg void OnDeleteNode();
	afx_msg void OnDeleteTree();
	afx_msg void OnResultOnly();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnUpdateEditNvalue();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


