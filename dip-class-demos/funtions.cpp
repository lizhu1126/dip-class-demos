#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

/******************************************************************************************************************************
													blob分析，示例程序
													第八周，练习1，轮毂中的圆孔定位
*****************************************************************************************************************************/

void rimBlobAnalysis()
{

	float wh_ratio_high = 1.1;
	float wh_ratio_low = 0.9;
	float area_th = 100;

	//定义图像容器
	Mat srcMat;
	Mat bnyMat;
	Mat disMat;
	Mat sttMat;
	Mat cntMat;
	Mat lblMat;

	//读取图片
	srcMat = imread("../testImages\\rim.png");
	//读取图片失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}
	srcMat.copyTo(disMat);
	cvtColor(srcMat, srcMat, COLOR_BGR2GRAY);

	//二值化
	threshold(srcMat, bnyMat, 100, 255, THRESH_OTSU);

	//反色
	bnyMat = 255 - bnyMat;

	//连通域
	int nComp = connectedComponentsWithStats(bnyMat, lblMat, sttMat, cntMat);

	int * flag = new int[nComp];
	memset(flag, 0, sizeof(int)*nComp);

	//计算宽长比
	//0号为背景，跳过，i=1开始循环
	for (int i = 1; i < nComp; i++) {
		float width = (float)sttMat.at<int>(i, CC_STAT_WIDTH);
		float height = (float)sttMat.at<int>(i, CC_STAT_HEIGHT);
		float ratio = width / height;

		if (
			(ratio > wh_ratio_low)
			&& (ratio < wh_ratio_high)
			&& (sttMat.at<int>(i, CC_STAT_AREA) > area_th)
			)
		{
			//绘制bounding box
			Rect bbox;
			//bounding box左上角坐标
			bbox.x = sttMat.at<int>(i, 0);
			bbox.y = sttMat.at<int>(i, 1);
			//bouding box的宽和长 
			bbox.width = sttMat.at<int>(i, 2);
			bbox.height = sttMat.at<int>(i, 3);
			//绘制
			rectangle(disMat, bbox, CV_RGB(255, 255, 0), 2, 8, 0);

			//记录标签
			flag[i] = 1;
		}
	}

	//筛选出的像素上色
	for (int i = 0; i<srcMat.rows; i++)
	{
		for (int j = 0; j<srcMat.cols; j++)
		{
			int no = lblMat.at<int>(i, j);

			if (flag[no] == 1) {
				disMat.at<Vec3b>(i, j)[0] = 0;
				disMat.at<Vec3b>(i, j)[1] = 255;
				disMat.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}

	delete[] flag;

	imshow("source image", srcMat);
	imshow("binary image", bnyMat);
	imshow("hole image", disMat);

	waitKey(0);

	destroyAllWindows();

}

/******************************************************************************************************************************
											第八周，练习2，芯片定位
*****************************************************************************************************************************/
void chipBlobAnalysis()
{
	//宽敞比阈值
	float wh_ratio_high = 1.2;
	float wh_ratio_low = 0.9;

	//定义图像容器
	Mat srcMat;
	Mat bnyMat;
	Mat disMat;
	Mat sttMat;
	Mat cntMat;
	Mat lblMat;

	//读取图片
	srcMat = imread("../testImages\\die_on_chip.png");
	//读取图片失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}
	srcMat.copyTo(disMat);
	cvtColor(srcMat, srcMat, COLOR_BGR2GRAY);

	//二值化
	threshold(srcMat, bnyMat, 100, 255, THRESH_OTSU);

	//腐蚀降噪
	cv::Mat element = cv::Mat::ones(3, 3, CV_8UC1);
	erode(bnyMat, bnyMat, element, cv::Point(-1, -1));

	//通过findContours函数寻找连通域
	/************************************************
	findContours（） 函数模型：
	findContours( InputOutputArray image, OutputArrayOfArrays contours,
                              int mode, int method, Point offset = Point());

	参数介绍：
	. InputOutputArray image：image，单通道图像矩阵
	. OutputArrayOfArrays contours：contours，定义为“vector<vector<Point>> contours”，是一个向量，并且是一个双重向量
	. int mode：int型的mode，定义轮廓的检索模式
	. int method: 定义轮廓的近似方法
	. Point offset: Point偏移量，所有的轮廓信息相对于原始图像对应点的偏移量

	**************************************************/
	vector<vector<Point>> contours;
	findContours(bnyMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


	//绘制轮廓
	for (int i = 0; i < contours.size(); i++) {
		//获得最小外界四边形
		RotatedRect rbox = minAreaRect(contours[i]);

		//计算宽敞比
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float ratio = width / height;

		//条件筛选
		if (
			(ratio > wh_ratio_low)
			&& (ratio < wh_ratio_high)
			)
		{
			//绘制轮廓
			/************************************************
			drawContours（） 函数模型：
			drawContours( InputOutputArray image, InputArrayOfArrays contours,
                              int contourIdx, const Scalar& color,
                              int thickness = 1, int lineType = LINE_8,
                              InputArray hierarchy = noArray(),
                              int maxLevel = INT_MAX, Point offset = Point() );

			参数介绍：
			. InputOutputArray image：目标图像
			. InputArrayOfArrays contours：表示输入的轮廓组，每一组轮廓由点vector构成量
			. int contourIdx：指明画第几个轮廓，如果该参数为负值，则画全部轮廓
			. const Scalar& color: color为轮廓的颜色
			. int thickness: thickness为轮廓的线宽，如果为负值或CV_FILLED表示填充轮廓内部
			. int lineTyp:lineType为线型
			. InputArray hierarchy:轮廓结构信息
			. int maxLevel:maxLevel
			. Point offset:点偏移量

			**************************************************/
			drawContours(disMat, contours, i, Scalar(0, 255, 255), 1, 8);
			//获取4个顶点
			cv::Point2f vtx[4];
			rbox.points(vtx);
			//绘制4条边
			for (int i = 0; i < 4; ++i) {
				cv::line(disMat, vtx[i], vtx[i<3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}

	imshow("source image", srcMat);
	imshow("binary image", bnyMat);
	imshow("hole image", disMat);

	waitKey(0);

	destroyAllWindows();

}



/******************************************************************************************************************************
											第八周，练习3，照片中的杯盖定位
*****************************************************************************************************************************/
void libBlobAnalysis()
{
	//筛选
	int width_th = 50;
	int height_th = 50;


	//0-180
	//红色
	//第一个Hue的范围
	double i_minH = 0;
	double i_maxH = 20;
	//第二个Hue的范围
	double i_minH2 = 160;
	double i_maxH2 = 180;

	//0-255
	double i_minS = 100;
	double i_maxS = 255;
	//0-255
	double i_minV = 50;
	double i_maxV = 255;

	Mat srcMat = imread("../testImages\\lib.jpg");
	//读取图片失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	Mat hsvMat;
	Mat disMat;
	Mat rangeMat1;
	Mat rangeMat2;
	Mat bnyMat;
	Mat lblMat, sttMat, cntMat;

	//转换至hsv模式
	cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);
	srcMat.copyTo(disMat);

	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), rangeMat1);
	cv::inRange(hsvMat, Scalar(i_minH2, i_minS, i_minV), Scalar(i_maxH2, i_maxS, i_maxV), rangeMat2);

	//与运算，合并两个范围的筛选结果
	bnyMat = rangeMat1 + rangeMat2;

	//连通域
	int nComp = connectedComponentsWithStats(bnyMat, lblMat, sttMat, cntMat);

	//0号为背景，跳过，i=1开始循环
	for (int i = 1; i < nComp; i++) {
		Rect bbox;
		//bounding box左上角坐标
		bbox.x = sttMat.at<int>(i, 0);
		bbox.y = sttMat.at<int>(i, 1);
		//bouding box的宽和长 
		bbox.width = sttMat.at<int>(i, 2);
		bbox.height = sttMat.at<int>(i, 3);
		//绘制
		if (
			bbox.width > width_th
			&&	bbox.height > height_th
			)
		{
			rectangle(disMat, bbox, CV_RGB(255, 255, 0), 2, 8, 0);
		}
	}

	imshow("source image", srcMat);
	imshow("binary image", bnyMat);
	imshow("hole image", disMat);

	waitKey(0);

}