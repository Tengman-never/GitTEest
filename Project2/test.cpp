#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void on_mouse(int EVENT, int x, int y, int flags, void* userdata);
RNG rng(123);
void main()
{
	VideoCapture cap("C:/Users/滕曼/Desktop/video.mp4");
	double scale = 1;
	//0-180
	double i_minH = 8;
	double i_maxH = 10;
	//0-255
	double i_minS = 43;
	double i_maxS = 255;
	//0-255 
	double i_minV = 46;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;
		Mat image;
		cap >> frame;
		if (frame.empty())
			break;
		GaussianBlur(frame,frame, Size(5,5),0,0);
		//ksize必须是大于1的奇数
		//medianBlur(frame,frame,5);
		//imshow("frame",frame);

		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
		//RGB转化为HSV  
		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		rFrame.copyTo(detectMat);
		//主要是将在两个阈值内的像素值设置为白色（255），而不在阈值区间内的像素值设置为黑色（0）
		//输出的detectMat是一幅二值化之后的图像。
		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);
		//灰度化
		threshold(detectMat, detectMat, 100, 255, THRESH_OTSU);
		//setMouseCallback("【display】", on_mouse, &detectMat);

		vector<Vec4i>hierarchy;
		std::vector<std::vector<Point>> contours;
		findContours(detectMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		vector<Rect> boundRect(contours.size());
		for (int i = 0; i < contours.size(); i++)
		{
			RotatedRect rbox = minAreaRect(contours[i]);
			float width = (float)rbox.size.width;
			float height = (float)rbox.size.height;
			float radio = width / height;
			if (width * height > 280 && width > 30)
			{
				boundRect[i] = boundingRect(Mat(contours[i]));
				rectangle(rFrame, boundRect[i].tl(), boundRect[i].br(), (0, 0, 255), 2, 8, 0);
			}
		}
	

		/*imshow("frame", frame);*/
		imshow("whie:in the range", detectMat);
		imshow("rFrame", rFrame);
		waitKey(30);
	}
}
void on_mouse(int EVENT, int x, int y, int flags, void* userdata)
{
	Mat hh;
	hh = *(Mat*)userdata;
	Point p(x, y);
	switch (EVENT)
	{
	case EVENT_LBUTTONDOWN:
	{

		printf("b=%d\t", hh.at<Vec3b>(p)[0]);
		printf("g=%d\t", hh.at<Vec3b>(p)[1]);
		printf("r=%d\n", hh.at<Vec3b>(p)[2]);
		circle(hh, p, 2, Scalar(255), 3);
	}
	break;

	}
}
