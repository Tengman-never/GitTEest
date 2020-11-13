#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//canny算子
int test1()
{
	Mat src = imread("C:/Users/滕曼/Pictures/1.jpg");
	Mat dst;
	float angle = -10.0, scale = 1;
	Point2f center(src.cols / 2.0, src.rows / 2.0);
	Mat rot = getRotationMatrix2D(center,angle,scale);
	Rect bbox = RotatedRect(center, src.size(), angle).boundingRect();
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	warpAffine(src, dst, rot, bbox.size());
	imshow("src",src);
	imshow("dst",dst);
	waitKey(0);
	return 0;
}
//旋转及缩放
int test2()
{
	std::vector<cv::Vec2f>lines;
	Mat image;
	Mat src=imread("D:/Program Files/QQ/文档/3050983836/FileRecv/18.jpg");
	Mat srcMat = imread("D:/Program Files/QQ/文档/3050983836/FileRecv/18.jpg",0);
	//threshold(srcMat,image,0,255,THRESH_OTSU);
	double threshold1 = 60, threshold2 = 150;
	Canny(srcMat, image, threshold1, threshold2, 3, false);
	HoughLines(image, lines, 1, CV_PI/180, 100);
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it)
	{
		float rho = (*it)[0], theta = (*it)[1];
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(src, pt1, pt2, Scalar(0,0,255), 1, CV_AA);
	}
	imshow("canny", image);
	imshow("dst", src);
	waitKey(0);
	return 0;
}
//霍夫变换
int test3()
{	
	Mat image;
	Mat src = imread("D:/Program Files/QQ/文档/3050983836/FileRecv/18.jpg");
	Mat srcMat = imread("D:/Program Files/QQ/文档/3050983836/FileRecv/18.jpg", 0);
	//threshold(srcMat,image,0,255,THRESH_OTSU);
	double threshold1 = 60, threshold2 = 150;
	Canny(srcMat, image, threshold1, threshold2, 3, false);

	std::vector<cv::Vec4i>lines;
	HoughLinesP(image, lines, 1, CV_PI/180, 40, 10 , 10);

	std::vector<cv::Vec4i>::iterator it = lines.begin();
	for (size_t i = 0; i < lines.size(); i++)
	{
		cv::Vec4i line = lines[i];
		cv::line(src, Point(line[0], line[1]), cv::Point(line[2], line[3]), Scalar(0, 0, 255), 1, CV_AA);
	}
	imshow("canny", image);
	imshow("dst", src);
	waitKey(0);
	return 0;
}
int main()
{
	test1();
	//test2();
	//test3();
	system("pause");
	return 0;
}
