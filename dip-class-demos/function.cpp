#include <opencv.hpp>
#include "function.h"
using namespace cv;
using namespace std;


/***************************************************************************************************************************
												第7周练习1：改进图片旋转
*****************************************************************************************************************************/
void spin_correct()
{
	cv::Mat srcMat = cv::imread("d:\\lena.jpg");

	//判断图片是否读取成功
	if (srcMat.empty()) return;

	//初始化旋转角度以及缩放尺度
	auto angle{ -10.0 };
	float scale = 1;


	//设置旋转中心
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);


	//获得变换矩阵																						
	Mat rot = getRotationMatrix2D(center, angle, scale);

	//获取外接四边形
	Rect bbox = RotatedRect(center, srcMat.size(), angle).boundingRect();


	//调整仿射矩阵参数
	rot.at < double >(0, 2) += bbox.width / 2.0 - center.x;
	rot.at < double >(1, 2) += bbox.height / 2.0 - center.y;


	//定存放结果的图像容器
	cv::Mat dstMat;

	//利用仿射变换函数
	cv::warpAffine(srcMat, dstMat, rot, bbox.size());

	cv::waitKey(0);
}


/******************************************************************************************************************************
												第7周练习2-3：霍夫变换的使用
*****************************************************************************************************************************/

/**********************************************标准霍夫变换****************************************/
void houghDemo()
{
	Mat srcMat = cv::imread("d:\\img.png");

	//判断图像读取是否成功
	if (srcMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return;
	}
	//定义图片容器
	Mat cannyMat;
	cv::Mat dx;
	cv::Mat dy;
	Mat lineMat;

	//canny函数边缘检测
	Sobel(srcMat, dy, CV_16SC1, 0, 2, 3);
	Sobel(srcMat, dx, CV_16SC1, 1, 0, 3);
	Canny(dx, dy, cannyMat, 60,180);

	//进行霍夫变换
	/************************************************
	HoughLines（） 函数模型：
	HoughLines( InputArray image, OutputArray lines,
                              double rho, double theta, int threshold,
                              double srn = 0, double stn = 0,
                              double min_theta = 0, double max_theta = CV_PI );

	参数介绍：
	. InputArray image：InputArray类型的image，输入8bit、单通道
	. OutputArray lines：InputArray类型的lines，经过调用HoughLines函数后储存了霍夫线变换检测到线条的输出矢量
	. double rho：double类型的rho，以像素为单位的距离精度
	. double theta: double类型的theta，以弧度为单位的角度精度
	. int threshold: int类型的threshold，累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值
	. double srn: double类型的srn，有默认值0
	. double stn: double类型的stn，有默认值0，对于多尺度霍夫变换，srn表示第四个参数进步尺寸的单位角度theta的除数距离
	. double min_theta: double类型的 min_theta，对于标准和多尺度Hough变换，检查线条的最小角度
	. double max_theta: double类型的 max_theta, 对于标准和多尺度Hough变换，检查线条的最大角度

	**************************************************/
	cv::HoughLines(cannyMat, lineMat, 1, CV_PI / 180, 55);


	//取出lineMat中存的线的信息
	int height = lineMat.rows;
	int width = lineMat.cols;

	//在原图上画线
	for (int i = 0;i < height;i++)
	{
		for (int j = 0;j < width;j++)
		{

			//读取ρ和theta
			float rho = lineMat.at<Vec3f>(i, j)[0], theta = lineMat.at<Vec3f>(i, j)[1];
			cv::Point pt1, pt2;
			double a = cos(theta);
			double b = sin(theta);
			double x0 = a*rho;
			double y0 = b*rho;


			//求点的坐标，saturate_cast防止数据溢出
			pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
			pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
			pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
			pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));

			//画线
			cv::line(srcMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
		}
	}

	imshow("srcMat", srcMat);
	cv::waitKey(0);
}

/**********************************************累计概率霍夫变换****************************************/
void houghsp_demo()
{
	Mat srcMat = cv::imread("d:\\img.png");

	//判断图像读取是否成功
	if (srcMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return;
	}
	//定义图片容器
	Mat gryMat;
	Mat cannyMat;
	Mat linesp_Mat;

	//转化为灰度图
	cvtColor(srcMat, gryMat, COLOR_BGR2GRAY);
	Canny(gryMat, cannyMat, 60, 180, 3);

	//进行霍夫变换
	/************************************************
	HoughLines（） 函数模型：
	HoughLinesP( InputArray image, OutputArray lines,
                               double rho, double theta, int threshold,
                               double minLineLength = 0, double maxLineGap = 0 );

	参数介绍：
	. InputArray image：InputArray类型的image，输入8bit、单通道
	. OutputArray lines：InputArray类型的lines，经过调用HoughLinesP函数后后存储了检测到的线条的输出矢量，每一条线由具有四个元素的矢量(x_1,y_1, x_2, y_2）  表示，其中，(x_1, y_1)和(x_2, y_2) 是是每个检测到的线段的结束点
	. double rho：double类型的rho，以像素为单位的距离精度
	. double theta: double类型的theta，以弧度为单位的角度精度
	. int threshold: int类型的threshold，累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值
	. double minLineLength: double类型的minLineLength，有默认值0，表示最低线段的长度，比这个设定参数短的线段就不能被显现出来
	. double maxLineGap: double类型的maxLineGap，有默认值0，允许将同一行点与点之间连接起来的最大的距离

	**************************************************/
	HoughLinesP(cannyMat, linesp_Mat, 1, CV_PI / 180, 22,10 ,10);
	int heightsp = linesp_Mat.rows;
	int widthsp = linesp_Mat.cols;


	//在原图上画线
	for (int i = 0;i < heightsp;i++)
	{
		for (int j = 0;j < widthsp;j++)
		{

			Point p1, p2;
			p1.x = linesp_Mat.at<Vec4i>(i, j)[0];
			p1.y = linesp_Mat.at<Vec4i>(i, j)[1];
			p2.x = linesp_Mat.at<Vec4i>(i, j)[2];
			p2.y = linesp_Mat.at<Vec4i>(i, j)[3];

			cv::line(srcMat, p1, p2, cv::Scalar(255, 255, 0), 1, 8, 0);
		}
	}

	imshow("srcMat", srcMat);
	waitKey(0);
}

