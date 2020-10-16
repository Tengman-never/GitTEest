#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void test1()
{
	    cv::Mat img = imread("E:/C++demo/Project2/04/1.jpg", 0);
		Mat src;
		threshold(img, src,100, 255, THRESH_BINARY);
		imshow("src", src);
	    Size(6,6);
		Mat getStructuringElement(int shape, Size ksize, Point anchor = Point(-1,-1));		
		Mat dst;
		Mat kernel = getStructuringElement(MORPH_RECT, Size (3,3), Point(-1, -1));
		//腐蚀
		/*erode(src,dst,kernel);
		imshow("fushi", dst);*/
		//膨胀
		/*dilate(src, dst, kernel);
		imshow("pengzhang", dst);*/
		//morphologyEx(src, dst, 2, kernel, Point(-1, -1));
		//imshow("open", dst);
		morphologyEx(src, dst, 3, kernel, Point(-1, -1));
		imshow("close", dst);
		waitKey(0); 
}

/*
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

*/
int main()
{
	test1();
	//test2();
	//test3();
	system("pause");
	return 0;
}
