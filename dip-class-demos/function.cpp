#include<opencv2/opencv.hpp>
#include"function.h"

using namespace cv;
using namespace std;

/***************************************************************************************************************************
                                  第五周 练习1-3： 中值滤波  均值滤波 高斯滤波
***************************************************************************************************************************/

void Filter()
{
	//打开摄像头
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
	/************************************************
	medianBlur（） 函数模型：
	medianBlur( InputArray src, OutputArray dst, int ksize );

	参数介绍：
	. InputArray src：InputArray类型的src，可以是多通道的Mat类型的图像；但深度应CV_8U，CV_16U，CV_16S，CV_32F
	. OutputArray dst：OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
	. int ksize：int类型的ksize，孔径的线性尺寸（aperture linear size），注意这个参数必须是大于1的奇数

	**************************************************/

	medianBlur(frame, median_Mat, 3);





	//均值滤波
	/************************************************
	blur（） 函数模型：
	blur( InputArray src, OutputArray dst,
                        Size ksize, Point anchor = Point(-1,-1),
                        int borderType = BORDER_DEFAULT );


	参数介绍：
	. InputArray src:InputArray类型的src，可以是多通道的Mat类型的图像；但深度应CV_8U，CV_16U，CV_16S，CV_32F
	. OutputArray dst:OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
	. Size ksize:Size类型的ksize，内核的大小
	. Point anchor:Point类型的anchor，表示锚点
	. int borderType: int类型的borderType，用于推断图像外部像素的某种边界模式

	**************************************************/
	blur(frame, blur_Mat, Size(3, 3), Point(-1, -1));





	//高斯滤波
	/************************************************
	GaussianBlur（） 函数模型：
	GaussianBlur( InputArray src, OutputArray dst, Size ksize,
                                double sigmaX, double sigmaY = 0,
                                int borderType = BORDER_DEFAULT );

	参数介绍：
	. InputArray src：InputArray类型的src，可以是多通道的Mat类型的图像；但深度应CV_8U，CV_16U，CV_16S，CV_32F
	. OutputArray dst：OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
	. Size ksize：高斯核大小
	. double sigmaX, double sigmaY：X,Y方向上的高斯核标准偏差
	. int borderType：int类型的borderType，用于推断图像外部像素的某种边界模式

	**************************************************/
	GaussianBlur(frame, Guass_Mat, Size(3, 3), 1, 0);


	//显示图片
	imshow("median_Mat", median_Mat);
	imshow("blur_Mat", blur_Mat);
	imshow("Guass_Mat", Guass_Mat);
	waitKey(30);
}



/***************************************************************************************************************************
										第五周练习4：利用sobel算子进行边缘提取
***************************************************************************************************************************/
void sobel_extracrtion()
{
	//打开摄像头
	VideoCapture cap;
	cap.open(0);

	//判断是否打开摄像头
	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return;
	}

	//读取当前帧照片
	Mat frame;
	cap.read(frame);

	//sobel边缘检测
	/************************************************
	sobel（） 函数模型：
	Sobel( InputArray src, OutputArray dst, int ddepth,
                         int dx, int dy, int ksize = 3,
                         double scale = 1, double delta = 0,
                         int borderType = BORDER_DEFAULT );

	参数介绍：
	. InputArray src：InputArray 类型的src，为输入图像，填Mat类型即可
	. OutputArray dst：OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
	. int ddepth：int类型的ddepth，输出图像的深度
	. int dx, int dy：X,Y方向上的差分阶数
	. int ksize：sobel核的大小
	. double scale：double类型的scale，计算导数值时可选的缩放因子，默认值是1
	. double delta: double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0
	. int borderType：int类型的borderType，边界模式

	**************************************************/
	Mat sobel_Mat;
	Sobel(frame, sobel_Mat,-1, 1, 0, 5);

	//显示结果
	imshow("sobel_Mat", sobel_Mat);
	waitKey(30);
}



/***************************************************************************************************************************
										第五周练习5：简易人脸磨皮程序
***************************************************************************************************************************/

void Convolution_app()
{
	//打开摄像头
	VideoCapture cap(0);

	//肤色h					
	double i_minH = 0;
	double i_maxH = 20;

	//肤色颜色饱和度s
	double i_minS = 43;
	double i_maxS = 255;

	//肤色颜色亮度v
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

		//利用inRange函数对图片进行hsv筛选（选出人脸部分）
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