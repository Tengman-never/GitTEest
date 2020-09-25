#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
	cv::Mat img = imread("E:/C++demo/Project1/1.jpg");
	imshow("test", img);
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
	imshow("img", img);
	//等待用户按键
	waitKey(0);
	
	system("pause");
	return 0;

}
