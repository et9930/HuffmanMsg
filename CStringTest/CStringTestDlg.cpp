
// CStringTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CStringTest.h"
#include "CStringTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCStringTestDlg �Ի���



CCStringTestDlg::CCStringTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CSTRINGTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCStringTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCStringTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCStringTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCStringTestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCStringTestDlg ��Ϣ�������

BOOL CCStringTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//CString a,b;
	//
	//GetDlgItem(IDC_EDIT_ORI)->GetWindowTextW(a);
	//int ddd = a.GetLength();
	//wchar_t DirName[65536] = { 0 };
	//lstrcpynW(DirName, (LPCTSTR)a, ddd+1);
	//for (int i = 0; i < ddd; i++)
	//{
	//	CString Bin;
	//	
	//	Dec2Bin(&Bin, (int)DirName[i]);		
	//	b = b + Bin;
	//}
	//GetDlgItem(IDC_ENCODE)->SetWindowTextW(b);
	//wchar_t d[65536] = { 0 };
	//lstrcpynW(d, (LPCTSTR)b, ddd * 16 + 1);
	//CString g;
	//for (int i = 0; i < b.GetLength() / 16; i++)
	//{
	//	int nResult = 0;
	//	for (int j = 0; j<16; j++)
	//	{
	//		nResult += (d[i*16+j]- '0')*pow(2.0, 15-j);
	//	}
	//	wchar_t e = (wchar_t)nResult;
	//	CString f(e);
	//	g = g + f;
	//}
	//GetDlgItem(IDC_DECODE)->SetWindowTextW(g);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCStringTestDlg::OnPaint()
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
HCURSOR CCStringTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCStringTestDlg::Dec2Bin(CString * Bin, int Dec)
{
	wchar_t a[17];
	for (int i = 0; i < 16; i++)
	{
		a[i] = '0';
	}
	a[16] = '\0';
	int j = 15;
	while (Dec)
	{
		if (Dec % 2 == 0)
		{
			a[j] = '0';
		}
		else
		{
			a[j] = '1';
		}
		Dec = Dec / 2;
		j--;
	}

	Bin->Format(L"%s",a);
	return;
}

void CCStringTestDlg::Bin2Dec(CString Bin, int * Dec)
{

}



void CCStringTestDlg::OnBnClickedButton1()
{
	CString a, b;

	GetDlgItem(IDC_EDIT_ORI)->GetWindowTextW(a);
	int ddd = a.GetLength();
	wchar_t DirName[65536] = { 0 };
	lstrcpynW(DirName, (LPCTSTR)a, ddd + 1);
	for (int i = 0; i < ddd; i++)
	{
		CString Bin;

		Dec2Bin(&Bin, (int)DirName[i]);
		b = b + Bin;
	}
	GetDlgItem(IDC_EDIT_ENCODED)->SetWindowTextW(b);
}


void CCStringTestDlg::OnBnClickedButton2()
{
	CString b;
	GetDlgItem(IDC_EDIT_ENCODED)->GetWindowTextW(b);
	wchar_t d[65536] = { 0 };
	lstrcpynW(d, (LPCTSTR)b, b.GetLength()+1);
	CString g;
	for (int i = 0; i < b.GetLength() / 16; i++)
	{
		int nResult = 0;
		for (int j = 0; j<16; j++)
		{
			nResult += (d[i * 16 + j] - '0')*pow(2.0, 15 - j);
		}
		wchar_t e = (wchar_t)nResult;
		CString f(e);
		g = g + f;
	}
	GetDlgItem(IDC_EDIT_DECODED)->SetWindowTextW(g);
}
