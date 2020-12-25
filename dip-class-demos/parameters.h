#pragma once


//选择需要演示的demo
#define DEMO_METHOD		2	//0:验证视频中像素值变化是否符合高斯分布
							//1:第一帧图像做背景的简单背景差分
							//2:单一高斯分布建模背景差分实现
							//3:调用opencv的背景差分函数方法演示


//参数设置
#define USE_CAMERA		true;	//ture: 使用摄像头作为输入	falese：读取本地视频
#define VIDEO_PATH		"../testImages\\vtest.avi";	//如果读取本地视频，则使用该路径

//高斯建模demo参数
#define FRAME_NUMBER	500	//使用视频的前多少帧进行背景建模
#define VAR_WEIGHT		3	//计算阈值时，方差乘以该权重

//OpenCV背景差分函数参数
#define BG_METHOD		0	//0：KNN 1：MOG2
#define UPDATE_MODEL	ture
#define SMOOTH_MASK		false

