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
			imshow("src", frame);
			medianBlur(frame, dstImage, 11);
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
//边缘提取
int test4()
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
//磨皮程序
int test5()
{
	VideoCapture cap(0);
	double scale = 0.5;
	//0-180肤色
	double i_minH = 0;
	double i_maxH = 20;
	//0-255
	double i_minS = 43;
	double i_maxS = 255;
	//0-255 
	double i_minV = 55;
	double i_maxV = 255;
	if (!cap.isOpened())
	{
		std::cout << "不能打开视频文件" << std::endl;
		return -1;
	}
	while (1)
	{
		Mat frame;
		cap >> frame;
		Mat hsvMat;
		Mat detectMat;	
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		imshow("whie:in the range", detectMat);
		imshow("frame", rFrame);
		waitKey(30);

	}
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
