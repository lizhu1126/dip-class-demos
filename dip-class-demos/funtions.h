#pragma once
#include <opencv.hpp>

using namespace cv;
using namespace std;



VideoCapture createInput(bool useCamera, std::string videoPath);

//模板匹配demo
int templateMatching_demo();


//光流法，good feature to track
int opticalFlow_demo();





