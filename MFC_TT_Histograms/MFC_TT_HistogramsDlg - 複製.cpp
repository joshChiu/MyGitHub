
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

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

IplImage *image;
IplImage *image_resize = cvCreateImage(cvSize(1288,964),IPL_DEPTH_8U,3);  //把image 轉成需要的大小
IplImage *image_gray;       //灰階圖
IplImage *image_hsv;     //把灰階圖做smooth
IplImage *image_threshold;  //把smooth過的圖，用Threshold變成黑白的

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


void CMFC_TT_HistogramsDlg::DrawMatOnPicture(Mat img, UINT ID) 
{
	CStatic* pStatic = (CStatic*)GetDlgItem(ID);
	pStatic->Invalidate(true);

	CRect rect;
	GetDlgItem(ID)->GetWindowRect(&rect);
	ScreenToClient(rect);
	RedrawWindow(rect);

	CDC *m_pDC;
	m_pDC = GetDlgItem(ID)->GetDC();	// picture control
	m_pDC->SetStretchBltMode(STRETCH_HALFTONE);
	CImage	m_ShowImg;
	BYTE *pCImgPixel;
	BYTE *pImgData = (BYTE*)(img.data);
	int loc_Wimg = img.cols, loc_Himg = img.rows;
	int loc_CHNLimg = img.step.buf[1],
		loc_WSTPimg = img.step.buf[0],
		nIndex_ImgCol;

	m_ShowImg.Create(loc_Wimg,loc_Himg,(8*loc_CHNLimg));
	if(loc_CHNLimg==1)
		m_ShowImg.SetColorTable(0,256,GrayColorTable);

	pCImgPixel = (BYTE*)(m_ShowImg.GetBits());
	nIndex_ImgCol = m_ShowImg.GetPitch();

	for(int x=0;x<loc_Himg;x++)
		memcpy(&pCImgPixel[x*nIndex_ImgCol],&pImgData[x*loc_WSTPimg],loc_Wimg*loc_CHNLimg*sizeof(BYTE));
			
	int show_Wimg,show_Himg;
	if((float)loc_Wimg/rect.Width() > (float)loc_Himg/rect.Height()) //配合寬度
	{
		show_Wimg = rect.Width();
		show_Himg = int((float)loc_Himg*(show_Wimg/(float)loc_Wimg));
	}
	else //配合高度
	{
		show_Himg = rect.Height();
		show_Wimg = int((float)loc_Wimg*(show_Himg/(float)loc_Himg));
	}
		
	m_ShowImg.Draw(m_pDC->m_hDC, 0, 0, show_Wimg, show_Himg, 0, 0, loc_Wimg, loc_Himg); //印出圖片 

	m_ShowImg.Destroy();
	ReleaseDC(m_pDC);
}


  /// Function Headers
void pickPoint (int event, int x, int y, int, void* );  //打在第二題前面，讓程式先看懂他
Mat HSV;
// IplImage *HSV;


void CMFC_TT_HistogramsDlg::OnBnClickedButton1()
{         // Button 1 

// AllocConsole();
// freopen ("CONOUT$", "w", stdout );  //輸入文字資訊


   image_hsv = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
  
   cvCvtColor(image, image_hsv, COLOR_BGR2HSV );

   DrawMatOnPicture(image_hsv , IDC_HSV);


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
  Mat src, dst ,hsv;  //建一些矩阵
  Mat H,r2,S,V; //各顏色的閥值

  int bins = 25;
  Mat hue;

    /// Read the image
   src = imread ("0930.png ");
   if ( !src.data ) cout<<"Error loading src \n"<<endl;  //文字模式下輸出"Find the"字串
 
   /// Transform it to HSV
   cvtColor(src,hsv,CV_BGR2HSV); //轉成hsv平面 CV_BGR2HSV

 /// Use only the Hue value
  //hue.create( hsv.size(), hsv.depth() );
  //int ch[] = { 0, 0 };
  //mixChannels( &hsv, 1, &hue, 1, ch, 1 );



    /// 分割成3个单通道图像 ( H, S 和 V )
 vector<Mat> hsv_planes;   //Mat - 基本图像容器
 split( hsv, hsv_planes );



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
 
 imshow("Hdomain",H);
 imshow("Sdomain",S);

 namedWindow("calcHist Demo_H" , CV_WINDOW_AUTOSIZE );
 namedWindow("calcHist Demo_S", CV_WINDOW_AUTOSIZE );
 namedWindow("calcHist Demo_V", CV_WINDOW_AUTOSIZE );
 
 imshow("calcHist Demo_H" , histImage_h );
 imshow("calcHist Demo_S", histImage_s );
 imshow("calcHist Demo_V", histImage_v );

 waitKey(0);
 
///////////////////////////////////////////////
}

int HueRangePosition = 30;
int HueMovePosition = 180;
int binsPosition = 25;
int SbinsPosition = 15;


Mat hsv_planes ,H ,hsv,hue ,Saturation ,S;


void onTrackbar(int Position) {  
	
	//int Range=HueRangePosition-10;
    //int Move=HueMovePosition -10;
    // double a,b;

   //vector<Mat> hsv_planes;   //Mat - 基本图像容器
   //split(hsv, hsv_planes );

  MatND hist;
  int histSize = MAX( binsPosition, 2 );
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

  for( int i = 0; i < binsPosition; i ++ )
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
  
  Mat src, dst; //建一些矩阵
//  Mat hsv;      //轉到hsv平面
//  Mat H,r2,S,V; //各顏色的閥值

//  int bins = 25;
//  Mat hue;

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

 cvCreateTrackbar("*Huebins:","BackProj",&binsPosition, 179, onTrackbar );
 cvCreateTrackbar("*Saturationbins:","SBackProj",&SbinsPosition, 255, onTrackbar );
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

	// cvNamedWindow("w",1); image_gray秀出在DrawMatOnPicture 沒能解決
	// cvShowImage("w",image_gray);  


	DrawMatOnPicture(image , IDC_STATIC);                  //把圖顯示在介面上


}

