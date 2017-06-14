// HuffmanChooseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HuffmanMsg.h"
#include "HuffmanChooseDlg.h"
#include "afxdialogex.h"
#include "HuffmanSendDlg.h"
#include "HuffmanReceiveDlg.h"

// HuffmanChooseDlg 对话框

IMPLEMENT_DYNAMIC(HuffmanChooseDlg, CDialogEx)

HuffmanChooseDlg::HuffmanChooseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HUFFMAN_CHOOSE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

HuffmanChooseDlg::~HuffmanChooseDlg()
{
}

void HuffmanChooseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}




BEGIN_MESSAGE_MAP(HuffmanChooseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_SEND_DLG_BTN, &HuffmanChooseDlg::OnBnClickedOpenSendDlgBtn)
	ON_BN_CLICKED(IDC_OPEN_RECEIVE_DLG_BTN, &HuffmanChooseDlg::OnBnClickedOpenReceiveDlgBtn)
	ON_BN_CLICKED(IDC_QUIT_BTN, &HuffmanChooseDlg::OnBnClickedQuitBtn)
END_MESSAGE_MAP()


// HuffmanChooseDlg 消息处理程序

BOOL HuffmanChooseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//  如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void HuffmanChooseDlg::OnPaint()
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
HCURSOR HuffmanChooseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void HuffmanChooseDlg::OnBnClickedOpenSendDlgBtn()
{
	HuffmanSendDlg *pSendDlg = new HuffmanSendDlg();
	pSendDlg->Create(IDD_SENDMSG_DLG, this);
	pSendDlg->ShowWindow(SW_SHOWNORMAL);
	this->ShowWindow(SW_HIDE);
}


void HuffmanChooseDlg::OnBnClickedOpenReceiveDlgBtn()
{
	HuffmanReceiveDlg *pReceiveDlg = new HuffmanReceiveDlg();
	pReceiveDlg->Create(IDD_RECEIVEMSG_DLG, this);
	pReceiveDlg->ShowWindow(SW_SHOWNORMAL);
	this->ShowWindow(SW_HIDE);	
}


void HuffmanChooseDlg::OnBnClickedQuitBtn()
{
	PostMessage(WM_CLOSE);
}
