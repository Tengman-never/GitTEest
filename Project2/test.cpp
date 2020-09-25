#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

void test1()
{
	cv::Mat img = imread("E:/C++demo/Project1/1.jpg");
	imshow("before", img);
	int height = img.rows;
	int width = img.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (img.at<Vec3b>(j, i)[0] + img.at<Vec3b>(j, i)[1] + img.at<Vec3b>(j, i)[2]) / 3;
			img.at<Vec3b>(j, i)[0] = average;
			img.at<Vec3b>(j, i)[1] = average;
			img.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("after", img);
	waitKey(0);
}
void test2()
{
	cv::Mat img = imread("E:/C++demo/Project1/1.jpg", 0);
	imshow("img", img);
	//等待用户按键
	waitKey(0);
}
void test3()
{
	cv::Mat img = imread("E:/C++demo/Project1/1.jpg");
	imshow("before", img);
	int height = img.rows;
	int width = img.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar threshold = 150;
			uchar average = (img.at<Vec3b>(j, i)[0] + img.at<Vec3b>(j, i)[1] + img.at<Vec3b>(j, i)[2]) / 3;
			if (average > threshold)
				average = 255;
			else
				average = 0;

			img.at<Vec3b>(j, i)[0] = average;
			img.at<Vec3b>(j, i)[1] = average;
			img.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("after", img);
	//等待用户按键
	waitKey(0);
}
void test4()
{
	cv::Mat srcM = imread("E:/C++demo/Project1/1.jpg");
	imshow("before", srcM);
	cv::Mat deepMat;
	cv::Mat shallowMat;
	shallowMat = srcM;
	srcM.copyTo(deepMat);
	int height = srcM.rows;
	int width = srcM.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar threshold = 150;
			uchar average = (srcM.at<Vec3b>(j, i)[0] + srcM.at<Vec3b>(j, i)[1] + srcM.at<Vec3b>(j, i)[2]) / 3;
			if (average > threshold)
				average = 255;
			else
				average = 0;

			srcM.at<Vec3b>(j, i)[0] = average;
			srcM.at<Vec3b>(j, i)[1] = average;
			srcM.at<Vec3b>(j, i)[2] = average;
		}
	}

	imshow("qian", shallowMat);
	imshow("shen", deepMat);

	//等待用户按键
	waitKey(0);
}
int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	system("pause");
	return 0;

}