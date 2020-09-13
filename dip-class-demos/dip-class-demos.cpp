#include<iostream>
#include<opencv2/opencv.hpp>
#include"function.h"

using namespace cv;
using namespace std;

int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());

	//处理函数
	//skinRecognition();
	//binarization();
	trackbar();

	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	cin.get();
	return 0;
}
