// HuffmanReceiveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HuffmanMsg.h"
#include "HuffmanReceiveDlg.h"
#include "afxdialogex.h"


// HuffmanReceiveDlg 对话框

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


// HuffmanReceiveDlg 消息处理程序

BOOL HuffmanReceiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	LPCTSTR Title = L"Huffman Receive Message Dialog";
	CWnd *pWnd = FindWindow(NULL, Title);
	hWndReceiveDlg = pWnd->GetSafeHwnd();
	DWORD PID = 0;
	GetWindowThreadProcessId(hWndReceiveDlg, &PID);
	CString strPID;
	strPID.Format(L"%u", PID);
	GetDlgItem(IDC_RECEIVE_SELF_PID_STATIC)->SetWindowText(strPID);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


//  如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void HuffmanReceiveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR HuffmanReceiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT HuffmanReceiveDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类 
	switch (message)
	{
		//如果是系统消息  
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
	
	// 将剪贴板内容清空，释放数据资源，然后指定当前打开剪贴板的窗口为剪贴板的所有制
	if (!EmptyClipboard())
	{
		AfxMessageBox(L"Cannot empty the Clipboard!");
		return;
	}

	// 取回当前控件的数据，hData开辟全局内存区域，存放数据
	CStringW str;
	this->GetDlgItemText(IDC_RECEIVE_SELF_PID_STATIC, str);
	size_t cbStr = (str.GetLength() + 1) * sizeof(TCHAR);
	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, cbStr);
	memcpy_s(GlobalLock(hData), cbStr, str.LockBuffer(), cbStr);
	GlobalUnlock(hData);
	str.UnlockBuffer();

	// 选择合适的格式
	UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;

	if (::SetClipboardData(uiFormat, hData) == NULL)
	{
		AfxMessageBox(L"Unable to set Clipboard data");
		CloseClipboard();
		return;
	}

	CloseClipboard();
}
