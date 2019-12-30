﻿
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "RedBlack.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_ADD_NODE, &CMainFrame::OnAddNode)
	ON_COMMAND(ID_DELETE_NODE, &CMainFrame::OnDeleteNode)
	ON_COMMAND(ID_DELETE_TREE, &CMainFrame::OnDeleteTree)
	ON_EN_UPDATE(IDC_EDIT_NVALUE, &CMainFrame::OnEnUpdateEditNvalue)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	m_bModeFlag = true;
	m_bSkipAnimation = true;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	
	
	int index = m_wndToolBar.CommandToIndex(ID_SKIP_ANIMATE);
	CRect rect;
	m_wndToolBar.GetItemRect(index, &rect);
	rect.top += 2;
	rect.bottom -= 2;
	rect.right += 100;
	m_wndToolBar.m_wndCheckBox.Create(L"Skip Animation", BS_CHECKBOX | WS_CHILD | WS_VISIBLE, rect, &m_wndToolBar, ID_SKIP_ANIMATE);
	m_wndToolBar.m_wndCheckBox.ShowWindow(SW_SHOW);
	

	if (!m_wndDialogBar.Create(this, IDD_DIALOGBAR, CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE, IDD_DIALOGBAR))
	{
		TRACE0("Dialog Create Error");
		return -1;
	}

	CFont font;
	font.CreateFontW(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("Times New Roman"));
	m_wndDialogBar.GetDlgItem(IDC_MODE_CAPTION)->SetFont(&font);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
		 | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnAddNode()
{
	m_wndDialogBar.GetDlgItem(IDC_MODE_CAPTION)->SetWindowTextW(L"Insert Node");
	m_wndDialogBar.GetDlgItem(IDC_BTN_ADEL)->SetWindowTextW(L"Insert");
	m_bModeFlag = true;
}

void CMainFrame::OnDeleteNode()
{
	m_wndDialogBar.GetDlgItem(IDC_MODE_CAPTION)->SetWindowTextW(L"Delete Node");
	m_wndDialogBar.GetDlgItem(IDC_BTN_ADEL)->SetWindowTextW(L"Delete");
	m_bModeFlag = false;
}

void CMainFrame::OnDeleteTree()
{
	if (MessageBox(L"현재 트리를 삭제합니까?", L"RBTree", MB_OKCANCEL) == IDOK)
	{
		MessageBox(L"삭제");
	}
	else
	{
		MessageBox(L"유지");
	}
}


void CMainFrame::OnEnUpdateEditNvalue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFrameWnd::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	static CString lastStr = L"";

	CEdit *editText = (CEdit*)m_wndDialogBar.GetDlgItem(IDC_EDIT_NVALUE);
	editText->GetWindowTextW(str);

	if (!str.GetLength())
		return;

	int start, end;
	editText->GetSel(start, end);

	if (end && (str.GetAt(end-1) < L'0' || str.GetAt(end-1) > L'9'))
	{
		
		editText->SetWindowTextW(lastStr);
		editText->SetSel(start - 1, end - 1, true);
	}
	else
		lastStr = str;
}