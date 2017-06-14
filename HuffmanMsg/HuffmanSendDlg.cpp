// HuffmanSendDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HuffmanMsg.h"
#include "HuffmanSendDlg.h"
#include "afxdialogex.h"


// HuffmanSendDlg �Ի���

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


// HuffmanSendDlg ��Ϣ�������

BOOL HuffmanSendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//  �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void HuffmanSendDlg::OnPaint()
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
HCURSOR HuffmanSendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���عرհ�ť
LRESULT HuffmanSendDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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


void HuffmanSendDlg::OnEnChangeOriginalTextEditctrl()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	CString fdPath;   //����·������  
	Path = Path + L"\\*.*"; //�ļ���·��  
	CString strTmp;      //��׺������  

	CFileFind find;     //����CFileFind  
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
				//������ļ�,�ж��Ƿ���*.txt  
				fdPath = find.GetFileName();
				strTmp = fdPath.Right(4);  //ȡ��׺��  
				strTmp.MakeLower();     //�ַ���Сд��  
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
	// ���ù�����   
	TCHAR szFilter[] = L"�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||";
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, L"txt", NULL, 0, szFilter, this);
	CString strFilePath;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR           szFolderPath[MAX_PATH] = { 0 };

	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("��ѡ��һ���ļ��У�");
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn = NULL;

	// ��ʾ�ļ���ѡ��Ի���  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// ȡ���ļ�����  
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
