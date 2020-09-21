#pragma once
#include <opencv.hpp>


using namespace cv;
using namespace std;


//gamma矫正演示函数
int gammaMain();
//直方图均衡化演示函数
int equalizeMain();



//gamma矫正功能函数
int gammaCorrection(cv::Mat srcMat, cv::Mat & dstMat, float gamma);


//直方图功能函数
int drawIntenHist(cv::Mat & histMat, float * srcHist, int bin_width, int bin_heght);
int calcIntenHist(const cv::Mat src, float * dstHist);
