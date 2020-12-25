// dip-class-demos.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"
#include "parameters.h"

using namespace cv;
using namespace std;

int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());

	int demo_method = DEMO_METHOD;

	if (demo_method == 0) {
		//该demo验证并演示，视频中的像素灰度值变换是否呈高斯分布
		verifyGaussian();
	}
	else if(demo_method == 1) {
		//实现普通背景差分
		bgSub_demo();
	}
	else if(demo_method == 2) {
		//实现高斯建模的背景差分
		bgSubGaussian_demo();

	}
	else if (demo_method == 3) {
		//调用opencv的背景差分法demo
		opencvBgSubtrator();
	}

	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");
    return 0;
}

