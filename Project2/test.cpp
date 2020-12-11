#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int test1()
{
	//Mat grayMat,binMat;
	Mat frame = imread("E:/C++demo/image/image1.jpg");
	//cvtColor(frame, grayMat, COLOR_BGR2GRAY);
	//threshold(grayMat,binMat,100, 255, THRESH_OTSU);
	float LUT[256] = { 0 };
	for (int i = 0; i < 256; ++i)
	{
		for (int j = 0; j < 256; j++)
		{
			int m = 0;
		    LUT[i] = frame.at<uchar>(i,j);
		}
		float s = (float)(i / 255.0);
		float gamma = 0.55;
		float op = pow(s, gamma);
		LUT[i] = op * 255;
		cout << "像素值为：" << i << "=" << LUT[i] << endl;

	}
	Mat dst;
	frame.copyTo(dst);
	//if (dst.channels() == 1) 
	//{
	//	cv::MatIterator_<uchar> it = dst.begin<uchar>();
	//	cv::MatIterator_<uchar> it_end = dst.end<uchar>();
	//	for (; it != it_end; ++it) 
	//	{
	//		*it = LUT[(*it)];
	//	}
	//}
	//else
	//{
		cv::MatIterator_<cv::Vec3b> it = dst.begin<cv::Vec3b>();
		cv::MatIterator_<cv::Vec3b> it_end = dst.end<cv::Vec3b>();
		for (; it != it_end; ++it) 
		{
			(*it)[0] = LUT[(*it)[0]];
			(*it)[1] = LUT[(*it)[1]];
			(*it)[2] = LUT[(*it)[2]];
		}
	//}
	imshow("frame", frame);
	//imshow("grayMat", grayMat);
	//imshow("binMat", binMat);
	imshow("dst", dst);
	waitKey(0);
	return 0;		
}
int test2()
{
	cv::Mat src = imread("E:/C++demo/image/image2.jpg");
	std::vector<cv::Mat> channels;
	cv::split(src, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	Mat B1, G1, R1;

	equalizeHist(B, B1);
	equalizeHist(G, G1);
	equalizeHist(R, R1);

	Mat dst;
	vector<Mat> mbgr(3);
	mbgr[0] = B1;
	mbgr[1] = G1;
	mbgr[2] = R1;
	merge(mbgr, dst);

	//imshow("B", B);
	//imshow("G", G);
	//imshow("R", R);

	imshow("src", src);
	imshow("dst", dst);

	waitKey(1000);
	return 0;

}
//gamma矫正
int test3()
{
	Mat frame = imread("E:/C++demo/image/image3.jpg");

	float LUT[256] = { 0 };
	for (int i = 0; i < 256; ++i)
	{
		for (int j = 0; j < 256; j++)
		{
			int m = 0;
			LUT[i] = frame.at<uchar>(i, j);
		}
		float s = (float)(i / 255.0);
		float gamma = 0.43;
		float op = pow(s, gamma);
		LUT[i] = op * 255;
		cout << "像素值为：" << i << "=" << LUT[i] << endl;
	}

	Mat dst;
	frame.copyTo(dst);

    cv::MatIterator_<cv::Vec3b> it = dst.begin<cv::Vec3b>();
	cv::MatIterator_<cv::Vec3b> it_end = dst.end<cv::Vec3b>();
	for (; it != it_end; ++it) 
	{
		(*it)[0] = LUT[(*it)[0]];
		(*it)[1] = LUT[(*it)[1]];
		(*it)[2] = LUT[(*it)[2]];
	}

	imshow("frame", frame);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}
int main()
{
	//test1();
	test2();
	//test3();
	waitKey(0);	
	system("pause");
	return 0;
}
