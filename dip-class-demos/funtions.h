#pragma once
#include <opencv.hpp>
#include "parameters.h"

using namespace cv;
using namespace std;

void on_mouse(int EVENT, int x, int y, int flags, void* userdata);
int drawHist(cv::Mat & histMat, float * srcHist, int bin_width, int bin_heght);
VideoCapture createInput(bool useCamera, std::string videoPath);


int verifyGaussian();
int bgSub_demo();
int bgSubGaussian_demo();
int calcGaussianBackground(std::vector<cv::Mat> srcMats,cv::Mat & meanMat,cv::Mat &varMat);
int gaussianThreshold(cv::Mat srcMat, cv::Mat meanMat, cv::Mat varMat, float weight, cv::Mat &dstMat);

int opencvBgSubtrator();

