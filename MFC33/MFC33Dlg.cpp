﻿
// MFC33Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC33.h"
#include "MFC33Dlg.h"
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


// CMFC33Dlg 对话框



CMFC33Dlg::CMFC33Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC33_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC33Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC33Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CMFC33Dlg::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN, &CMFC33Dlg::OnBnClickedButtonShutdown)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CMFC33Dlg::OnBnClickedButtonReboot)
END_MESSAGE_MAP()


// CMFC33Dlg 消息处理程序

BOOL CMFC33Dlg::OnInitDialog()
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

void CMFC33Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC33Dlg::OnPaint()
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
HCURSOR CMFC33Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC33Dlg::OnBnClickedButtonLogout()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// 注销
	if (IDNO == MessageBox(TEXT("确定注销吗？"),
				TEXT("Logout"), MB_YESNO)) {
		return;
	}

	// 获取进程令牌
	if (!OpenProcessToken(GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			&hToken)) {
		AfxMessageBox(TEXT("OpenProcessToken failed"));
		return;
	}

	// 提升权限
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) {
		AfxMessageBox(TEXT("AdjustTokenPrivileges failed"));
		return;
	}

	//AfxMessageBox(TEXT("注销-提权成功"));
	ExitWindowsEx(EWX_LOGOFF, 0);
}


void CMFC33Dlg::OnBnClickedButtonShutdown()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// 注销
	if (IDNO == MessageBox(TEXT("确定关机吗？"),
		TEXT("Shutdown"), MB_YESNO)) {
		return;
	}

	// 获取进程令牌
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken)) {
		AfxMessageBox(TEXT("OpenProcessToken failed"));
		return;
	}

	// 提升权限
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) {
		AfxMessageBox(TEXT("AdjustTokenPrivileges failed"));
		return;
	}

	//AfxMessageBox(TEXT("关机-提权成功"));
	ExitWindowsEx(EWX_SHUTDOWN, 0);
}


void CMFC33Dlg::OnBnClickedButtonReboot()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// 注销
	if (IDNO == MessageBox(TEXT("确定重启吗？"),
		TEXT("Reboot"), MB_YESNO)) {
		return;
	}

	// 获取进程令牌
	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken)) {
		AfxMessageBox(TEXT("OpenProcessToken failed"));
		return;
	}

	// 提升权限
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS) {
		AfxMessageBox(TEXT("AdjustTokenPrivileges failed"));
		return;
	}

	//AfxMessageBox(TEXT("重启-提权成功"));
	ExitWindowsEx(EWX_REBOOT, 0);
}
