#pragma once

//选择需要演示的demo
#define DEMO_METHOD		2		//0:手写模板匹配
							//1:模板匹配
							//2:光流

							
//参数设置
#define USE_CAMERA		true	//true: 使用摄像头作为输入	false：读取本地视频
#define VIDEO_PATH		"../testImages\\vtest.avi"		//如果读取本地视频，则使用该路径
