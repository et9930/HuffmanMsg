#pragma once


// HuffmanReceiveDlg 对话框

class HuffmanReceiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HuffmanReceiveDlg)

public:
	HuffmanReceiveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HuffmanReceiveDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECEIVEMSG_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedCopyPidBtn();
};
