#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
	cv::Mat img = imread("E:/C++demo/Project3/1.png");
	std::vector<cv::Mat> channels;
	cv::split(img, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	imshow("red", R);
	imshow("green", G);
	imshow("blue", B);
	imshow("original Mat", img);

	waitKey(0); //等待用户按键
	system("pause");
	return 0;
}



