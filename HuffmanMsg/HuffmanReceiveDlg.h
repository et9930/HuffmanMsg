#pragma once


// HuffmanReceiveDlg �Ի���

class HuffmanReceiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HuffmanReceiveDlg)

public:
	HuffmanReceiveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HuffmanReceiveDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECEIVEMSG_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedCopyPidBtn();
};
