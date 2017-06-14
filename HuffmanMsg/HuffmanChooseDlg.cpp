// HuffmanChooseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HuffmanMsg.h"
#include "HuffmanChooseDlg.h"
#include "afxdialogex.h"
#include "HuffmanSendDlg.h"
#include "HuffmanReceiveDlg.h"

// HuffmanChooseDlg �Ի���

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


// HuffmanChooseDlg ��Ϣ�������

BOOL HuffmanChooseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//  �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void HuffmanChooseDlg::OnPaint()
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
