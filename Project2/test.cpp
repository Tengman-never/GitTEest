#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//canny算子
int test1()
{
	VideoCapture cap(0);
	double scale = 0.5;
	if (!cap.isOpened())
	{
		cout << "不能打开文件" << endl;
		return -1;
	}
	Mat dstMat;
	while (1)
	{
		Mat frame;
		Mat srcMat;
		cap >> frame;		
		threshold(frame, srcMat, 100, 255, THRESH_BINARY);
		double threshold1 = 0, threshold2 = 0;
		Canny(srcMat, dstMat, threshold1, threshold2, 3, false);
		imshow("src", frame);
		imshow("dst", dstMat);
		waitKey(30);
	}
	return 0;
}
//旋转及缩放
int test2()
{
	Mat dstMat;
	Mat srcMat = imread("C:/Users/滕曼/Desktop/1.jpg");
	if (srcMat.empty()) return -1;
	//旋转-40°
	float angle = 7.0, scale = 1;
	//
	Point2f center(srcMat.cols*0.5,srcMat.rows*0.5);
	//
	const Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());
	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	return 0;
}
//仿射变换
int test3()
{	
	Mat dstMat;
	Mat srcMat = imread("C:/Users/滕曼/Desktop/1.jpg");
	if (srcMat.empty()) return -1;
	const Point2f src_pt[] = { Point2f(200,200),
							   Point2f(250,200),
		                       Point2f(200,100) };
	const Point2f dst_pt[] = { Point2f(300,100),
						       Point2f(300,50),
						       Point2f(200,100) };
	const Mat affine_matrix = getAffineTransform(src_pt, dst_pt);
	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());
	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	return 0;
}
//投影变换
int test4()
{
	Mat dstMat;
	Mat srcMat = imread("C:/Users/滕曼/Desktop/1.jpg");
	if (srcMat.empty()) return -1;
	const Point2f pst1[] = {   Point2f(150,150),
							   Point2f(150,300),
							   Point2f(350,300),
	                           Point2f(350,150)};
	const Point2f pst2[] = {   Point2f(200,150),
							   Point2f(200,300),
							   Point2f(340,270),
	                           Point2f(340,180)};
	const Mat perspective_matrix = getPerspectiveTransform(pst1, pst2);
	warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());
	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	return 0;
}
//图像矫正
int test5()
{
	Mat dstMat;
	Mat srcMat = imread("C:/Users/滕曼/Desktop/1.jpg");
	if (srcMat.empty()) return -1;
	Mat image = imread("C:/Users/滕曼/Desktop/1.jpg",0);
	
	int width = srcMat.rows;
	int height = srcMat.cols;
	uchar aver = 0;

	//原图中的三个点
	Point src_pt1, src_pt2, src_pt3;

	//修正后的三个点
	Point dst_pt1, dst_pt2, dst_pt3;
	dst_pt1 = Point(0, 0);
	dst_pt2 = Point(0, width - 1);
	dst_pt3 = Point(width - 1, height - 1);

	//遍历第一行像素
	for (int i = 0; i < width; ++i) 
	{
		aver = image.at<uchar>(i, height - 1);
		if (aver < 127)
		{
			src_pt1 = Point(i, 0);
			break;
		}
	}
	//遍历第一列像素
	for (int i = 0; i < height; ++i) 
	{
		aver = image.at<uchar>(0, i);
		if (aver < 250) 
		{
			src_pt2= Point(0, height - i);
			break;
		}
	}
	//遍历最后一行像素
	for (int i = 0; i < width; ++i) 
	{
		aver = image.at<uchar>(i, 0);
		if (aver < 127) 
		{
			src_pt3 = Point(i, height - 1);
			break;
		}
	}
	const Point2f pt1[] = { src_pt1, src_pt2, src_pt3 };
	const Point2f pt2[] = { dst_pt1, dst_pt2, dst_pt3 };

	Mat affine_matrix = getAffineTransform(pt1, pt2);
	warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	return 0;
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
