#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//中值滤波
int test1()
{
	    VideoCapture cap(0);
	    double scale = 0.5;
		if (!cap.isOpened())
		{
			std::cout << "不能打开视频文件" << std::endl;
			return -1;
		}
		Mat dstImage;
		while (1)
		{
			Mat frame;
			cap >> frame;
			medianBlur(frame, dstImage, 7);
			imshow("中值滤波", dstImage);
			waitKey(30); 
		}
		return 0;
}
//均值滤波
int test2()
{
	VideoCapture cap(0);
	double scale = 0.5;
	if (!cap.isOpened())
	{
		std::cout << "不能打开视频文件" << std::endl;
		return -1;
	}
	Mat dstImage;
	while (1)
	{
		Mat frame;
		cap >> frame;
		blur(frame, dstImage, Size(5, 5), Point(-1, -1), BORDER_DEFAULT);
		imshow("均值滤波", dstImage);
		waitKey(30);
	}
	return 0;
}
//均值滤波
int test3()
{	
	VideoCapture cap(0);
	double scale = 0.5;
	if (!cap.isOpened())
	{
		std::cout << "不能打开视频文件" << std::endl;
		return -1;
	}
	Mat dstImage;
	while (1)
	{
		Mat frame;
		cap >> frame;
		GaussianBlur(frame, dstImage, Size(5, 5), 5, 0, BORDER_DEFAULT);
		imshow("均值滤波", dstImage);
		waitKey(30);
	}
	return 0;
}


int main()
{
	test1();
	//test2();
	//test3();
	//test4();
	//test5();
	system("pause");
	return 0;
}
