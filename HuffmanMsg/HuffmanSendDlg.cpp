// HuffmanSendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HuffmanMsg.h"
#include "HuffmanSendDlg.h"
#include "afxdialogex.h"


// HuffmanSendDlg 对话框

IMPLEMENT_DYNAMIC(HuffmanSendDlg, CDialogEx)

HuffmanSendDlg::HuffmanSendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SENDMSG_DLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

HuffmanSendDlg::~HuffmanSendDlg()
{
	delete HFM;
}

void HuffmanSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(HuffmanSendDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_ORIGINAL_TEXT_EDITCTRL, &HuffmanSendDlg::OnEnChangeOriginalTextEditctrl)
	ON_BN_CLICKED(IDC_ENCODE_BTN, &HuffmanSendDlg::OnBnClickedEncodeBtn)
	ON_BN_CLICKED(IDC_READ_FROM_FILE_BTN, &HuffmanSendDlg::OnBnClickedReadFromFileBtn)
	ON_EN_CHANGE(IDC_OBJECT_PID_EDITCTRL, &HuffmanSendDlg::OnEnChangeObjectPidEditctrl)
	ON_BN_CLICKED(IDC_READ_PATH_BTN, &HuffmanSendDlg::OnBnClickedReadPathBtn)
END_MESSAGE_MAP()


// HuffmanSendDlg 消息处理程序

BOOL HuffmanSendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);

	LPCTSTR Title = L"Huffman Send Message Dialog";
	CWnd *pWnd = FindWindow(NULL, Title);
	hWndSendDlg = pWnd->GetSafeHwnd();
	DWORD PID = 0;
	GetWindowThreadProcessId(hWndSendDlg, &PID);
	CString strPID;
	strPID.Format(L"%u", PID);
	GetDlgItem(IDC_SEND_SELF_PID_STATIC)->SetWindowText(strPID);

	HFM = new Huffman();
	HFM->CreateRandomWeights();
	HFM->CreateHuffmanTree();
	HFM->CreateHuffmanCodeList();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//  如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void HuffmanSendDlg::OnPaint()
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
HCURSOR HuffmanSendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//重载关闭按钮
LRESULT HuffmanSendDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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


void HuffmanSendDlg::OnEnChangeOriginalTextEditctrl()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CWnd *EncodeBtn = GetDlgItem(IDC_ENCODE_BTN);
	CString OriginalText;
	GetDlgItemText(IDC_ORIGINAL_TEXT_EDITCTRL, OriginalText);
	if (OriginalText != "")
	{
		EncodeBtn->EnableWindow(1);
	}
	else
	{
		EncodeBtn->EnableWindow(0);
	}
}


void HuffmanSendDlg::OnBnClickedEncodeBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString OriText;
	GetDlgItemText(IDC_ORIGINAL_TEXT_EDITCTRL, OriText);

	HFM->setOriText(OriText);
	HFM->HuffmanEncode();

	CString EncodedText;
	EncodedText = HFM->getEncodedText();
	DisplayInEncodedEditCtrl(EncodedText);

	CWnd *SendMsgBtn = GetDlgItem(IDC_SEND_MSG_BTN);
	CString PIDInfo;
	GetDlgItemText(IDC_OBJECT_PID_EDITCTRL, PIDInfo);

	if (PIDInfo != "" && EncodedText != "")
	{
		SendMsgBtn->EnableWindow(1);
	}
	else
	{
		SendMsgBtn->EnableWindow(0);
	}
}


void HuffmanSendDlg::OnBnClickedReadFromFileBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePath;
	CStringW FileText;
	if (OpenFileDlg(&FilePath))
	{
		if (ReadFile(FilePath, &FileText))
		{
			ReadFileList.SentFileText.push_back(FileText);
			ReadFileList.FileCount = 1;
			DisplayInOriEditCtrl(FileText);
		}
	}
	return;	
}

void HuffmanSendDlg::DisplayInOriEditCtrl(CStringW FileText)
{
	int b = FileText.GetLength();
	CWnd *OriginalEditCtrl = GetDlgItem(IDC_ORIGINAL_TEXT_EDITCTRL);
	OriginalEditCtrl->SetWindowText(L"");
	OriginalEditCtrl->SetWindowText(FileText);
	CWnd *EncodeBtn = GetDlgItem(IDC_ENCODE_BTN);
	EncodeBtn->EnableWindow(1);
}

void HuffmanSendDlg::DisplayInEncodedEditCtrl(CString EncodedText)
{
	
	CWnd *EncodedEditCtrl = GetDlgItem(IDC_ENCODED_TEXT_EDITCTRL);
	EncodedEditCtrl->SetWindowText(L"");
	EncodedEditCtrl->SetWindowText(EncodedText);
}

void HuffmanSendDlg::FindTXTFile(CString Path)
{
	CString fdPath;   //设置路径变量  
	Path = Path + L"\\*.*"; //文件夹路径  
	CString strTmp;      //后缀名变量  

	CFileFind find;     //例化CFileFind  
	BOOL bf = find.FindFile(Path);    //  
	while (bf)
	{
		bf = find.FindNextFile();
		if (!find.IsDots())
		{
			if (find.IsDirectory())
			{
				continue;
			}
			else
			{
				//如果是文件,判断是否是*.txt  
				fdPath = find.GetFileName();
				strTmp = fdPath.Right(4);  //取后缀名  
				strTmp.MakeLower();     //字符串小写化  
				if (strTmp == ".txt")
				{
					CStringW FileText;
					ReadFile(fdPath, &FileText);
					ReadFileList.SentFileText.push_back(FileText);
					ReadFileList.FileName.push_back(fdPath);
					ReadFileList.FileCount += 1;

				}
			}
		}
	}
	find.Close();
}

BOOL HuffmanSendDlg::OpenFileDlg(CString * FilePath)
{
	// 设置过滤器   
	TCHAR szFilter[] = L"文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||";
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, L"txt", NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_FILE_PATH_STATIC, strFilePath);
	}
	else
	{
		return FALSE;
	}
	*FilePath = strFilePath;
	return TRUE;
}

BOOL HuffmanSendDlg::ReadFile(CString FilePath, CStringW * FileText)
{
	int b;
	char strFileText[MAX_TEXT_LENGTH+1] = {' '};
	CFile file(FilePath, CFile::modeRead);
	if (file)
	{
		file.SeekToBegin();
		file.Read(strFileText, MAX_TEXT_LENGTH);
		file.Close();
		FileText->Format(L"%s", CStringW(strFileText));	
		b = FileText->GetLength();
	}
	else
	{
		return FALSE;
	}
	
	return TRUE;
}


void HuffmanSendDlg::OnEnChangeObjectPidEditctrl()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString EncodedText;
	GetDlgItemText(IDC_ENCODED_TEXT_EDITCTRL, EncodedText);

	
	CString PIDInfo;
	GetDlgItemText(IDC_OBJECT_PID_EDITCTRL, PIDInfo);

	CWnd *SendMsgBtn = GetDlgItem(IDC_SEND_MSG_BTN);
	if (PIDInfo != "" && EncodedText != "")
	{
		SendMsgBtn->EnableWindow(1);
	}
	else
	{
		SendMsgBtn->EnableWindow(0);
	}
}


void HuffmanSendDlg::OnBnClickedReadPathBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR           szFolderPath[MAX_PATH] = { 0 };

	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("请选择一个文件夹：");
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名  
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			FindTXTFile(szFolderPath);
			ReadFileList.PathName = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
}
