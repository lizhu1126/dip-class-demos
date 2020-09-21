// dip-class-demos.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());

	//基本图形的绘制

	//绘制直线
	//drawLines();

	//绘制矩形
	//drawRectangles();

	//绘制圆形
	//drawCircles();

	//绘制椭圆，或圆弧
	//drawEllipse();

	//绘制标记
	//drawMarkers();

	//字符
	writeText();

	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");
    return 0;
}

