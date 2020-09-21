#include <opencv.hpp>
#include "function.h"

using namespace cv;
using namespace std;


/***************************************************************************************************************************
								第6周练习1：利用canny算子进行边缘提取
****************************************************************************************************************************/

void canny_extracrtion()
{

	//打开摄像头
	VideoCapture cap;
	cap.open(0);

	//判断摄像头是否打开
	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return;

	}

	//读取当前帧照片
	Mat frame;
	cap.read(frame);


	//定义图片容器
	Mat dx;
	Mat dy;
	Mat canny_Mat1;
	Mat canny_Mat2;
	Mat gry_Mat;


	//通过sobel算子得到x、y方向上的梯度
	/************************************************
	sobel（） 函数模型：
	sobel( src,dx/dy,CV_16SC1,1,0,3);

	参数介绍：
	. src：Mat类的输入图像
	. dx/dy：x/y方向上的梯度
	. CV_16SC1：输出的格式
	. 1，0表示对x或者对y方向求微分的次数
	. 3表示sobel核的大小
	**************************************************/
	Sobel(frame, dx, CV_16S, 1, 0, 3);
	Sobel(frame, dy, CV_16S, 0, 1, 3);

	//进行sobel边缘提取
	/************************************************
	Canny（） 函数模型：
	Canny(InputArray dx, InputArray dy,
					     OutputArray edges,
				         double threshold1, double threshold2,
						 bool L2gradient = false);

	参数介绍：
	. InputArray dx/InputArray dy：输入图像x/y方向上的梯度
	. dx/dy：x/y方向上的梯度
	. OutputArray edges：输出边缘图像，单通道，8bit；
	. double threshold1：表示阈值1
	. double threshold2：表示阈值2
	. bool L2gradient:是否采用更精确的方式计算图像梯度
	**************************************************/
	
	Canny(dx, dy, canny_Mat1, 20, 60);
	
	//转化为灰度图，在进行边缘提取
	cvtColor(frame, gry_Mat, COLOR_BGR2GRAY);

	/************************************************
	Canny（） 函数模型：
	Canny( InputArray image, OutputArray edges,
                         double threshold1, double threshold2,
                         int apertureSize = 3, bool L2gradient = false );

	参数介绍：
	. InputArray image：输入图像，单通道8位图像
	. OutputArray edges：输出边缘图像，单通道，8bit；
	. double threshold1：表示阈值1
	. double threshold2：表示阈值2
	. int apertureSize: Sobel算子大小
	. bool L2gradient: 是否采用更精确的方式计算图像梯度
	**************************************************/
	Canny(gry_Mat,canny_Mat2, 20, 60);


	imshow("canny_Mat2", canny_Mat2);
	imshow("canny_Mat1", canny_Mat1);

	waitKey(30);

}

/****************************************************************************************************************************
								第6周练习2、3、4 旋转、缩放以及仿射变换 投影变换
*****************************************************************************************************************************/

void warpaffine()
{
	//读取图片
	cv::Mat srcMat = cv::imread("d:\\lena.jpg");

	//判断图片是否读取成功
	if (srcMat.empty()) return;

	/**************************************************旋转及缩放*****************************************/

	//初始化旋转角度以及缩放尺度
	auto angle{ -10.0 };
	float scale = 1;

	
	//设置旋转中心
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);

	//获得变换矩阵
	/************************************************
	getRotationMatrix2D（） 函数模型：
	getRotationMatrix2D( Point2f center, double angle, double scale );

	参数介绍：
	. Point2f center：Point2f类型的center，表示旋转的中心点
	. double angle：表示旋转的角度
	. double scale：图像缩放因子

	**************************************************/
	const cv::Mat affine_matrix_zoom = cv::getRotationMatrix2D(center, angle, scale);


	//定存放结果的图像容器
	cv::Mat dstMat;

	//利用仿射变换函数
	/************************************************
	warpAffine（） 函数模型：
	warpAffine( InputArray src, OutputArray dst,
                              InputArray M, Size dsize,
                              int flags = INTER_LINEAR,
                              int borderMode = BORDER_CONSTANT,
                              const Scalar& borderValue = Scalar());

	参数介绍：
	. InputArray src：输入图像，Mat类对象即可
	. OutputArray dst：输出图像，需要和原图片有一样的尺寸和类型
	. InputArray M：2*3的变换矩阵
	. Size dsize：Size类型的dsize表示输出图像的尺寸
	. int flags：int类型的flag，插值方法的标识符
	. int borderMode:边界像素模式
	. const Scalar& borderValue:恒定边界下取的值

	**************************************************/
	cv::warpAffine(srcMat, dstMat, affine_matrix_zoom, srcMat.size());

	

	/**************************************************仿射变换部分*****************************************/


	Mat affine_Mat;

	//变换前3点坐标
	const cv::Point2f src_pt[] = {
		  cv::Point2f(200,200),
		  cv::Point2f(250,200),
		  cv::Point2f(200,100),
	};

	//变换后3点坐标
	const cv::Point2f warp_pt[] = {
		  cv::Point2f(300,100),
		  cv::Point2f(300,50),
		  cv::Point2f(200,100),
	};

	//计算仿射变换后的矩阵
	//获得变换矩阵
	/************************************************
	getAffineTransform（） 函数模型：
	getAffineTransform( const Point2f src[], const Point2f dst[] );

	参数介绍：
	. const Point2f src[]：原始图像的点
	. const Point2f dst[]：目标图像的点

	**************************************************/
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, warp_pt);

	cv::warpAffine(srcMat, affine_Mat, affine_matrix, srcMat.size());


	/**************************************************投影变换部分*****************************************/
	Mat perspective_Mat;


	//变换前4点坐标
	cv::Point2f pts1[] = {
		cv::Point2f(150,150),
		cv::Point2f(150,300),
		cv::Point2f(350,300),
		cv::Point2f(350,150),

	};

	//变换后4点坐标
	cv::Point2f pts2[] = {
	cv::Point2f(200,150),
	cv::Point2f(200,300),
	cv::Point2f(340,270),
	cv::Point2f(340,180),
	};

	//投影变换矩阵生成(3*3)
	cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

	//投影变换
	/************************************************
	warpPerspective（） 函数模型：
	warpPerspective( InputArray src, OutputArray dst,
                                   InputArray M, Size dsize,
                                   int flags = INTER_LINEAR,
                                   int borderMode = BORDER_CONSTANT,
                                   const Scalar& borderValue = Scalar());

	参数介绍：
	. InputArray src：输入图像，Mat类对象即可
	. OutputArray dst：输出图像，需要和原图片有一样的尺寸和类型
	. InputArray M：透视的变换矩阵
	. Size dsize：Size类型的dsize表示输出图像的尺寸
	. int flags：int类型的flag，插值方法的标识符
	. int borderMode:边界像素模式
	. const Scalar& borderValue:恒定边界下取的值

	**************************************************/
	cv::warpPerspective(srcMat, perspective_Mat, perspective_matrix, srcMat.size());


	//显示所有结果
	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);
	imshow("affine_Mat", affine_Mat);
	imshow("perspective_Mat", perspective_Mat);

	waitKey(0);
}


/***************************************************************************************************************************
												第6周练习5：图像矫正
*****************************************************************************************************************************/
void imgcorrect()
{
	//读取图片
	cv::Mat  src = imread("d:\\lena_rot.jpg");

	//定义图片容器
	cv::Mat  gry_Mat; 
	Mat correct_Mat;
	cvtColor(src,gry_Mat,COLOR_BGR2GRAY);

	//找4个点，通过仿射变换矫正位置
	int height = src.rows;
	int width = src.cols;
	Point2f pst_1[4];

	//找左上角的点
	for (int j = 0;j < width;j++)
	{
		if (gry_Mat.at<uchar>(0, j) < 250)
		{
			pst_1[0] = Point2f(j, 0);
			j = width;
		}
	}

	//找右下角的点
	for (int j = width-1;j >0;j--)
	{
		if (gry_Mat.at<uchar>(height - 1, j) <250)
			pst_1[1] = Point2f(static_cast<float>(j), static_cast<float>(height - 1)), j = 0;
	}


	//找左下角的点
	for (int i = height-1;i >0;i--)
	{
		if (gry_Mat.at<uchar>(i, 0) <250)
			pst_1[2] = Point2f(0, static_cast<float>(i)), i = 0;
	}

	//找右上角的点
	for (int i = 0;i < height;i++)
	{
		if (gry_Mat.at<uchar>(i, width - 1) < 250)
			pst_1[3] = Point2f(static_cast<float>(width - 1), static_cast<float>(i)), i = height;
	}


	//变换后的4个点
	Point2f pst_2[4]{ Point2f(0,0),Point2f(static_cast<float>(width - 1),static_cast<float>(height - 1)),Point2f(0,static_cast<float>(height - 1)),Point2f(static_cast<float>(width - 1),0) };
	
	//计算投影变换矩阵
	const Mat Matrix = cv::getPerspectiveTransform(pst_1, pst_2);

	//进行投影变换
	cv::warpPerspective(src, correct_Mat, Matrix, src.size());


	imshow("src", src);
	imshow("correct_Mat", correct_Mat);
	waitKey(0);

}

