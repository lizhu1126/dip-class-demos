// dip-class-demos.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

//OpenCV中的mat的基本操作demo
int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());

	//读取图片
	//readImage();

	//读取视频,以及打开摄像头
	//readVideo();

	//读取图像序列	
	//readSequence();

	//Mat的创建
	//createMat();

	//Mat的复制方法
	//copyMat();


	//Mat的基本运算
	//calcMat();

	//基本的线性代数操作
	//calcLinearAlg();

	//利用Mat求解线性方程
	//solveLinearEquations();

	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");
    return 0;
}

