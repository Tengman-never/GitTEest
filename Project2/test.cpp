#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
/*
void test1()
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
}
*/
/*
int test2()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		std::cout << "无法打开视频文件" << std::endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess)
		{
			std::cout << "不能从视频中读取帧" << std::endl;
			break;
		}
		else
		{
			cv::imshow("frame", frame);
		}
		waitKey(30); //等待用户按键
	}

}
*/
/*
void test3()
{
	cv::Mat dispMat = imread("E:/C++demo/Project3/1.png");
	//矩形
	cv::Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.width=50;
	rect.height=50;
	rectangle(dispMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);
	//线段
	cv::Point pt1;
	cv::Point pt2;
	pt1.x= 50;
	pt1.y = 50;
	pt2.x =100;
	pt2.y = 100;
	line(dispMat,pt1,pt2, CV_RGB(255, 0, 0),1,8,0);
    //圆
	cv::Point pt;
	pt.x = 100;
	pt.y = 100;
	circle(dispMat, pt, 50, CV_RGB(0, 0, 255), 1, 8, 0);

	imshow("img", dispMat);
	waitKey(0); //等待用户按键
	system("pause");	
}
*/
void test4()
{

}
int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	//test5();
	system("pause");
	return 0;
}
