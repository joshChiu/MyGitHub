
// MFC_TT_HistogramsDlg.cpp : 實作檔
//


#include "stdafx.h"
#include "MFC_TT_Histograms.h"
#include "MFC_TT_HistogramsDlg.h"
#include "afxdialogex.h"

#include <opencv/cv.h>
#include <stdio.h>  // C的函式庫
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cxcore.h>   
#include <vector>   

#include <iostream>  // 引入C++<iostream>函式庫

using namespace std;  //C++的函式庫會定義在std名稱空間
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CMFC_TT_HistogramsDlg 對話方塊



CMFC_TT_HistogramsDlg::CMFC_TT_HistogramsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_TT_HistogramsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_TT_HistogramsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_TT_HistogramsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_TT_HistogramsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC_TT_HistogramsDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC_TT_HistogramsDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC_TT_HistogramsDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFC_TT_HistogramsDlg::OnBnClickedButton5)

	ON_STN_CLICKED(IDC_Hdomain, &CMFC_TT_HistogramsDlg::OnStnClickedHdomain)
	ON_STN_CLICKED(IDC_Sdomain, &CMFC_TT_HistogramsDlg::OnStnClickedSdomain)
	
	ON_STN_CLICKED(IDC_HSV, &CMFC_TT_HistogramsDlg::OnStnClickedHsv)

	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON6, &CMFC_TT_HistogramsDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFC_TT_HistogramsDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CMFC_TT_HistogramsDlg 訊息處理常式

BOOL CMFC_TT_HistogramsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	//GrayColorTable = new RGBQUAD[256];						// Gray CImage color table
	//for (int i = 0; i<256; i++)
		//GrayColorTable[i].rgbBlue = GrayColorTable[i].rgbGreen = GrayColorTable[i].rgbRed = (BYTE)(i);

	///Hue_bin IDC_SLIDER
	CSliderCtrl *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);   //IDC_SLIDER1 是 slider的名稱
	pSlidCtrl->SetRange(3, 180, TRUE);    //設定大小值                             
	pSlidCtrl->SetPos(21);
	pSlidCtrl->SetTicFreq(1);

	/// Saturation_bin IDC_SLIDER
	CSliderCtrl *pSlidCtrl2 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER4);   //IDC_SLIDER1 是 slider的名稱
	pSlidCtrl2->SetRange(5, 255, TRUE);    //設定大小值                             
	pSlidCtrl2->SetPos(73);
	pSlidCtrl2->SetTicFreq(1);

	/// Hue Bin 區間下限
	CSliderCtrl *pSlidCtrl3 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER5);   //IDC_SLIDER1 是 slider的名稱
	pSlidCtrl3->SetRange(1, 170, TRUE);    //設定大小值                             
	pSlidCtrl3->SetPos(80);  // 80
	pSlidCtrl3->SetTicFreq(1);

	/// Hue Bin 區間上限
	CSliderCtrl *pSlidCtrl4 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER6);   //IDC_SLIDER1 是 slider的名稱
	pSlidCtrl4->SetRange(6, 180, TRUE);    //設定大小值                             
	pSlidCtrl4->SetPos(95);
	pSlidCtrl4->SetTicFreq(1);

	/// S 區間下限
	CSliderCtrl *pSlidCtrl5 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER7);   //IDC_SLIDER1 是 slider的名稱
	pSlidCtrl5->SetRange(1, 255, TRUE);    //設定大小值                             
	pSlidCtrl5->SetPos(75); // 75
	pSlidCtrl5->SetTicFreq(1);

	/// S 區間上限
	CSliderCtrl *pSlidCtrl6 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER8);   //IDC_SLIDER1 是 slider的名稱
	pSlidCtrl6->SetRange(6, 255, TRUE);    //設定大小值                             
	pSlidCtrl6->SetPos(90);
	pSlidCtrl6->SetTicFreq(1);


	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}



void CMFC_TT_HistogramsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFC_TT_HistogramsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFC_TT_HistogramsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


IplImage *image;
IplImage *image_resize = cvCreateImage(cvSize(1288, 964), IPL_DEPTH_8U, 3);  //把image 轉成需要的大小
IplImage *image_gray;       //灰階圖
IplImage *image_smooth;     //把灰階圖做smooth

IplImage *image_hsv;     //把圖做SHV 已做smooth
IplImage *image_threshold;  //把smooth過的圖，用Threshold變成黑白的

IplImage *image_canny;      //把Threshold過的圖做canny
IplImage *image_lines;      //把canny後的圖做Houghlines
IplImage *hist_x;			//水平投影



Mat src, dst; //建一些矩阵
//  Mat hsv;      //轉到hsv平面
//  Mat H,r2,S,V; //各顏色的閥值

int HbinsPosition= 21 ;
int SbinsPosition=127 ;
int Hue_BinLow=73 , Hue_BinHig=95 ;
int Sat_BinLow=75 , Sat_BinHig=90 ;

Mat hsv_planes, H, hsv, hue, Saturation, S;

Mat hueLow, hueBilateral ;
Mat SatLow, SatBilateral ;

Mat Huehist ;
Mat Saturationhist ;

Mat HSV;
// IplImage *HSV;


void CMFC_TT_HistogramsDlg::ShowMatOnPicture(Mat& image, CDialog* dlg, int pID)
{
	CRect PictureRect;
	CStatic* PictureControl = (CStatic*)dlg->GetDlgItem(pID);
	PictureControl->GetClientRect(&PictureRect);
	CDC *pDc = PictureControl->GetWindowDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	Mat resizeImage = image.clone();
	if (resizeImage.rows>PictureRect.Height() || resizeImage.cols>PictureRect.Width())
	{
		double resizeRatio = min((double)PictureRect.Width() / (double)image.cols, (double)PictureRect.Height() / (double)image.rows);
		resize(image, resizeImage, Size(), resizeRatio, resizeRatio);
	}

	ATL::CImage outputImage;
	int width = resizeImage.cols;
	int height = resizeImage.rows;
	int channels = resizeImage.channels();
	outputImage.Destroy(); //clear
	outputImage.Create(width, height, 8 * channels);

	if (channels == 1)
	{
		RGBQUAD* ColorTable;
		int MaxColors = outputImage.GetMaxColorTableEntries();
		ColorTable = new RGBQUAD[MaxColors];
		outputImage.GetColorTable(0, MaxColors, ColorTable);
		for (int i = 0; i < MaxColors; i++)
		{
			ColorTable[i].rgbBlue = (BYTE)i;
			ColorTable[i].rgbGreen = (BYTE)i;
			ColorTable[i].rgbRed = (BYTE)i;
		}
		outputImage.SetColorTable(0, MaxColors, ColorTable);
		delete[]ColorTable;
	}

	uchar* ps;
	uchar* pimg = (uchar*)outputImage.GetBits(); //A pointer to the bitmap buffer
	//The pitch is the distance, in bytes. represent the beginning of
	// one bitmap line and the beginning of the next bitmap line
	int step = outputImage.GetPitch();
	for (int i = 0; i < height; ++i)
	{
		ps = (resizeImage.ptr<uchar>(i));
		for (int j = 0; j < width; j++)
		{
			if (channels == 1) //gray
			{
				*(pimg + i*step + j) = ps[j];
			}
			else if (channels == 3) //color
			{
				for (int k = 0; k < 3; k++)
				{
					*(pimg + i*step + j * 3 + k) = ps[j * 3 + k];
				}
			}
		}
	}
	outputImage.Draw(pDc->m_hDC, CRect(CPoint(PictureRect.TopLeft().x + (PictureRect.Width() - width) / 2, PictureRect.TopLeft().y + (PictureRect.Height() - height) / 2), CSize(width, height)));
	dlg->ReleaseDC(pDc);
}

  /// Function Headers
void pickPoint (int event, int x, int y, int, void* );  //打在第二題前面，讓程式先看懂他


void CMFC_TT_HistogramsDlg::OnBnClickedButton1()
{         
// AllocConsole();
// freopen ("CONOUT$", "w", stdout );  //輸入文字資訊

	image_smooth = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvSmooth(image, image_smooth, CV_BILATERAL, 3, 3, 11, 11); // BILATERAL (双向滤波) param1，param2分别是關於色彩和空間的參數

	image_hsv = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
  
	cvCvtColor(image, image_hsv, COLOR_BGR2HSV);

   Mat Matimage=image_hsv;
   ShowMatOnPicture(Matimage,this, IDC_HSV);  
}

/**
 * @function MouseCallback*/

void pickPoint (int event, int x, int y, int, void* param )
{
  if( event != EVENT_LBUTTONDOWN )
	{ return; }
  // Point get the HSV
  
		
  Point seed = Point( x, y );
//  HSV.at<Vec3b>(x,y)[0] = ; 

  HSV.at<uchar>(x,y) ;

  // uchar s = HSV.at<uchar>(seed.y,seed.x);



//  cout<< seed.y<<""<<seed.x<<" "<<endl;
  // CvScalar s = cvGet2D (HSV,seed.y,seed.x);
  // printf(" HSV : H=%.2f, S=%.2f, V=%.2f \n" , s.val[0], s.val[1], s.val[2]);
  
 
 
}



void onTrackbar1(int Position) { 


}
 
void CMFC_TT_HistogramsDlg::OnBnClickedButton2()
{       // Button 2   histogram (Hue-Saturation)

	/// Global Variables
  Mat src, dst ;// ,hsv;  //建一些矩阵
  Mat H,r2,S,V; //各顏色的閥值

  int bins = 25;
  Mat hue;

    /// Read the image
   // src = imread ("0930.png ");
   // if ( !src.data ) cout<<"Error loading src \n"<<endl;  //文字模式下輸出"Find the"字串
 

   /// Transform it to HSV
   // cvtColor(src,hsv,CV_BGR2HSV); //轉成hsv平面 CV_BGR2HSV

 /// Use only the Hue value
  //hue.create( hsv.size(), hsv.depth() );
  //int ch[] = { 0, 0 };
  //mixChannels( &hsv, 1, &hue, 1, ch, 1 );



    /// 分割成3个单通道图像 ( H, S 和 V )
 vector<Mat> hsv_planes;   //Mat - 基本图像容器
 split( image_hsv, hsv_planes );



 /// 设定bin数目 360/2
 int histSize = 180; 
 int histSize_sv = 255; 

 /// 设定取值范围 ( H,S,V) )
 float range[] = { 0, 256 } ;
 const float* histRange = { range };

 bool uniform = true; bool accumulate = false; // bin范围设定成同样大小(均一)

 inRange(hsv_planes[0],80,95, H);  
    //二值化：h值介於80~95 
 inRange(hsv_planes[1],Scalar(45) , Scalar(70), S);            
    //二值化：s值介於45~70
 inRange(hsv_planes[2],Scalar(0) ,Scalar(255), V);                
    //二值化：v值介於120~255


 Mat h_hist, s_hist, v_hist; //最后创建储存直方图的矩阵

 /// 计算直方图:
 calcHist( &hsv_planes[0] , 1, 0, Mat(), h_hist, 1, &histSize, &histRange, uniform, accumulate );
 calcHist( &hsv_planes[1] , 1, 0, Mat(), s_hist, 1, &histSize_sv, &histRange, uniform, accumulate );
 calcHist( &hsv_planes[2] , 1, 0, Mat(), v_hist, 1, &histSize_sv, &histRange, uniform, accumulate );
 // &rgb_planes[0]: 输入数组(或数组集)
 // 1: 输入数组的个数, 0: 需要统计的通道 (dim)索引 ,Mat(): 掩码( 0 表示忽略该像素) ,h_hist: 储存直方图的矩阵 ,1: 直方图维数 ,histRange: 每个维度的取值范围
 // uniform 和 accumulate: bin大小相同，清楚直方图痕迹


 // 创建直方图画布
 int hist_w = 400; int hist_h = 400;
 int bin_w = cvRound( (double) hist_w/histSize );
 int svbin_w = cvRound( (double) hist_w/histSize_sv );

 Mat histImage_h( hist_w, hist_h, CV_8UC3, Scalar( 0,0,0) );
 Mat histImage_s( hist_w, hist_h, CV_8UC3, Scalar( 0,0,0) );
 Mat histImage_v( hist_w, hist_h, CV_8UC3, Scalar( 0,0,0) );
 
 /// 将直方图归一化到范围 [ 0, histImage.rows ]
 normalize(h_hist, h_hist, 0, histImage_h.rows, NORM_MINMAX, -1, Mat() );
 normalize(s_hist, s_hist, 0, histImage_s.rows, NORM_MINMAX, -1, Mat() );
 normalize(v_hist, v_hist, 0, histImage_v.rows, NORM_MINMAX, -1, Mat() );

 /*
#b_hist: Input array
#b_hist: Output normalized array (can be the same)
#0 and**histImage.rows**: For this example, they are the lower and upper limits to normalize the values of h_hist
#NORM_MINMAX: Argument that indicates the type of normalization (as described above, it adjusts the values between the two limits set before)
#-1: Implies that the output normalized array will be the same type as the input
#Mat(): Optional mask
*/

 /// 在直方图画布上画出直方图  
 for( int i = 1; i < histSize; i++ )
   {
     line( histImage_h, Point( bin_w*(i-1), hist_h - cvRound(h_hist.at<float>(i-1)) ) ,
                        Point( bin_w*(i), hist_h - cvRound(h_hist.at<float>(i)) ),
                        Scalar( 0, 0, 255), 2, 8, 0  );

     line( histImage_s, Point( svbin_w*(i-1), hist_h - cvRound(s_hist.at<float>(i-1)) ) ,
                        Point( svbin_w*(i), hist_h - cvRound(s_hist.at<float>(i)) ),
                        Scalar( 0, 255, 0), 2, 8, 0  );

     line( histImage_v, Point( svbin_w*(i-1), hist_h - cvRound(v_hist.at<float>(i-1)) ) ,
                        Point( svbin_w*(i), hist_h - cvRound(v_hist.at<float>(i)) ),
                        Scalar( 255, 0, 0), 2, 8, 0  );
    }
 void line(CV_IN_OUT Mat& img, Point pt1, Point pt2, const Scalar& color,
                     int thickness=1, int lineType=8, int shift=0); 
 /// 显示直方图
 
//  imshow("Hdomain",H);
//  imshow("Sdomain",S);
 // Mat Matimage=image_hsv;  
 ShowMatOnPicture(H, this, IDC_STATIC);  //IDC_STATIC  ,IDC_Hdomain

 //cvWaitKey(200);

 //Mat Matimage=image_hsv;
 ShowMatOnPicture(S, this, IDC_HSV);   // IDC_HSV  ,  IDC_Sdomain

 // DrawMatOnPicture(image_hsv , IDC_Hdomain);
 // DrawMatOnPicture(image_hsv , IDC_Sdomain);

 namedWindow("calcHist Demo_H" , CV_WINDOW_AUTOSIZE );
 namedWindow("calcHist Demo_S", CV_WINDOW_AUTOSIZE );
 namedWindow("calcHist Demo_V", CV_WINDOW_AUTOSIZE );
 
 imshow("calcHist Demo_H" , histImage_h );
 imshow("calcHist Demo_S", histImage_s );
 imshow("calcHist Demo_V", histImage_v );

 waitKey(0);
 
///////////////////////////////////////////////
}

 //int HueRangePosition = 30;
 //int HueMovePosition = 180;


void onTrackbar(int Position) {  
	
	//int Range=HueRangePosition-10;
    //int Move=HueMovePosition -10;
    // double a,b;

   //vector<Mat> hsv_planes;   //Mat - 基本图像容器
   //split(hsv, hsv_planes );

  MatND hist;
  int histSize = MAX( HbinsPosition, 2 );
  float hue_range[] = { 0, 180 };
  const float* ranges = { hue_range };

  MatND Shist;
  int ShistSize = MAX( SbinsPosition, 2 );
  float Saturation_range[] = { 0, 255 };
  const float* Sranges = { Saturation_range };


  //Brightness/Contrast Formula
  //a=Move ; //-(Range/4);
  //b=Range; //4);

  
  /// Get the Histogram and normalize it
  calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
  normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

  calcHist(&Saturation, 1, 0, Mat(), Shist, 1, &ShistSize, &Sranges, true, false );
  normalize( Shist, Shist, 0, 255, NORM_MINMAX, -1, Mat() );

  /// Get Backprojection
  MatND backproj;
  calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true );

  MatND Sbackproj;
  calcBackProject(&Saturation, 1, 0, Shist, Sbackproj, &Sranges, 1, true );


  /// Draw the backproj
  imshow( "BackProj", backproj );
  imshow( "SBackProj", Sbackproj );

	/// Draw the histogram
  int w = 400; int h = 400;
  int bin_w = cvRound( (double) w / histSize );
  Mat histImg = Mat::zeros( w, h, CV_8UC3 );

  for( int i = 0; i < HbinsPosition; i ++ )
     { rectangle( histImg, Point( i*bin_w, h ),
	 Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 0, 0, 255 ), -1 ); }


  int S_w = 400; int S_h = 400;
  int Sbin_w = cvRound( (double) S_w / ShistSize );
  Mat ShistImg = Mat::zeros( S_w, S_h, CV_8UC3 );

  for( int i = 0; i < SbinsPosition; i ++ )
     { rectangle( ShistImg, Point( i*Sbin_w, h ),
	 Point( (i+1)*Sbin_w, S_h - cvRound( Shist.at<float>(i)*S_h/255.0 ) ), Scalar( 0, 0, 255 ), -1 ); }

    //End
  
    imshow( "Histogram", histImg );
	imshow( "SHistogram", ShistImg );
	//imshow("Hdomain",H);


}
  

void CMFC_TT_HistogramsDlg::OnBnClickedButton3()
{


	/// Global Variables
   //char** argv ;

    /// Read the image
   src = imread ("0930.png ");
   if ( !src.data ) cout<<"Error loading src \n"<<endl;  //文字模式下輸出"Find the"字串
 
   /// Transform it to HSV
   cvtColor(src,hsv,CV_BGR2HSV); //轉成hsv平面 CV_BGR2HSV

  /// Use only the Hue value
  hue.create( hsv.size(), hsv.depth() );
  int ch[] = { 0, 0 };
  mixChannels( &hsv, 1, &hue, 1, ch, 1 );

  /// Use only the Saturation value
  Saturation.create( hsv.size(), hsv.depth() );
  int ch1[] = { 1, 0 };
  mixChannels( &hsv, 1, &Saturation, 1, ch1, 1 );


  inRange(hue,80,95, H);  
  //二值化：h值介於80~95 

  inRange(Saturation,45,70, S);  
  //二值化：s值介於75~90 



  /// 创建 Trackbar 来输入bin的数目
 char* window_image = "Source image";
 cvNamedWindow("BackProj",CV_WINDOW_AUTOSIZE);
 cvNamedWindow("SBackProj",CV_WINDOW_AUTOSIZE);

 cvCreateTrackbar("*Huebins:","BackProj",&HbinsPosition, 179, onTrackbar );  //最大限制
 cvCreateTrackbar("*Saturationbins:","SBackProj",&SbinsPosition, 255, onTrackbar );  //最大限制

 //cvCreateTrackbar("HueRange","HueRange/Move",&HueRangePosition,180,onTrackbar);
 //cvCreateTrackbar("HueMove","HueRange/Move" ,&HueMovePosition,180,onTrackbar);

 onTrackbar(0);

 /// Show the image
 imshow( window_image, src );

 waitKey(0);

}



void CMFC_TT_HistogramsDlg::OnBnClickedButton4()   //Read Image
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CStringA cs;        //CStringA 物件包含 char 類型，且支援單一位元組和多位元組 (MBCS) 字串。     string ASCII                        
	//CStringW 物件包含 wchar_t 類型，且支援 Unicode 字串。 CString 物件支援 char 類型或 wchar_t 類型，具體取決於編譯時是定義 MBCS 符號，還是 UNICODE 符號。
	
	CFileDialog fd(TRUE);
	if (fd.DoModal()==IDOK)              //IDOK 和 IDCANCEL 是表示常數使用者是否選取了 [確定] 或 [取消] 按鈕。
	{                                    //if 內表示選擇圖片
	cs = fd.GetPathName();
	string s = cs.GetBuffer(0);
	cout << s.c_str();
	image = cvLoadImage(s.c_str(), 1);
	//cvResize(image,image_resize,1);
	}
    
	image_gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);  //創造空間給灰階圖   
	cvCvtColor(image,image_gray,CV_BGR2GRAY);   //灰階圖

//	cvNamedWindow("w",1);  //image_gray秀出在DrawMatOnPicture 沒能解決,更換副程式ShowMatOnPicture
//	cvShowImage("w",image_gray);  

	Mat Matimage=image;
	ShowMatOnPicture(Matimage,this, IDC_STATIC);     


	// Mat Matimage2 = image_gray;
	// ShowMatOnPicture(Matimage2, this, IDC_HSV);    //把圖顯示在介面上


	image_smooth = cvCreateImage(cvGetSize(image_gray), IPL_DEPTH_8U, 1);
	cvSmooth(image_gray, image_smooth, CV_BILATERAL, 3, 3, 11, 11); // BILATERAL (双向滤波) param1，param2分别是關於色彩和空間的參數；param3和param4根本没有用

	Mat Matimage2 = image_smooth;
	// ShowMatOnPicture(Matimage2, this, IDC_HSV);    //把圖顯示在介面上  



}



void CMFC_TT_HistogramsDlg::OnStnClickedHdomain()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}


void CMFC_TT_HistogramsDlg::OnStnClickedSdomain()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}

/*		CString ss;
		ss.Format(_T("%S"), title.c_str());
		pAlignStatus->SetWindowText(ss);

		
		MatND hist;
		int histSize = MAX(HbinsPosition, 2);
		float hue_range[] = { 0, 180 };
		const float* ranges = { hue_range };

		/// Get the Histogram and normalize it
		calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
		normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

		/// Get Backprojection
		MatND backproj;
		calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);

		/// Draw the backproj
		 // imshow("BackProj", backproj);

		Mat Matimage = backproj;
		ShowMatOnPicture(Matimage, this, IDC_STATIC);



		/// Draw the histogram
		int w = 400; int h = 400;
		int bin_w = cvRound((double)w / histSize);
		Mat histImg = Mat::zeros(w, h, CV_8UC3);

		for (int i = 0; i < HbinsPosition; i++)
		{
			rectangle(histImg, Point(i*bin_w, h),
				Point((i + 1)*bin_w, h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(0, 0, 255), -1);
		}


		//imshow("Histogram", histImg);

		Mat Matimage2= histImg;
		ShowMatOnPicture(histImg, this, IDC_HSV);  // (hist_x, IDC_STATIC_hist);   //把水平投影同步顯示在介面上

		//Mat Matimage = image_canny;
		//ShowMatOnPicture(Matimage, this, IDC_HSV);  // (image_canny, IDC_HSV);			  //把圖顯示在介面上

		/*
		hist_x = cvCreateImage(cvSize(image_canny->width, 256), 8, 3);    //histogram 開始
		int *xhist = new int[image_canny->width];

		for (int i = 0; i<image_canny->width; i++)  //x座標的每一點，設為零
		{
			xhist[i] = 0;
		}

		for (int j = 0; j<image_canny->height; j++)  //統計
		{
			uchar *ptr = (uchar*)(image_canny->imageData + j*image_canny->widthStep);
			for (int i = 0; i<image_canny->width; i++)
			{
				xhist[i] += (int)ptr[i];
			}
		}

		for (int i = 0; i<image_canny->width; i++)
		{
			//CvPoint* line = (CvPoint*)cvGetSeqElem(xhist,i);
			xhist[i] /= image_canny->height;
			//cvCircle(hist_x,cvPoint(i,xhist[i]),1,cvScalar(255,0,0),1,8,0);
			cvLine(hist_x, cvPoint(i, hist_x->height), cvPoint(i, hist_x->height - xhist[i]), CV_RGB(0, 0, 0), 1, 8, 0);
		}           //histogram 結束 

		ShowMatOnPicture(Matimage, this, IDC_HSV); // (hist_x, IDC_STATIC_hist);   //把水平投影同步顯示在介面上  

		// Mat Matimage = image_canny;
		
	}
}
*/

void CMFC_TT_HistogramsDlg::OnBnClickedButton5()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	

}


void CMFC_TT_HistogramsDlg::OnStnClickedHsv()
{
	// TODO:  在此加入控制項告知處理常式程式碼
}


void CMFC_TT_HistogramsDlg::OnStnClickedStatic2()
{
	// TODO:  在此加入控制項告知處理常式程式碼
}


// cvSplit(image_hsv, channelsH, channelsS, channelsV);

void CMFC_TT_HistogramsDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	Mat Matimage_Test = image_hsv;
	// vector<Mat>Matimage_Test;


	//// Hue_Bin IDC_SLIDER
	if (pScrollBar == GetDlgItem(IDC_SLIDER1))
	{
		HbinsPosition = ((CSliderCtrl*)pScrollBar)->GetPos();
		Mat Matimage_hsv = image_hsv;

		/// Use only the Hue value
		hue.create(Matimage_hsv.size(), Matimage_hsv.depth());
		int ch[] = { 0, 0 };
		mixChannels(&Matimage_hsv, 1, &hue, 1, ch, 1);

		// inRange(hue, 80, 95, H);
		threshold(hue, hueLow, Hue_BinLow, 0, THRESH_TOZERO);   // h值介於80~95  
		threshold(hueLow, hueBilateral, Hue_BinHig, 0, THRESH_TOZERO_INV);


		MatND hist ;
        MatND histBa ;
		int histSize = MAX(HbinsPosition, 2);
		float hue_range[] = { 0, 179 };
		const float* ranges = { hue_range };

		/// Get the Histogram and normalize it  (Hue) , const int Matimage_hsv[3]={0,1,2} 
		calcHist(&hue, 1, 0 , Mat(), hist, 1, &histSize, &ranges, true, false); 
		calcHist(&hueBilateral, 1, 0 , Mat(), histBa, 1, &histSize, &ranges, true, false);  //為劃出沒有取threshold的直方圖
		
		
		/// 将直方图归一化到范围 [ 0, histImage.rows ]
		normalize (hist, hist, 0, 255, NORM_MINMAX, -1, Mat());     //為劃出取threshold的BackProject 
		normalize (histBa, histBa, 0, 255, NORM_MINMAX, -1, Mat()); 

		/// Get Backprojection
		MatND backproj;
		//calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true); 
		calcBackProject(&hueBilateral, 1, 0, histBa, backproj, &ranges, 1, true); 
		 
		ShowMatOnPicture(backproj, this, IDC_STATIC);  //劃出Hue取threshold反向投影图 

		CStatic *pAlignStatus = (CStatic *)GetDlgItem(IDC_STATIC2);
		string title = /*"HbinsPosition: " +*/ to_string(HbinsPosition);
		CString ss;
		ss.Format(_T("%S"), title.c_str());
		pAlignStatus->SetWindowText(ss);


		/// Draw the histogram
		int w = 400; int h = 400;
		int bin_w = cvRound((double)w / histSize);
		Mat histImg = Mat::zeros(w, h, CV_8UC3);

		// Mat Matimage = Huehist ;  //為劃出沒有取threshold的直方圖
		Huehist = hist ;

		for (int i = 0; i < HbinsPosition; i++)
		{   /// rectangle参数为：承载的图像、顶点、对角点、颜色（这里是蓝色）、粗细、大小 
			rectangle(histImg, Point(i*bin_w, h),
				Point((i + 1)*bin_w ,h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(255, 0, 0), -1);
		}

		///Hue Bin 下限画线  
        Point LowerlimitTP = Point (Hue_BinLow*2.3,600);   
		Point LowerlimitDP =Point (Hue_BinLow*2.3,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(histImg, LowerlimitTP, LowerlimitDP ,Scalar(34,177,76),3 );  

		///Hue Bin 上限画线  
        Point UpperlimitTP = Point (Hue_BinHig*2.3,600);  
		Point UpperlimitDP =Point (Hue_BinHig*2.3,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(histImg, UpperlimitTP, UpperlimitDP ,Scalar(0,0,255),3 );  


		ShowMatOnPicture(histImg, this, IDC_Hdomain);   // 把水平投影同步顯示在介面上

	}




	////   Saturation_bin IDC_SLIDER
	if (pScrollBar == GetDlgItem(IDC_SLIDER4))
	{
		SbinsPosition = ((CSliderCtrl*)pScrollBar)->GetPos();
		// image_hsv = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
		Mat Matimage_hsv = image_hsv;   // Saturation

		/// Use only the Saturation value
		Saturation.create(Matimage_hsv.size(), Matimage_hsv.depth());
		int ch1[] = { 1, 0 };
		mixChannels(&Matimage_hsv, 1, &Saturation, 1, ch1, 1);

		// Saturation Bin Threshold 值介於75~90
		threshold(Saturation, SatLow, Sat_BinLow, 0, THRESH_TOZERO);  //S值介於75~90
		threshold(SatLow, SatBilateral, Sat_BinHig, 0, THRESH_TOZERO_INV);

		MatND Shist;
		MatND ShistBa;
		int ShistSize = MAX(SbinsPosition, 2);
		float Saturation_range[] = { 0, 255 };
		const float* Sranges = { Saturation_range };


		/// Get the Histogram and normalize it  (Saturation)
		calcHist(&Saturation, 1, 0, Mat(), Shist, 1, &ShistSize, &Sranges, true, false);
		calcHist(&SatBilateral, 1, 0, Mat(), ShistBa, 1, &ShistSize, &Sranges, true, false);

		normalize(Shist, Shist, 0, 255, NORM_MINMAX, -1, Mat());
		normalize(ShistBa, ShistBa, 0, 255, NORM_MINMAX, -1, Mat());

		/// Get Backprojection
		MatND Sbackproj;
		calcBackProject(&Saturation, 1, 0, Shist, Sbackproj, &Sranges, 1, true);
		calcBackProject(&SatBilateral, 1, 0, ShistBa, Sbackproj, &Sranges, 1, true);

		ShowMatOnPicture(Sbackproj, this, IDC_HSV);  //劃出Saturation反向投影图 


		CStatic *pAlignStatus = (CStatic *)GetDlgItem(IDC_STATIC5);
		string title = /*"SbinsPosition: " +*/ to_string(SbinsPosition);
		CString ss;
		ss.Format(_T("%S"), title.c_str());
		pAlignStatus->SetWindowText(ss);

		/// Draw the histogram
		int S_w = 400; int S_h = 400;
		int Sbin_w = cvRound((double)S_w / ShistSize);
		Mat ShistImg = Mat::zeros(S_w, S_h, CV_8UC3);

		Saturationhist = Shist ;

		for (int i = 0; i < SbinsPosition; i++)
		{
			rectangle(ShistImg, Point(i*Sbin_w, S_h),
				Point((i + 1)*Sbin_w, S_h - cvRound(Shist.at<float>(i)*S_h / 255.0)), Scalar(0, 0, 255), -1);
		}

		///Saturation Bin 下限画线  
        Point LowerlimitTP = Point (Sat_BinLow*1.56,600);   
		Point LowerlimitDP =Point (Sat_BinLow*1.56,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(ShistImg, LowerlimitTP, LowerlimitDP ,Scalar(34,177,76),3 );  

		///Saturation Bin 上限画线  
        Point UpperlimitTP = Point (Sat_BinHig*1.56,600);  
		Point UpperlimitDP =Point (Sat_BinHig*1.56,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(ShistImg, UpperlimitTP, UpperlimitDP ,Scalar(255,0,0),3 );  

		ShowMatOnPicture(ShistImg, this, IDC_Sdomain);   //把水平投影同步顯示在介面上


	}

	////  Hue 區間下限
	if (pScrollBar == GetDlgItem(IDC_SLIDER5))
	{
		 Hue_BinLow = ((CSliderCtrl*)pScrollBar)->GetPos();
		 /////////////////////////////////////////////////////////////////////////////////////////////////
		 Mat Matimage_hsv = image_hsv;
		 /// Use only the Hue value
		 hue.create(Matimage_hsv.size(), Matimage_hsv.depth());
		 int ch[] = { 0, 0 };
		 mixChannels(&Matimage_hsv, 1, &hue, 1, ch, 1);
		 
		 // Hue Bin Threshold 值介於80~95
		 // Mat hueLow, hueBilateral;
		 threshold(hue, hueLow, Hue_BinLow, 0, THRESH_TOZERO);  //h值介於80~95  
		 threshold(hueLow, hueBilateral, Hue_BinHig, 0, THRESH_TOZERO_INV);

		 // inRange(hue, 80, 95, H);

		 MatND hist ;

		 int histSize = MAX(HbinsPosition, 2);
		 float hue_range[] = { 0, 180 };
		 const float* ranges = { hue_range };


		 /// Get the Histogram and normalize it  (Hue)
		 calcHist(&hueBilateral, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
		 //calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
		 normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());


		 /// Get Backprojection
		 MatND backproj;
		 calcBackProject(&hueBilateral, 1, 0, hist, backproj, &ranges, 1, true);
		 //calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);
		 // Mat Matimage = backproj; 
		 ShowMatOnPicture(backproj, this, IDC_STATIC);  //劃出 Hue反向投影图 


		CStatic *pAlignStatus = (CStatic *)GetDlgItem(IDC_STATIC8);
		string title = /*"Hue_BinLow: " +*/ to_string(Hue_BinLow);
		CString ss;
		ss.Format(_T("%S"), title.c_str());
		pAlignStatus->SetWindowText(ss);
		////////////////////////////////////////////////////////////////////////////////////////////////

		/// Draw the histogram
		int w = 400; int h = 400;
		int bin_w = cvRound((double)w / histSize);
		Mat histImg = Mat::zeros(w, h, CV_8UC3);

		for (int i = 0; i < HbinsPosition; i++)
		{   /// rectangle参数为：承载的图像、
			rectangle(histImg, Point(i*bin_w, h),  /// 顶点
				Point((i + 1)*bin_w, h - cvRound(Huehist.at<float>(i)*h / 255.0)), /// 对角点
				Scalar(255, 0, 0), -1); /// 颜色（这里是蓝色）、粗细、大小 
		}

		///Hue Bin 下限画线  
        Point LowerlimitTP = Point (Hue_BinLow*2.3,600);   
		Point LowerlimitDP =Point (Hue_BinLow*2.3,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(histImg, LowerlimitTP, LowerlimitDP ,Scalar(34,177,76),3 );  

		///Hue Bin 上限画线  
        Point UpperlimitTP = Point (Hue_BinHig*2.3,600);  
		Point UpperlimitDP =Point (Hue_BinHig*2.3,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
		line(histImg, UpperlimitTP, UpperlimitDP ,Scalar(0,0,255),3 );  

		Mat Matimage2 = histImg;
		ShowMatOnPicture(histImg, this, IDC_Hdomain); //// 把水平投影同步顯示在介面上

		///////////////////////////////////////////////////////////////////////////////////////////////
	}


	////  Hue 區間上限
	if (pScrollBar == GetDlgItem(IDC_SLIDER6))
	{
		Hue_BinHig = ((CSliderCtrl*)pScrollBar)->GetPos();

		/////////////////////////////////////////////////////////////////////////////////////////////
		Mat Matimage_hsv = image_hsv;
		/// Use only the Hue value
		hue.create(Matimage_hsv.size(), Matimage_hsv.depth());
		int ch[] = { 0, 0 };
		mixChannels(&Matimage_hsv, 1, &hue, 1, ch, 1);

		// Hue Bin Threshold 值介於80~95
		// Mat hueLow, hueBilateral;
		threshold(hue, hueLow, Hue_BinLow, 0, THRESH_TOZERO);  //h值介於80~95  THRESH_TOZERO_INV
		threshold(hueLow, hueBilateral, Hue_BinHig, 0, THRESH_TOZERO_INV);

		// inRange(hue, 80, 95, H);

		MatND hist;
		int histSize = MAX(HbinsPosition, 2);
		float hue_range[] = { 0, 180 };
		const float* ranges = { hue_range };

		/// Get the Histogram and normalize it  (Hue)
		calcHist(&hueBilateral, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
		normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

		/// Get Backprojection
		MatND backproj;
		calcBackProject(&hueBilateral, 1, 0, hist, backproj, &ranges, 1, true);

		Mat Matimage = backproj;
		ShowMatOnPicture(Matimage, this, IDC_STATIC);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		CStatic *pAlignStatus = (CStatic *)GetDlgItem(IDC_STATIC9); 
		string title = /*"Hue_BinHig: " +*/ to_string(Hue_BinHig);
		CString ss;
		ss.Format(_T("%S"), title.c_str());
		pAlignStatus->SetWindowText(ss);
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Draw the histogram
		int w = 400; int h = 400;
		int bin_w = cvRound((double)w / histSize);
		Mat histImg = Mat::zeros(w, h, CV_8UC3);

		for (int i = 0; i < HbinsPosition; i++)
		{
			rectangle(histImg, Point(i*bin_w, h),
				Point((i + 1)*bin_w, h - cvRound(Huehist.at<float>(i)*h / 255.0)), Scalar(255, 0, 0), -1);
		}

		///Hue Bin 下限画线  
        Point LowerlimitTP = Point (Hue_BinLow*2.3,600);   
		Point LowerlimitDP =Point (Hue_BinLow*2.3,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(histImg, LowerlimitTP, LowerlimitDP ,Scalar(34,177,76),3 );  

		///Hue Bin 上限画线  
        Point UpperlimitTP = Point (Hue_BinHig*2.3,600);  
		Point UpperlimitDP =Point (Hue_BinHig*2.3,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
		 line(histImg, UpperlimitTP, UpperlimitDP ,Scalar(0,0,255),3 );  

		ShowMatOnPicture(histImg, this, IDC_Hdomain);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	////  Saturation 區間下限 
	if (pScrollBar == GetDlgItem(IDC_SLIDER7))

	{
		Sat_BinLow = ((CSliderCtrl*)pScrollBar)->GetPos();
		
		Mat Matimage_hsv = image_hsv;
		/// Use only the Saturation value
		Saturation.create(Matimage_hsv.size(), Matimage_hsv.depth());
		int ch1[] = { 1, 0 };
		mixChannels(&Matimage_hsv, 1, &Saturation, 1, ch1, 1);

		// Saturation Bin Threshold 值介於75~90
		// Mat SatLow, SatBilateral;
		threshold(Saturation, SatLow, Sat_BinLow, 0, THRESH_TOZERO);  //S值介於75~90
		threshold(SatLow, SatBilateral, Sat_BinHig, 0, THRESH_TOZERO_INV);

		// inRange(Sat, 75, 90, H);

		MatND Shist;
		int ShistSize = MAX(SbinsPosition, 2);
		float Saturation_range[] = { 0, 255 };
		const float* Sranges = { Saturation_range };

		/// Get the Histogram and normalize it  (Saturation)
		calcHist(&SatBilateral, 1, 0, Mat(), Shist, 1, &ShistSize, &Sranges, true, false);
		normalize(Shist, Shist, 0, 255, NORM_MINMAX, -1, Mat());

		/// Get Backprojection
		MatND Sbackproj;
		calcBackProject(&SatBilateral, 1, 0, Shist, Sbackproj, &Sranges, 1, true);

		Mat Matimage = Sbackproj;
		ShowMatOnPicture(Matimage, this, IDC_HSV);

		CStatic *pAlignStatus = (CStatic *)GetDlgItem(IDC_STATIC10);
		string title = /*"Hue_BinHig: " +*/ to_string(Sat_BinLow);
		CString ss;
		ss.Format(_T("%S"), title.c_str());
		pAlignStatus->SetWindowText(ss);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Draw the histogram
		int S_w = 400; int S_h = 400;
		int Sbin_w = cvRound((double)S_w / ShistSize);
		Mat ShistImg = Mat::zeros(S_w, S_h, CV_8UC3);

		for (int i = 0; i < SbinsPosition; i++)
		{
			rectangle(ShistImg, Point(i*Sbin_w, S_h),
				Point((i + 1)*Sbin_w, S_h - cvRound(Saturationhist.at<float>(i)*S_h / 255.0)), Scalar(0, 0, 255), -1);
		}

		///Saturation Bin 下限画线  
        Point LowerlimitTP = Point (Sat_BinLow*1.56,600);   
		Point LowerlimitDP =Point (Sat_BinLow*1.56,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(ShistImg, LowerlimitTP, LowerlimitDP ,Scalar(34,177,76),3 );  

		///Saturation Bin 上限画线  
        Point UpperlimitTP = Point (Sat_BinHig*1.56,600);  
		Point UpperlimitDP =Point (Sat_BinHig*1.56,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(ShistImg, UpperlimitTP, UpperlimitDP ,Scalar(255,0,0),3 );  

		ShowMatOnPicture(ShistImg, this, IDC_Sdomain);
	}


	////  Saturation 區間上限
	if (pScrollBar == GetDlgItem(IDC_SLIDER8))
	{
		Sat_BinHig = ((CSliderCtrl*)pScrollBar)->GetPos();

		Mat Matimage_hsv = image_hsv;

		/// Use only the Saturation value
		Saturation.create(Matimage_hsv.size(), Matimage_hsv.depth());
		int ch1[] = { 1, 0 };
		mixChannels(&Matimage_hsv, 1, &Saturation, 1, ch1, 1);

		// Saturation Bin Threshold 值介於75~90
		// Mat SatLow, SatBilateral;
		threshold(Saturation, SatLow, Sat_BinLow, 0, THRESH_TOZERO);  //S值介於75~90
		threshold(SatLow, SatBilateral, Sat_BinHig, 0, THRESH_TOZERO_INV);

		// inRange(Sat, 75, 90, H);

		MatND Shist;
		int ShistSize = MAX(SbinsPosition, 2);
		float Saturation_range[] = { 0, 255 };
		const float* Sranges = { Saturation_range };

		/// Get the Histogram and normalize it  (Saturation)
		calcHist(&SatBilateral, 1, 0, Mat(), Shist, 1, &ShistSize, &Sranges, true, false);
		normalize(Shist, Shist, 0, 255, NORM_MINMAX, -1, Mat());

		/// Get Backprojection
		MatND Sbackproj;
		calcBackProject(&SatBilateral, 1, 0, Shist, Sbackproj, &Sranges, 1, true);

		Mat Matimage = Sbackproj;
		ShowMatOnPicture(Matimage, this, IDC_HSV);

		CStatic *pAlignStatus = (CStatic *)GetDlgItem(IDC_STATIC11);
		string title = /*"Hue_BinHig: " +*/ to_string(Sat_BinHig);
		CString ss;
		ss.Format(_T("%S"), title.c_str());
		pAlignStatus->SetWindowText(ss);

		/// Draw the histogram
		int S_w = 400; int S_h = 400;
		int Sbin_w = cvRound((double)S_w / ShistSize);
		Mat ShistImg = Mat::zeros(S_w, S_h, CV_8UC3);

		for (int i = 0; i < SbinsPosition; i++)
		{
			rectangle(ShistImg, Point(i*Sbin_w, S_h),
				Point((i + 1)*Sbin_w, S_h - cvRound(Saturationhist.at<float>(i)*S_h / 255.0)), Scalar(0, 0, 255), -1);
		}
		///Saturation Bin 下限画线  
        Point LowerlimitTP = Point (Sat_BinLow*1.56,600);   
		Point LowerlimitDP =Point (Sat_BinLow*1.56,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(ShistImg, LowerlimitTP, LowerlimitDP ,Scalar(34,177,76),3 );  

		///Saturation Bin 上限画线  
        Point UpperlimitTP = Point (Sat_BinHig*1.56,600);  
		Point UpperlimitDP =Point (Sat_BinHig*1.56,0) ;
        ///参数为：承载的图像、起始点、结束点、颜色、粗细、线型  
        line(ShistImg, UpperlimitTP, UpperlimitDP ,Scalar(255,0,0),3 );  

		ShowMatOnPicture(ShistImg, this, IDC_Sdomain);
	}



	/////
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CMFC_TT_HistogramsDlg::OnBnClickedButton6()
{
	// TODO:  在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	Mat Matimage_Test = image_hsv;
	// vector<Mat>Matimage_Test;

	// cvSplit(image_hsv, channelsH, channelsS, channelsV,0);
	Mat Test2 ,Test3;

	// double threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)

	Mat Matimage_h = image_hsv;

	/// Use only the Hue value
	hue.create(Matimage_h.size(), Matimage_h.depth());
	int ch[] = { 0, 0 };
	mixChannels(&Matimage_h, 1, &hue, 1, ch, 1);

	threshold(hue, Test2, Hue_BinLow, 0, THRESH_TOZERO);  //h值介於80~95  THRESH_TOZERO_INV
	threshold(Test2, Test3, Hue_BinHig, 0, THRESH_TOZERO_INV);

	// inRange(hue, 80, 95, H);
	//二值化：h值介於80~95 

	MatND hist;
	int histSize = MAX(HbinsPosition, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	/// Get the Histogram and normalize it  (Hue)
	calcHist(&Test3, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	/// Get Backprojection
	MatND backproj;
	calcBackProject(&Test3, 1, 0, hist, backproj, &ranges, 1, true);

	Mat Matimage = backproj;
	ShowMatOnPicture(Matimage, this, IDC_STATIC);


	/// Draw the histogram
	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	for (int i = 0; i < HbinsPosition; i++)
	{
		rectangle(histImg, Point(i*bin_w, h),
			Point((i + 1)*bin_w, h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(0, 0, 255), -1);
	}

	//imshow("Histogram", histImg);

	Mat Matimage2 = histImg;
	ShowMatOnPicture(histImg, this, IDC_Hdomain);

}


void CMFC_TT_HistogramsDlg::OnBnClickedButton7()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	// inRange(hueBilateral, Hue_BinLow, Hue_BinHig, H);

	Mat dstImage = Mat::zeros(hueBilateral.rows, hueBilateral.cols, CV_8UC3); //為了濾掉其他顏色

	vector<vector<Point > > contours;
	vector<Vec4i > hierarchy;
	findContours(hueBilateral ,//輸入圖
		contours, //輪廓組數
		hierarchy, CV_RETR_CCOMP , CV_CHAIN_APPROX_SIMPLE); // two-level hierarchy = CV_RETR_CCOMP
	std::cout<<"共有多少組輪廓："<<contours.size()<<"組"<<std::endl; 

	//
	int cmin = 100;  
    int cmax = 1000;  
    std::vector<std::vector<Point>>::const_iterator itc = contours.begin();  
    while(itc != contours.end())  
     {  
      if(itc->size() < cmin || itc->size() > cmax)  
        itc = contours.erase(itc);  
      else  
        ++itc;  
     }  
	//

	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dstImage, contours, index, color, CV_FILLED, 8, hierarchy); //color

		imshow("圖", dstImage);
		
	}

}
