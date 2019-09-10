﻿
// MFC42Dlg.h: 头文件
//

#pragma once


// CMFC42Dlg 对话框
class CMFC42Dlg : public CDialogEx
{
// 构造
public:
	CMFC42Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC42_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	BOOL LoadFile(CString strFileName);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//CString m_strText;
	CString m_strText;
};
