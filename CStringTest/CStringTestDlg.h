
// CStringTestDlg.h : 头文件
//

#pragma once


// CCStringTestDlg 对话框
class CCStringTestDlg : public CDialogEx
{
// 构造
public:
	CCStringTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSTRINGTEST_DIALOG };
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
	void Dec2Bin(CString *Bin, int Dec);
	void Bin2Dec(CString Bin, int *Dec);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
