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
			cout << "不能打开视频文件" << endl;
			return -1;
		}
		Mat dstImage;
		while (1)
		{
			Mat frame;
			cap >> frame;
			imshow("src", frame);
			medianBlur(frame, dstImage, 5);
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
		cout << "不能打开视频文件" << endl;
		return -1;
	}
	Mat dstImage;
	while (1)
	{
		Mat frame;
		cap >> frame;
		imshow("frame", frame);
		blur(frame, dstImage, Size(5,5), Point(-1, -1), BORDER_DEFAULT);
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
		cout << "不能打开视频文件" << endl;
		return -1;
	}
	Mat dstImage;
	while (1)
	{
		Mat frame;
		cap >> frame;
		imshow("frame", frame);
		GaussianBlur(frame, dstImage, Size(5, 5), 0, 0, BORDER_DEFAULT);
		imshow("均值滤波", dstImage);
		waitKey(30);
	}
	return 0;
}
//边缘提取
int test4()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return -1;
	}
	Mat dstImage;
	while (1)
	{
		Mat frame;
		cap >> frame;
		imshow("frame", frame);
		/*
		Mat dx;
		Mat dy;
		Sobel(frame, dx, -1, 1, 0, 3);
		Sobel(frame, dy, -1, 0, 1, 3);
		imshow("dx", dx);
		imshow("dy", dy);*/
		//Sobel(frame, dstImage, -1, 1, 0, 3);//x方向
		Sobel(frame, dstImage, -1, 0, 1, 3);//y方向
		imshow("边缘提取", dstImage);
		waitKey(30);
	}
	return 0;
}
//磨皮程序
int test5()
{
	VideoCapture cap(0);
	double scale = 0.5;
	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return -1;
	}
	//0-180肤色
	double i_minH = 0;
	double i_maxH = 20;
	//0-255
	double i_minS = 43;
	double i_maxS = 255;
	//0-255 
	double i_minV = 55;
	double i_maxV = 255;
	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;

		cap >> frame;		
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
		//将原图转化为HSV图像
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		rFrame.copyTo(detectMat);

		inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		Mat image; 
		Mat dst;
		GaussianBlur(rFrame, image, Size(5, 5), 3, 3);		
		rFrame.copyTo(dst);
		image.copyTo(dst, detectMat);

		imshow("detectMat", detectMat);//原图
		imshow("rFrame", image);//高斯滤波后
		imshow("dst", dst);
		waitKey(30);
	}
}
int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	system("pause");
	return 0;
}
