
// OmronFinsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OmronFins.h"
#include "OmronFinsDlg.h"
#include "afxdialogex.h"
#include "COmronFins.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

USING_OMRAN_NAMESPACE
	// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
	{
	public:
		CAboutDlg();

		// �Ի�������
		enum { IDD = IDD_ABOUTBOX };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

		// ʵ��
	protected:
		DECLARE_MESSAGE_MAP()
	};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
	{
	}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialogEx::DoDataExchange(pDX);
	}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COmronFinsDlg �Ի���



COmronFinsDlg::COmronFinsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COmronFinsDlg::IDD, pParent)
	{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

void COmronFinsDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialogEx::DoDataExchange(pDX);
	}

BEGIN_MESSAGE_MAP(COmronFinsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &COmronFinsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COmronFinsDlg ��Ϣ�������

BOOL COmronFinsDlg::OnInitDialog()
	{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
		{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
			{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			}
		}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
	}

void COmronFinsDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
		}
	else
		{
		CDialogEx::OnSysCommand(nID, lParam);
		}
	}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COmronFinsDlg::OnPaint()
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
HCURSOR COmronFinsDlg::OnQueryDragIcon()
	{
	return static_cast<HCURSOR>(m_hIcon);
	}



void COmronFinsDlg::OnBnClickedOk()
	{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();

	auto omronFins = CCOmronFins::Create();
	omronFins->ConnectPLC(9600,"192.168.100.193");
	CString valueFrame;
	omronFins->Read("D1000",valueFrame);
	
	}
