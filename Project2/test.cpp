#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void test1()
{
	VideoCapture cap(0);
	double scale = 0.5;
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
		cap >>frame;
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		imshow("whie:in the range", detectMat);
		imshow("frame", rFrame);
		waitKey(30); 

	}	
}


void test2()
{
	cv::Mat img = imread("E:/C++demo/Project2/1.jpg",0);
	imshow("origin", img);
	Mat result;
	threshold(img, result, 100, 255, THRESH_BINARY);
	imshow("result", result);
	adaptiveThreshold(img, result, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);
	imshow("result_a", result);		
	waitKey(0); //等待用户按键

}

string window_name = "binaryMat";
void threshod_Mat(int th, void* data)
{
	Mat src = *(Mat*)(data);
	Mat dst;
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
}

int test3()
{
	Mat srcMat;
	Mat gryMat;
	int lowTh = 30;
	int maxTh = 255;

	srcMat = imread("E:/C++demo/Project2/1.jpg");
	if (!srcMat.data)
	{
		cout << "图像加载失败" << endl;
		return 0;
	}
	
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);
	imshow(window_name, gryMat);
	createTrackbar("{threshold", window_name, &lowTh, maxTh, threshod_Mat, &gryMat);
	
	waitKey(0); //等待用户按键
	system("pause");
	return 0;
}


int main()
{
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}
