#include <opencv.hpp>
#include "function.h"
using namespace cv;
using namespace std;


/******************************************************************
第7周练习1：改进图片旋转
*******************************************************************/
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


/******************************************************************
第7周练习2-3：霍夫变换的使用
*******************************************************************/

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

