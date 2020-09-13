
#include<iostream>
#include<opencv2/opencv.hpp>
#include"function.h"
using namespace cv;
using std::cout;
using std::endl;

/**********************************
第三周练习1：肤色提取实验
利用不同色域物体在HSV色彩空间上的不同色域，实现对人肤色的提取
************************************/
void skinRecognition()
{
		VideoCapture cap(0);//打开0号摄像头
		double scale = 0.5;

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
			Mat detectMat;

			cap >> frame;//读取当前帧的照片

			//修改图片尺寸大小
			Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
			Mat rFrame = Mat(ResImgSiz, frame.type());
			resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

			//将原图转化为hsv类型的图片
			cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

			//对detecMat进行初始化
			frame.copyTo(detectMat);
			//利用inRange函数对图片进行hsv筛选
			cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);


			imshow("while:in the range", detectMat);
			imshow("frame", rFrame);

			waitKey(30);
		}
	
}

/**********************************
第三周练习2：
调用几种图像二值化的方法
************************************/
void binarization()
{
	//读取图片并转化为灰度图
	cv::Mat srcMat = cv::imread("d:\\timg.jpg", 0);

	//判断图片是否提取成功
	if (srcMat.empty())
	{
		cout << "fail to read !" << endl;
		return;
	}


    //定义图像容器
	cv::Mat bin_Mat;
	cv::Mat otsu_Mat;
	cv::Mat adap_Mat;


	//普通二值化方法
	threshold(srcMat, bin_Mat, 100, 255, CV_THRESH_BINARY);

	//大津法
	threshold(srcMat, otsu_Mat, 100, 255, CV_THRESH_OTSU);

	//区域自适应二值化
	adaptiveThreshold(srcMat, adap_Mat, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 10);//适合对那些光照不均的图片进行二值化，因为它的二值化阈值是自适应的

	//显示结果图像
	cv::imshow("bin_Mat", bin_Mat);
	cv::imshow("otsu_Mat", otsu_Mat);
	cv::imshow("adap_Mat", adap_Mat);
	

	cv::waitKey(0);
}

/**********************************
第三周练习3：
创建一个滑动条，可通过移动滑动条调节二值化阈值
************************************/


//回调函数
void callback(int th, void* data)
{
	//强制类型转换
	cv::Mat src = *((cv::Mat*) data);

	//定义输出图片容器
	cv::Mat dst;

	//二值化函数
	threshold(src, dst, th, 255, CV_THRESH_BINARY);
	cv::imshow("bar", dst);
}
//主函数
void trackbar()
{	
	//定义图像容器
	cv::Mat srcMat;
	cv::Mat gryMat;


	//初始化滑动条的值，并设置滑动节的调节范围
	int lowth = 30;
	int maxth = 255;
	
	//读取图片
	srcMat = cv::imread("d:\\timg.jpg");

	//判断图片读取是否成功
	if (srcMat.empty())
	{
		cout << "fail to read!" << endl;
	}

	//转化为灰度图
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);

	//显示灰度图
	namedWindow("bar");
	cv::imshow("bar", gryMat);

	//创建滑动条函数
	createTrackbar("threshold", "bar", &lowth, maxth, callback, &gryMat);
	cv::waitKey(0);

}

