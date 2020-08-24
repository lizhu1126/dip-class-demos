#include<opencv2/opencv.hpp>
#include"function.h"

using namespace cv;
using namespace std;

//第五周 练习1—3 中值滤波  均值滤波 高斯滤波
void Filter()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return;

	}

	//读取当前帧照片
	Mat frame;
	cap.read(frame);


	//定义图像容器
	Mat median_Mat;
	Mat blur_Mat;
	Mat Guass_Mat;

	//中值滤波
	medianBlur(frame, median_Mat, 3);

	//均值滤波
	blur(frame, blur_Mat, Size(3, 3), Point(-1, -1));

	//高斯滤波
	GaussianBlur(frame, Guass_Mat, Size(3, 3), 1, 0);


	//显示图片
	imshow("median_Mat", median_Mat);
	imshow("blur_Mat", blur_Mat);
	imshow("Guass_Mat", Guass_Mat);
	waitKey(30);
}

//第五周练习4 边缘提取
void sobel_extracrtion()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return;

	}

	//读取当前帧照片
	Mat frame;
	cap.read(frame);

	//sobel边缘检测
	Mat sobel_Mat;
	Sobel(frame, sobel_Mat,-1, 1, 0, 5);
	imshow("sobel_Mat", sobel_Mat);
	waitKey(30);
}

//第五周练习5 磨皮程序
void Convolution_app()
{
	//第三周肤色提取程序
	VideoCapture cap(0);//打开0号摄像头

	//肤色h					
	double i_minH = 0;
	double i_maxH = 20;

	//颜色饱和度s
	double i_minS = 43;
	double i_maxS = 255;

	//颜色亮度v
	double i_minV = 55;
	double i_maxV = 255;

	while (1)
	{
		//定义图像容器
		Mat frame;
		Mat hsvMat;
		Mat maskMat;
		Mat objectMat;
		Mat guss_Mat;


		cap >> frame;//读取当前帧的照片

		//将原图转化为hsv类型的图片
		cvtColor(frame, hsvMat, COLOR_BGR2HSV);

		//对detecMat进行初始化
		frame.copyTo(maskMat);


		//利用inRange函数对图片进行hsv筛选
		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), maskMat);

		//原图拷入输出中
		frame.copyTo(objectMat);

		//对图像进行高斯滤波
		GaussianBlur(frame, guss_Mat, Size(5, 5), 3, 0);

		//高斯滤波后的人脸部分送入目标图中
		guss_Mat.copyTo(objectMat, maskMat);//从原图中取出目标图像（与运算）


		//显示结果
		imshow("磨皮前", frame);
		imshow("磨皮后", objectMat);
	
		waitKey(30);
	}
		
}