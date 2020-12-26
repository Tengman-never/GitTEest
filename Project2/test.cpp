#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int test1()
{
	cv::VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened())
		return 0;
	int cnt = 0;
	Mat frame, tempMat, refMat, resultMat;
	while (1)
	{
		
		cap >> frame;
		if (frame.empty())
			break;
		if (cnt == 0)
		{
			Rect2d  r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}
		cnt++;
		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX);
		double minVal; double maxVal;
		Point minLoc;  Point maxLoc;
		Point matchLoc;
		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		rectangle(frame,minLoc,Point(minLoc.x + refMat.cols,minLoc.y + refMat.rows),Scalar(0,255,255),1,8,0);
		imshow("hello", frame);
		waitKey(50);
	}
	system("pause");
	return 0;
}
//图像、装有直方图信息的指针、量化级数、cell数目

int calcHOG(Mat src, float *hist, int nAngle, int nSize)
{
	int nX = src.cols / nSize;
	int nY = src.rows / nSize;

	int binAngle = 360 / nAngle;

	//计算梯度及角度
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	Rect roi;
	roi.width = nSize;
	roi.height = nSize;
	//遍历
	for (int i = 0; i < nY; i++)
	{
		for (int j = 0; j < nX; j++)
		{
			Mat roiMat;
			Mat roiMag;
			Mat roiAgl;

			roi.x = j * nSize;
			roi.y = i * nSize;
			//赋值图像，一个cell赋给一个roiMat
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//直方图信息
			int head = (i*nX + j)*nAngle;
			for (int n = 0; n < roiMat.rows; n++)
			{
				for (int m = 0; m < roiMat.cols; m++)
				{
					//计算角度在哪个bin，通过int自动取整实现
					int pos = (int)(roiAgl.at<float>(n, m) / binAngle);
					//以像素点的值为权重
					hist[head + pos] += roiMag.at<float>(n, m);
				}
			}
		}

	}
	return 0;
}
float normL2(float *hist1, float *hist2, int size)
{
	float sum = 0, dst = 0;
	for (int i = 0; i < size; i++)
	{
		sum += (hist1[i] - hist2[i])*(hist1[i] - hist2[i]);
	}
	dst = sqrt(sum);
	return dst;
}

int Hog(Mat refMat,Mat plMat)
{
	cvtColor(refMat,refMat, COLOR_BGR2GRAY);
	cvtColor(plMat, plMat, COLOR_BGR2GRAY);

	float dis = 0;

	int nAngle = 8;
	int cellSize = 16;
	int nX = refMat.cols / cellSize;
	int nY = refMat.rows / cellSize;

	int bins = nX * nY * nAngle;

	float * ref_hist = new float[bins];
	memset(ref_hist,0,sizeof(float)*bins);
	float * pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float)*bins);

	int reCode = 0;
	reCode = calcHOG(refMat, ref_hist, nAngle, cellSize);
	reCode = calcHOG(plMat, pl_hist, nAngle, cellSize);

	if (reCode != 0)
	{
		delete[] ref_hist;
		delete[] pl_hist;
		return -1;
	}

	dis = normL2(ref_hist, pl_hist, bins);
	//cout << "相似度为：" << dis << endl;

	waitKey(0);

	delete[] ref_hist;
	delete[] pl_hist;
	return dis;
}
void test2()
{
	Mat src = imread("E:/C++demo/image/origin.jpg");
	Mat image = imread("E:/C++demo/image/18.jpg");
	int h = image.rows;//行数
	int w = image.cols;//列数
	Mat tempMat, refMat;
	float dist = 0;//相似度
	float result = 0;
	float distMin = 100000;
	Point pt;
	for (int j = 0; j < h - src.rows; j++)
	{
		for (int i = 0; i < w - src.cols; i++)
		{

			Rect rectMat;
			rectMat.x = i;
			rectMat.y = j;
			rectMat.width = src.cols;
			rectMat.height = src.rows;

			tempMat = image(rectMat);
			tempMat.copyTo(refMat);

			dist = Hog(src, refMat);
			cout << "相似度为：" << dist << endl;

			//distMin = dist;
			if (dist < distMin)
			{
				distMin = dist;
				pt = Point(i,j);
			}
		}
	}

	Rect rect;
	rect.x = pt.x;
	rect.y = pt.y;
	rect.width = src.cols;
	rect.height = src.rows;

	rectangle(image, rect, Scalar(0, 0, 255), 1, 8, 0);

	imshow("image", image);
	waitKey(0);
}
int main()
{
	//test1();
	test2();

	system("pause");
	return 0;
}
