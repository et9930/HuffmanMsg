
// CStringTestDlg.h : ͷ�ļ�
//

#pragma once


// CCStringTestDlg �Ի���
class CCStringTestDlg : public CDialogEx
{
// ����
public:
	CCStringTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSTRINGTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
