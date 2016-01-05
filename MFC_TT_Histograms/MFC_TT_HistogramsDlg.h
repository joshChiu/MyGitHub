
// MFC_TT_HistogramsDlg.h : ���Y��
//

#pragma once

#include <opencv\cv.h>
#include <iostream>
#include <opencv\highgui.h>
#include <string>


using namespace std;  // iostream �����w�Ѽ�
using namespace cv;  // cv �����w�Ѽ�

// CMFC_TT_HistogramsDlg ��ܤ��
class CMFC_TT_HistogramsDlg : public CDialogEx
{
// �غc
public:
	CMFC_TT_HistogramsDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_MFC_TT_HISTOGRAMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	
	void ShowMatOnPicture(Mat& image, CDialog* dlg, int pID) ;

	RGBQUAD *GrayColorTable;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnStnClickedStatic1();
	afx_msg void OnStnClickedStatichist();

	afx_msg void OnStnClickedHdomain();
	afx_msg void OnStnClickedSdomain();
	
	afx_msg void OnStnClickedHsv();
	afx_msg void OnStnClickedStatic2();
	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	afx_msg void OnBnClickedButton7();
};
