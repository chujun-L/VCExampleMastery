﻿
// MFC41.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFC41.h"
#include "MFC41Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC41App

BEGIN_MESSAGE_MAP(CMFC41App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFC41App 构造

CMFC41App::CMFC41App()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFC41App 对象

CMFC41App theApp;


// CMFC41App 初始化

BOOL CMFC41App::InitInstance()
{
	m_hMutex = ::CreateMutex(NULL,FALSE, TEXT("DemoApp"));
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		//AfxMessageBox(TEXT("已经有一个实例在运行"));

		// 获取桌面所有的窗口
		CWnd *pDesktopWnd = CWnd::GetDesktopWindow();
		
		// 获取桌面的第一个窗口
		CWnd *pWnd = pDesktopWnd->GetWindow(GW_CHILD);

		// 循环获取桌面的窗口
		while (pWnd) {
			if (::GetProp(pWnd->m_hWnd, m_pszExeName)) {
				// 找到当前程序的窗口后，在前台显示
				pWnd->SetForegroundWindow();
				return TRUE;
			}

			// 继续找一下个窗口
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}

		return FALSE;
	}
	//AfxMessageBox(TEXT("实例是第一次运行"));


	CWinApp::InitInstance();


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CMFC41Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

