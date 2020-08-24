#include <opencv.hpp>
#include "function.h"

using namespace cv;
using namespace std;



//第四周 练习1  图像形态学
void morphology()
{
	//读取图片并转化为灰度图
	Mat srcMat = imread("d:\\coin.png",0);

	//判断读取图片是否失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}


	//定义图像容器
	Mat thresh_Mat;
	Mat dilate_Mat;
	Mat erode_Mat;
	Mat open_Mat;
	Mat close_Mat;

	//二值化
	threshold(srcMat, thresh_Mat, 100, 255, THRESH_OTSU);

	//定义结构元素
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

	//腐蚀
	erode(thresh_Mat, erode_Mat, element, Point(-1,-1),1);

	//膨胀
	dilate(thresh_Mat, dilate_Mat, element, Point(-1, -1), 1);

	//开运算
	morphologyEx(thresh_Mat, open_Mat, MORPH_OPEN, element, Point(-1, -1), 1);

	// 闭运算
	morphologyEx(thresh_Mat, close_Mat, MORPH_CLOSE, element, Point(-1, -1), 1);


	//显示结果
	imshow("thresh_Mat", thresh_Mat);
	imshow("erode_Mat", erode_Mat);
	imshow("dilate_Mat", dilate_Mat);
	imshow("open_Mat", open_Mat);
	imshow("close_Mat", close_Mat);
	waitKey(0);
}

//第四周练习2：连通域标记
void connectedwithstats()
{
	//读取图片并转化为灰度图
	Mat srcMat = imread("d:\\coin.png");

	//判断读取图片是否失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	//转化为灰度图
	Mat gryMat;
	cvtColor(srcMat, gryMat, COLOR_BGRA2GRAY);

	//定义图像容器
	Mat stats;
	Mat centroids;
	Mat labels;
	Mat thresh_Mat;

	//大津法处理图像
	threshold(gryMat, thresh_Mat, 100, 255, THRESH_OTSU);
	
	//进行连通域标记
	int nComp = connectedComponentsWithStats(thresh_Mat, labels, stats, centroids, 8, CV_32S);

	//减去背景0，并输出
	cout << "硬币个数为：" << nComp - 1 << endl;

	//对识别出的连通域加最小外接边框
	for (int i = 1;i < nComp;i++)
	{
		Rect bandbox;
		bandbox.x = stats.at<int>(i, 0);
		bandbox.y = stats.at<int>(i, 1);

		bandbox.width = stats.at<int>(i, 2);
		bandbox.height = stats.at<int>(i, 3);

		rectangle(thresh_Mat, bandbox, 255, 1, 8, 0);
	}
	
}







//第四周练习3 原点计数
void origincount()
{
	//读取图片并转化为灰度图
	Mat srcMat = imread("d:\\1.jpg");

	//判断读取图片是否失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	//转化为灰度图
	Mat gryMat;
	cvtColor(srcMat, gryMat, COLOR_BGRA2GRAY);



	//反色
	gryMat = 255 - gryMat;

	Mat stats;
	Mat centroids;
	Mat labels;
	Mat thresh_Mat;
	Mat erode_Mat;

	//大津法处理图像
	threshold(gryMat, thresh_Mat, 100, 255, THRESH_OTSU);


	//定义结构元素
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

	//对图像进行腐蚀处理，消除掉线
	erode(thresh_Mat, erode_Mat, element, Point(-1, -1), 2);



	//进行连通域标记
	int nComp = connectedComponentsWithStats(erode_Mat, labels, stats, centroids, 8, CV_32S);

	//减去背景0，并输出
	cout << "原点个数为：" << nComp - 1 << endl;

}




//第四周练习4 回型针计数
void clipcount()
{
	//读取图片并转化为灰度图
	Mat srcMat = imread("d:\\clip.png");

	//判断读取图片是否失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	//转化为灰度图
	Mat gryMat;
	cvtColor(srcMat, gryMat, COLOR_BGRA2GRAY);

	//反色
	gryMat = 255 - gryMat;

	Mat stats;
	Mat centroids;
	Mat labels;
	Mat thresh_Mat;
	Mat open_Mat;

	//大津法处理图像
	threshold(gryMat, thresh_Mat, 100, 255, THRESH_OTSU);


	//定义结构元素
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

	//对图像进行开运算处理，消除一些杂点
	morphologyEx(thresh_Mat, open_Mat, MORPH_OPEN, element, Point(-1, -1), 1);



	//进行连通域标记
	int nComp = connectedComponentsWithStats(open_Mat, labels, stats, centroids, 8, CV_32S);


	//比较长宽比，筛选掉干扰连通域
	for (int i = 1;i < nComp;i++)
	{
		int width = stats.at<int>(i, 2);
		int height = stats.at<int>(i, 3);
		int ratio =  height/ width;
		if (ratio > 10)
		{
			nComp--;
		}
	}

	//减去背景0，并输出
	cout << "回型针个数为：" << nComp - 1 << endl;
	
}