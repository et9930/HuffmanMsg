#pragma once

#include "Huffman.h"
// HuffmanSendDlg �Ի���

class HuffmanSendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HuffmanSendDlg)

public:
	HuffmanSendDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HuffmanSendDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SENDMSG_DLG };
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
	afx_msg void OnEnChangeOriginalTextEditctrl();
	afx_msg void OnBnClickedEncodeBtn();
	afx_msg void OnBnClickedReadFromFileBtn();
	afx_msg void OnEnChangeObjectPidEditctrl();
	void DisplayInOriEditCtrl(CStringW FileText);
	void DisplayInEncodedEditCtrl(CString EncodedText);
	void FindTXTFile(CString Path);
	BOOL GetTextFromOriEditCtrl(CStringW *OriText);
	BOOL Encode(CStringW OriText, DWORD *EncodedText[]);
	BOOL OpenFileDlg(CString *FilePath);
	BOOL ReadFile(CString FilePath, CStringW *FileText);

	Huffman *HFM;
	FileList ReadFileList;
	afx_msg void OnBnClickedReadPathBtn();
};
