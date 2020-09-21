#pragma once
#include <opencv.hpp>

using namespace cv;

//OpenCV中的mat的基本操作demo

//读取图片
int readImage();
int readVideo();
int readSequence();

//Mat的创建，复制及运算。包括Mat的各种参数解释
int createMat();
int copyMat();
int calcMat();
int calcLinearAlg();
int solveLinearEquations();
