#pragma once


// HuffmanChooseDlg 对话框

class HuffmanChooseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HuffmanChooseDlg)

public:
	HuffmanChooseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HuffmanChooseDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUFFMAN_CHOOSE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenSendDlgBtn();
	afx_msg void OnBnClickedOpenReceiveDlgBtn();
	afx_msg void OnBnClickedQuitBtn();
};
