
// DCY_DateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DCY_Date.h"
#include "DCY_DateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDCY_DateDlg 对话框
CDCY_DateDlg *dlg_backup;



CDCY_DateDlg::CDCY_DateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDCY_DateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDCY_DateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDCY_DateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BEXIT, &CDCY_DateDlg::OnBnClickedBexit)
END_MESSAGE_MAP()


// CDCY_DateDlg 消息处理程序

BOOL CDCY_DateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	dlg_backup=this;
	SetWindowText(_T("亲爱的瑜宝宝"));
	WriteFile("dcypicture.jpg",data_dcy_jpg,86338);
	for(int i=0;i<5;i++)
	{
		if(MyLoadPicture(_T(".\\dcypicture.jpg"))==1)//成功载入位图
		{
			break;
		}
		Sleep(200);
	}
	HANDLE thread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)proc1,NULL,0,NULL);//启动多线程
	HANDLE thread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)proc2,NULL,0,NULL);//启动多线程

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDCY_DateDlg::OnPaint()
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
HCURSOR CDCY_DateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDCY_DateDlg::OnBnClickedBexit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}

int JudgeYear(int year)//判断平闰年
{
	if(year%400==0)		            return 1;//闰年
	    else if(year%100==0)		return 0;//平年
	    else if(year%4==0)		    return 1;//闰年
	    else		                return 0;//平年
}

int JudgeMonth(int year,int month)//判断某月有多少天
{
	switch(month)
	{
	       case 1:{return 31;}
		   case 2:
		   {
			   if(JudgeYear(year)==1)   return 29;//闰年
			       else                 return 28;//平年
		   }
		   case 3:{return 31;}
		   case 4:{return 30;}
		   case 5:{return 31;}
		   case 6:{return 30;}
		   case 7:{return 31;}
		   case 8:{return 31;}
		   case 9:{return 30;}
		   case 10:{return 31;}
		   case 11:{return 30;}
		   case 12:{return 31;}
		   default:{return -1;}
	}
}

int CalculuteDay(int startyear,int startmonth,int startday,int endyear,int endmonth,int endday)//计算两日期相距多少天
{
	if(endyear<startyear)                                                           return -1;//数据有误
	    else if((endyear==startyear)&&(endmonth<startmonth))                        return -1;//数据有误
	    else if((endyear==startyear)&&(endmonth==startmonth)&&(endday<startday))    return -1;//数据有误
	int days=0;
	if(endyear>startyear)
	{
		int startyearday=0;
		if(JudgeYear(startyear)==1)       startyearday=366;//闰年
		    else                          startyearday=365;//平年
		days+=startyearday-CalculuteDayInOneYear(startyear,startmonth,startday);
		int tempyearday=0;
		for(int i=startyear+1;i<endyear;i++)
		{
			if(JudgeYear(i)==1)           tempyearday=366;//闰年
		        else                      tempyearday=365;//平年
			days+=tempyearday;
		}
		days+=CalculuteDayInOneYear(endyear,endmonth,endday);
	}
	else//endyear==startyear
	{
		days=CalculuteDayInOneYear(endyear,endmonth,endday)-CalculuteDayInOneYear(startyear,startmonth,startday);
	}
	return days;
}

int CalculuteDayInOneYear(int year,int month,int day)//计算某一日期为该年的第几天
{
	int sumdays=0;
	for(int i=1;i<month;i++)
	{
		sumdays+=JudgeMonth(year,i);
	}
	sumdays+=day;
	return sumdays;
}

int JudgeWeek(int year,int month,int day)//判断某一日期星期几
{
	//1601年1月1日星期一
	int days=CalculuteDay(1601,1,1,year,month,day);
	return (days%7+1);
}

int CDCY_DateDlg::MyLoadPicture(CString picturename)
{
	//判断picturename文件是否存在
	errno_t err_read;
	FILE *fp_read = NULL;
	err_read = fopen_s(&fp_read, MyCStringToConstChar(picturename), "rb");
	if (err_read != 0)
	{
		return -1;//文件打开失败
	}
	fclose(fp_read);

	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_SPC);//得到Picture Control句柄
    CImage image; 
    image.Load(picturename);
    HBITMAP hBmp = image.Detach();
    pWnd->SetBitmap(hBmp);
	if(hBmp)
	{
		//DeleteObject(hBmp);
	}
	return 1;//成功
}

UINT proc1(LPVOID pParam)
{
	SYSTEMTIME SystemTime;
	int year=-1;
	int month=-1;
	int day=-1;
	int week=-1;
	int hour=-1;
	int minute=-1;
	int oldsecond=-2;
	int newsecond=-3;
	CString cstr_time=_T("");
    while(true)
    {
	    GetLocalTime(&SystemTime);//获取系统时间
		newsecond=SystemTime.wSecond;
		if(newsecond!=oldsecond)
		{
			oldsecond=newsecond;
			year=SystemTime.wYear;
	        month=SystemTime.wMonth;
	        day=SystemTime.wDay;
	        week=SystemTime.wDayOfWeek;
	        hour=SystemTime.wHour;
	        minute=SystemTime.wMinute;
			CString cstr_time=_T("");
			switch(week)
			{
				case 0:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期日 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
				case 1:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期一 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
				case 2:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期二 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
				case 3:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期三 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
				case 4:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期四 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
				case 5:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期五 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
				case 6:{cstr_time.Format(_T("当前时间：%04d年%02d月%02d日星期六 %02d:%02d:%02d"),year,month,day,hour,minute,newsecond);break;}
				default:{break;}
			}
			dlg_backup->SetDlgItemText(IDC_STIME,cstr_time);
        }
	}
	return 0;
}

UINT proc2(LPVOID pParam)
{
	SYSTEMTIME SystemTime;
	int year=-1;
	int month=-1;
	int day=-1;
	int oldapartday0214=-2;
	int newapartday0214=-3;
	int newapartday0520=-3;
	int newapartday0601=-3;
	int newapartday0723=-3;
	int newapartday1225=-3;
	CString cstr_apartday=_T("");
	while(true)
	{
		GetLocalTime(&SystemTime);//获取系统时间
		year=SystemTime.wYear;
		month=SystemTime.wMonth;
		day=SystemTime.wDay;
		newapartday0214=CalculuteDay(year,month,day,year,2,14);
		if(newapartday0214==-1)
		{
			newapartday0214=CalculuteDay(year,month,day,year+1,2,14);
		}
		if(newapartday0214!=oldapartday0214)
		{
			oldapartday0214=newapartday0214;
			newapartday0520=CalculuteDay(year,month,day,year,5,20);
			if(newapartday0520==-1)
			{
				newapartday0520=CalculuteDay(year,month,day,year+1,5,20);
			}
			newapartday0601=CalculuteDay(year,month,day,year,6,1);
			if(newapartday0601==-1)
			{
				newapartday0601=CalculuteDay(year,month,day,year+1,6,1);
			}
			newapartday0723=CalculuteDay(year,month,day,year,7,23);
			if(newapartday0723==-1)
			{
				newapartday0723=CalculuteDay(year,month,day,year+1,7,23);
			}
			newapartday1225=CalculuteDay(year,month,day,year,12,25);
			if(newapartday1225==-1)
			{
				newapartday1225=CalculuteDay(year,month,day,year+1,12,25);
			}
			cstr_apartday.Format(_T("%d"),newapartday0214);
			dlg_backup->SetDlgItemText(IDC_E0214,cstr_apartday);
			cstr_apartday.Format(_T("%d"),newapartday0520);
			dlg_backup->SetDlgItemText(IDC_E0520,cstr_apartday);
			cstr_apartday.Format(_T("%d"),newapartday0601);
			dlg_backup->SetDlgItemText(IDC_E0601,cstr_apartday);
			cstr_apartday.Format(_T("%d"),newapartday0723);
			dlg_backup->SetDlgItemText(IDC_E0723,cstr_apartday);
			cstr_apartday.Format(_T("%d"),newapartday1225);
			dlg_backup->SetDlgItemText(IDC_E1225,cstr_apartday);
		}
	}
	return 0;
}