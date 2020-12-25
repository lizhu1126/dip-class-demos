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

	int method = DEMO_METHOD;

	if (method == 0) {
		//手写模板匹配

	}
	else if (method == 1) {
		//cam shift
		templateMatching_demo();
	}
	else if (method == 2) {
		opticalFlow_demo();
	}




	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");
    return 0;
}

