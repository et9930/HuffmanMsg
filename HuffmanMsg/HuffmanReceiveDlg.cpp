// HuffmanReceiveDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HuffmanMsg.h"
#include "HuffmanReceiveDlg.h"
#include "afxdialogex.h"


// HuffmanReceiveDlg �Ի���

IMPLEMENT_DYNAMIC(HuffmanReceiveDlg, CDialogEx)

HuffmanReceiveDlg::HuffmanReceiveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RECEIVEMSG_DLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

HuffmanReceiveDlg::~HuffmanReceiveDlg()
{
}

void HuffmanReceiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(HuffmanReceiveDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COPY_PID_BTN, &HuffmanReceiveDlg::OnBnClickedCopyPidBtn)
END_MESSAGE_MAP()


// HuffmanReceiveDlg ��Ϣ�������

BOOL HuffmanReceiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	LPCTSTR Title = L"Huffman Receive Message Dialog";
	CWnd *pWnd = FindWindow(NULL, Title);
	hWndReceiveDlg = pWnd->GetSafeHwnd();
	DWORD PID = 0;
	GetWindowThreadProcessId(hWndReceiveDlg, &PID);
	CString strPID;
	strPID.Format(L"%u", PID);
	GetDlgItem(IDC_RECEIVE_SELF_PID_STATIC)->SetWindowText(strPID);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


//  �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void HuffmanReceiveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR HuffmanReceiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT HuffmanReceiveDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û��� 
	switch (message)
	{
		//�����ϵͳ��Ϣ  
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}





void HuffmanReceiveDlg::OnBnClickedCopyPidBtn()
{
	if (!OpenClipboard())
	{
		AfxMessageBox(L"Cannot open the Clipboard!");
		return;
	}
	
	// ��������������գ��ͷ�������Դ��Ȼ��ָ����ǰ�򿪼�����Ĵ���Ϊ�������������
	if (!EmptyClipboard())
	{
		AfxMessageBox(L"Cannot empty the Clipboard!");
		return;
	}

	// ȡ�ص�ǰ�ؼ������ݣ�hData����ȫ���ڴ����򣬴������
	CStringW str;
	this->GetDlgItemText(IDC_RECEIVE_SELF_PID_STATIC, str);
	size_t cbStr = (str.GetLength() + 1) * sizeof(TCHAR);
	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, cbStr);
	memcpy_s(GlobalLock(hData), cbStr, str.LockBuffer(), cbStr);
	GlobalUnlock(hData);
	str.UnlockBuffer();

	// ѡ����ʵĸ�ʽ
	UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;

	if (::SetClipboardData(uiFormat, hData) == NULL)
	{
		AfxMessageBox(L"Unable to set Clipboard data");
		CloseClipboard();
		return;
	}

	CloseClipboard();
}
