#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//canny算子
int test1()
{
	Mat grayMat,binaryMat;
	Mat src = imread("C:/Users/滕曼/Desktop/1.png");
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
	cvtColor(image, grayMat, COLOR_BGR2GRAY);
	threshold(grayMat, binaryMat, 100, 255, THRESH_OTSU);
	//vector<vector<Point>>contours;
	//vector<Vec4i>hierarchy;
	//findContours(binaryMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	vector<Vec3f> circles;
	HoughCircles(grayMat, circles, HOUGH_GRADIENT, 1, 10, 100, 30, 5, 50);

	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3f c = circles[i];
		circle(src, Point(c[0], c[1]), c[2], Scalar(0, 0, 255), -1, CV_AA);
	}
	imshow("src", src);
	//imshow("grayMat", grayMat);
	//imshow("binaryMat",binaryMat);
	waitKey(0);
	return 0;
}
//
int test2()
{
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	Mat binaryMat;
	Mat src=imread("C:/Users/滕曼/Desktop/2.jpg");
	Mat grayMat = imread("C:/Users/滕曼/Desktop/2.jpg",0); 
	threshold(grayMat,binaryMat,0,255,THRESH_OTSU);
	findContours(binaryMat,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());
	for(int i = 0;i < contours.size();i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float radio = width / height;
		if (radio> 0.9 && radio<1.1)
		{
			boundRect[i] = boundingRect(Mat(contours[i]));
			rectangle(src, boundRect[i].tl(), boundRect[i].br(), (0, 0, 255), 2, 8, 0);
			//drawContours(src, contours, i, Scalar(0, 0, 255), 3, 8);
			//Point2f vtx[4];
			//rbox.points(vtx);
			//for (int j = 0; j < 4; j++)
			//{				
			//	line(src,vtx[j],vtx[j < 3 ? j+1 : 0],Scalar(0,0,255),2,CV_AA);
			//}
		}
	}	
	imshow("src", src);
	//imshow("grayMat", grayMat);
	//imshow("binaryMat",binaryMat);
	waitKey(0);
	return 0;
}
//
int test3()
{	
	Mat image;
	Mat src = imread("C:/Users/滕曼/Desktop/2.jpg");
	Mat srcMat = imread("C:/Users/滕曼/Desktop/2.jpg", 0);
	threshold(srcMat,image,0,255,THRESH_OTSU);
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
