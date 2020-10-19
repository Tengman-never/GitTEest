﻿#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
/*
void test1()
{
	    cv::Mat img = imread("E:/C++demo/Project2/04/1.jpg", 0);
		Mat src;
		threshold(img, src,100, 255, THRESH_BINARY);
		imshow("src", src);
	    Size(6,6);
		Mat getStructuringElement(int shape, Size ksize, Point anchor = Point(-1,-1));	//结构算子
		Mat dst;
		Mat kernel = getStructuringElement(MORPH_RECT, Size (3,3), Point(-1, -1));
		/*--------腐蚀----------*/
		//erode(src,dst,kernel);
		//imshow("fushi", dst);
		/*--------膨胀-----------*/
		//dilate(src, dst, kernel);
		//imshow("pengzhang", dst);
		/*--------开运算---------*/
		//morphologyEx(src, dst, 2, kernel, Point(-1, -1));
		//imshow("open", dst);
		/*---------闭运算--------*/
		//morphologyEx(src, dst, 3, kernel, Point(-1, -1));
		//imshow("close", dst);
		//waitKey(0); 
//}
/*
RNG rng(123);
void test2()
{
	cv::Mat src_binary;
	cv::Mat image_gray;

	cv::Mat src = imread("E:/C++demo/Project2/04/1.jpg");
	cvtColor(src, image_gray, COLOR_BGR2GRAY);

	threshold(image_gray, src_binary, 100, 255, THRESH_BINARY);
	imshow("二值化后", src_binary);

	Mat image;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5), Point(-1, -1));
	morphologyEx(src_binary, image, MORPH_CLOSE, kernel, Point(-1, -1));
	imshow("闭运算处理后", image);
	Mat labels;
	Mat stats;
	Mat centroids;
	int num = connectedComponentsWithStats(image, labels, stats, centroids, 8, CV_32S);

	//使用不同的颜色标记连通域
	vector<Vec3b> colors(num);
	colors[0] = Vec3b(0, 0, 0);
	//int b = rng.uniform(0, 255);
	//int g = rng.uniform(0, 255);
	//int r = rng.uniform(0, 255);
	for (int i = 1; i < num; i++) 
	{
		colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	}
	Mat dst = Mat::zeros(src.size(), src.type());
	int w = src.cols;
	int h = src.rows;
	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			int label = labels.at<int>(row, col);
			if (label == 0) continue;
			dst.at<Vec3b>(row, col) = colors[label];
		}
	}
	imshow("连通域标记图像", dst);
	
	//标记连通域

	for (int i = 1; i < num; i++)
	{
		Vec2d pt = centroids.at<Vec2d>(i, 0);
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);
		cout << "连通域中心的矩阵" << endl;
		cout << pt[0] << "," << pt[1] << endl;
		cout << "状态矩阵" << endl;
		cout << x << "," << y << "," << width << "," << height << "," << area << endl;
		circle(dst, Point(pt[0], pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);
		rectangle(dst, Rect(x, y, width, height), Scalar(255, 0, 255), 1, 8, 0);
	}
	imshow("连通域标记图像", dst);
	cout << "硬币数=" << num - 1 << endl;//硬币数

	waitKey(0);
}
*/

void test3()
{	
	cv::Mat src_binary;
	cv::Mat image_gray;

	cv::Mat src = imread("E:/C++demo/Project2/04/2.jpg");
	cvtColor(src, image_gray, COLOR_BGR2GRAY);

	threshold(image_gray, src_binary, 100, 255, THRESH_BINARY);
	imshow("二值化后", src_binary);
	// 对图像进行所有像素用 （255- 像素值）
	Mat image;
	src.copyTo(image);
	// 获取图像宽、高
	int channels = src.channels();
	int rows = src.rows; //高---行
	int col = src.cols;//宽---列
	int cols = src.cols * channels;
	if (src.isContinuous())
	{
		cols *= rows;
		rows = 1;
	}
	// 每个像素点的每个通道255取反（0-255（黑-白））
	uchar* p1;
	uchar* p2;
	for (int row = 0; row < rows; row++) 
	{
		p1 = src.ptr<uchar>(row);// 获取像素指针
		p2 = image.ptr<uchar>(row);
		for (int col = 0; col < cols; col++)
		{
			*p2 = 255 - *p1; // 取反
			p2++;
			p1++;
		}
	}
	imshow("取反后的图像", image);

	Mat image_Ostu;//大津法分割后的图像
	Mat image_Open;//开运算后的图像
	//大津法分割图像
	threshold(image, image_Ostu, 0, 255, THRESH_OTSU);
	imshow("大津法后的图像", image_Ostu);
	/*Mat kernel = getStructuringElement(MORPH_RECT, Size(11, 11));
	morphologyEx(image_Ostu, image_Open, 2, kernel, Point(-1, -1), 1);//开运算
	Mat labels;
	Mat stats;
	Mat centroids;
	int num = connectedComponentsWithStats(image_Open, labels, stats, centroids, 8, CV_32S);
	imshow("开运算后的图像", image_Open);
	/*
	//输出连通域信息
	for (int i = 0; i < num; i++)
	{
		//各个连通域的统计信息保存在stasMat中
		Vec2d pt = centroids.at<Vec2d>(i, 0);

		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);

		cout << x << "," << y << "," << width << "," << height << "," << area << endl;
		circle(image_Open , Point(pt[0], pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);
		rectangle(image_Open, Rect(x, y, width, height), Scalar(255, 255, 255), 1, 8, 0);
	}
	cout << "连通域个数为 " << num - 1 << endl;//-1,num包括背景

	vector<Vec3f> circles;
	HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(image, center, radius, Scalar(155, 50, 255), 3, 8, 0);

	}

	count(image_Open);
	imshow("标记后的图像", image_Open);
	std::vector<cv::Vec3b> colors(num);
	colors[0] = cv::Vec3b(0, 0, 0);//背景黑色

*/
	waitKey(0);
}

int main()
{
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}
