
// MFC_TT_HistogramsDlg.h : 標頭檔
//

#pragma once

#include <opencv\cv.h>
#include <iostream>
#include <opencv\highgui.h>
#include <string>


using namespace std;  // iostream 的內定參數
using namespace cv;  // cv 的內定參數

// CMFC_TT_HistogramsDlg 對話方塊
class CMFC_TT_HistogramsDlg : public CDialogEx
{
// 建構
public:
	CMFC_TT_HistogramsDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_MFC_TT_HISTOGRAMS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
