#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int test1()
{
	VideoCapture cap;
	cap.open(0);
	int cnt = 0;
	Mat bgMat,subMat,resMat;
	while (1)
	{
		Mat frame;
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0)
		{
			frame.copyTo(bgMat);
			cnt++;
		}
		else
		{
			absdiff(frame, bgMat, subMat);
			threshold(subMat, resMat, 100, 255, CV_THRESH_OTSU);
			imshow("subMat", subMat);
			imshow("resMat", resMat);
			waitKey(30);
		}
	}

	return 0;		
}
int test2()
{
	VideoCapture cap;
	cap.open(0);
	vector<Mat> image;
	int cnt = 0;
	Mat mean(480,640, CV_8UC1);
	Mat var(480, 640, CV_32FC1);
	int h = 640;
	int w = 480;
	bool haveModel = false;
	while (1)
	{
		Mat frame;
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		threshold(frame, frame, 100, 255, THRESH_OTSU);
		if (cnt < 20)
		{
			image.push_back(frame);
		}
		else
		{
			//没有高斯模型，则计算
			if (!haveModel)
			{
				//计算均值和方差
				for (cnt = 0; cnt < 20; cnt++)
				{
					//Mat Th = var;
					for (int j = 0; j < h; j++)
					{
						for (int i = 0; i < w; i++)
						{
							for (int m = 0; m < 20; m++)
							{
								mean.at<uchar>(i, j) += image[m].at<uchar>(i, j);
							}
							mean.at<uchar>(i, j) /= 20;
							for (int n = 0; n < 20; n++)
							{
								var.at<float>(i, j) = pow(float(image[n].at<uchar>(i, j) - mean.at<uchar>(i, j)), 2);
							}
							var.at<float>(i, j) /= 20;

						}
					}
				}
			}
			//模型计算完成，置true,下次不再计算
			haveModel = true;

			Mat Th = var;
			for (int j = 0; j < h; j++)
			{
				for (int i = 0; i < w; i++)
				{
					if (frame.at<uchar>(i, j) - mean.at<uchar>(i, j) > Th.at<uchar>(i, j))
					{
						frame.at<uchar>(i, j) = 255;
					}
					else
					{
						frame.at<uchar>(i, j) = 0;
					}
				}
			}
		}
		imshow("frame", frame);
		waitKey(30);
	}
	return 0;
}
int main()
{
	//test1();
	test2();
	waitKey(0);	
	system("pause");
	return 0;
}
