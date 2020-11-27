#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//图像、装有直方图信息的指针、量化级数、cell数目
int calcHOG(Mat src,float *hist,int nAngle,int nSize)
{
	int nX = src.cols / nSize;
	int nY = src.rows / nSize;

	int binAngle = 360 / nAngle;

	//计算梯度及角度
	Mat gx,gy;
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
	waitKey(0);
	return 0;
}
float normL2(float *hist1,float *hist2,int size)
{
	float sum = 0,dst = 0;
	for (int i = 0; i < size; i++)
	{
		sum += (hist1[i] - hist2[i])*(hist1[i] - hist2[i]);
	}
	dst = sqrt(sum);
	return dst;
}

int main()
{
	Mat refMat = imread("E:/C++demo/image/hogTemplate.jpg",0);
	Mat plMat = imread("E:/C++demo/image/img1.jpg",0);
	Mat bgMat = imread("E:/C++demo/image/img2.jpg",0);

	int nAngle = 8;
	int cellSize = 16;
	int nX = refMat.cols / cellSize;
	int nY = refMat.rows / cellSize;

	int bins = nX * nY * nAngle;

	float * ref_hist = new float[bins];
	memset(ref_hist,0,sizeof(float)*bins);
	float * pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float)*bins);
	float * bg_hist = new float[bins];
	memset(bg_hist, 0, sizeof(float)*bins);

	int reCode = 0;
	reCode = calcHOG(refMat, ref_hist, nAngle, cellSize);
	reCode = calcHOG(plMat, pl_hist, nAngle, cellSize);
	reCode = calcHOG(bgMat, bg_hist, nAngle, cellSize);

	if (reCode != 0)
	{
		delete[] ref_hist;
		delete[] pl_hist;
		delete[] bg_hist;
		return -1;
	}

	float dis1 = normL2(ref_hist, pl_hist, bins);
	float dis2 = normL2(ref_hist, bg_hist, bins);
	cout << "distance between reference and image1:" << dis1 << endl;
	cout << "distance between reference and image2:" << dis2 << endl;

	if (dis1 <= dis2)
	{
		cout << "image1 is more simular" << endl;
	}
	else
	{
		cout << "image2 is more simular" << endl;
	}

	imshow("hogTemplate", refMat);
	imshow("image1", plMat);
	imshow("image2", bgMat);
	waitKey(0);
	system("pause");

	delete[] ref_hist;
	delete[] pl_hist;
	delete[] bg_hist;
	return 0;
}
