#pragma once


// HuffmanChooseDlg �Ի���

class HuffmanChooseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HuffmanChooseDlg)

public:
	HuffmanChooseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HuffmanChooseDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUFFMAN_CHOOSE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenSendDlgBtn();
	afx_msg void OnBnClickedOpenReceiveDlgBtn();
	afx_msg void OnBnClickedQuitBtn();
};
