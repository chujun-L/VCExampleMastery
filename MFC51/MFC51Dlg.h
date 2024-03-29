﻿
// MFC51Dlg.h: 头文件
//

#pragma once

UINT Button1Thread(LPVOID pParam);
UINT Button2Thread(LPVOID pParam);

// CMFC51Dlg 对话框
class CMFC51Dlg : public CDialogEx
{
// 构造
public:
	CMFC51Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CMFC51Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC51_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
