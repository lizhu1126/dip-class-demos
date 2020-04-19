// dip-class-demos.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

int main()
{
	//寻找2-n范围内的质数
	int n = 50000000;
	//是否将找到的质数打印在状态栏
	bool ifPrint = false;

	//开始计时
	double start = static_cast<double>(cvGetTickCount());
	
	//00.普通的试除法(trial division)寻找质数
	pickPrime(n, ifPrint);

	//结束计时
	double pp_time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time of trial division algorithm:" << pp_time / 1000 << "ms" << endl;


	//开始计时
	double Estart = static_cast<double>(cvGetTickCount());
	//01.埃拉托斯特尼筛法(sieve of Eratosthenes)寻找质数
	EratosSieve(n,ifPrint);
	//结束计时
	double E_time = ((double)cvGetTickCount() - Estart) / cvGetTickFrequency();
	//显示时间
	cout << "processing time of Eratosthenes's algorithm:" << E_time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");
    return 0;
}

