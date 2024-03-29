﻿
// MFC30Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC30.h"
#include "MFC30Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC30Dlg 对话框



CMFC30Dlg::CMFC30Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC30_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nRedID = 0;
	m_nGreenID = 0;
}

void CMFC30Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC30Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RED, &CMFC30Dlg::OnBnClickedButtonRed)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GREEN, &CMFC30Dlg::OnBnClickedButtonGreen)
END_MESSAGE_MAP()


// CMFC30Dlg 消息处理程序

BOOL CMFC30Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC30Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC30Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC30Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC30Dlg::OnBnClickedButtonRed()
{
	if (m_nRedID == 0) {
		// 设置定时器的方式：消息通知(WM_TIMER)
		m_nRedID = SetTimer(1, 500, NULL);
	} else {
		KillTimer(m_nRedID);
		m_nRedID = 0;
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_RED), SW_SHOW);
	}
}


void CMFC30Dlg::OnTimer(UINT_PTR nIDEvent)
{
	int nShow;

	if (nIDEvent == m_nRedID) {
		HWND hRed = ::GetDlgItem(m_hWnd, IDC_RED);
		if (::IsWindowVisible(hRed)) {
			nShow = SW_HIDE;
		} else {
			nShow = SW_SHOW;
		}

		::ShowWindow(hRed, nShow);
	}

	CDialogEx::OnTimer(nIDEvent);
}

VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT uID, DWORD dwTime)
{
	int nShow;

	HWND hGreen = ::GetDlgItem(hWnd, IDC_GREEN);
	if (::IsWindowVisible(hGreen)) {
		nShow = SW_HIDE;
	} else {
		nShow = SW_SHOW;
	}

	::ShowWindow(hGreen, nShow);
}

void CMFC30Dlg::OnBnClickedButtonGreen()
{
	if (m_nGreenID == 0) {
		// 设置定时器的方式：回调函数
		m_nGreenID = SetTimer(2, 1000, TimerProc);
	} else {
		KillTimer(m_nGreenID);
		m_nGreenID = 0;
		::ShowWindow(::GetDlgItem(m_hWnd, IDC_GREEN), SW_SHOW);
	}
}