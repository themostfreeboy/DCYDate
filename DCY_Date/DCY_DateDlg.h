
// DCY_DateDlg.h : ͷ�ļ�
//

#pragma once


// CDCY_DateDlg �Ի���
class CDCY_DateDlg : public CDialogEx
{
// ����
public:
	CDCY_DateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DCY_DATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBexit();
	int MyLoadPicture(CString picturename);
};

int JudgeYear(int year);//�ж�ƽ����
int JudgeMonth(int year,int month);//�ж�ĳ���ж�����
int CalculuteDay(int startyear,int startmonth,int startday,int endyear,int endmonth,int endday);//������������������
int CalculuteDayInOneYear(int year,int month,int day);//����ĳһ����Ϊ����ĵڼ���
int JudgeWeek(int year,int month,int day);//�ж�ĳһ�������ڼ�
UINT proc1(LPVOID pParam);
UINT proc2(LPVOID pParam);