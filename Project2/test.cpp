#include<iostream>
#include<opencv2/opencv.hpp>
#define _CRT_SECURE_NO_WARNINGS
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

RNG rng(12345);
void test2()
{
	cv::Mat src = imread("E:/C++demo/Project2/04/1.jpg", 0);
	threshold(src, src, 100, 255, THRESH_BINARY);
	imshow("二值化后", src);
	Mat image;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5), Point(-1, -1));
	morphologyEx(src, image,3, kernel, Point(-1, -1));
	imshow("闭运算处理后", image);

	Mat labels= Mat::zeros(image.size(), CV_32S);
	Mat stats;
	Mat centroids;
	int num = connectedComponentsWithStats(image, labels, stats, centroids, 8, CV_32S);
	//使用不同的颜色标记连通域
	/*vector<Vec3b> color(num);
	color[0] = Vec3b(0, 0, 0);  //设置背景颜色
	for (int i = 1; i < num; i++)
	{
		color[i] = Vec3b(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)); //设置目标颜色
	}
	Mat dst = Mat::zeros(image.size(), image.type());
	int w = image.cols;
	int h = image.rows;
	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++) 
		{
			int label = labels.at<int>(row, col);
			if (label == 0) continue;
			dst.at<Vec3b>(row, col) = color[label];
		}
	}*/
	//imshow("连通域标记图像", dst);
	//标记连通域
	for (int i = 1; i < num; i++) 
	{
		Vec2d pt = centroids.at<Vec2d>(i, 0);
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);		
		cout<<x<<","<<y<<","<<width<<","<<height<<","<<area<< endl;
		//int Rx =(static_cast<unsigned int>(pt[0]));
		//int Ry =(static_cast<unsigned int>(pt[1]));
		circle(image, Point(pt[0],pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);
		rectangle(image, Rect(x, y, width, height), Scalar(255, 0, 255), 1, 8, 0);
	}
	cout << "硬币数=" << num - 1 << endl;//硬币数
	imshow("连通域标记图像", image);
	waitKey(0);
}

void test3()
{
	Mat src = imread("E:/C++demo/Project2/04/2.jpg", 0);
	imshow("src", src);
	Mat image;
	threshold(src, image, 60, 255, THRESH_OTSU);//二值化

	Mat kernel = getStructuringElement(MORPH_RECT, Size(10,10), Point(-1, -1));
	morphologyEx(src, image, 3, kernel, Point(-1, -1));
	imshow("闭运算处理后", image);
	Mat labels;
	Mat stats;
	Mat centroids;
	int num = connectedComponentsWithStats(image, labels, stats, centroids, 8, CV_32S);
	vector<Vec3b> color(num);
	color[0] = Vec3b(0, 0, 0);  //设置背景颜色
	for (int i = 1; i < num; i++)
	{
		color[i] = Vec3b(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)); //设置目标颜色
	}
	
	
	
	waitKey(0); //等待用户按键
	system("pause");
}


int main()
{
	//test1();
	test2();
	//test3();
	system("pause");
	return 0;
}
