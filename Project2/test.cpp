#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//识别火焰并画出矩形框
void checkFire(Mat& src);
//找出水柱上3个点
void find3Points(Mat& src, vector<Point>* parameter);
//根据找到的三个点画出抛物线
void drawLine(Mat& src, const vector<Point>* parameter);
//识别火焰并画出矩形框
void checkFire(Mat& src)
{
	double scale = 1;
	//0-180
	double i_minH = 8;
	double i_maxH = 10;
	//0-255
	double i_minS = 43;
	double i_maxS = 255;
	//0-255 
	double i_minV = 220;
	double i_maxV = 255;

	Mat hsvMat, detectMat;

	Size ResImgSiz = Size(src.cols*scale, src.rows*scale);
	Mat rFrame = Mat(ResImgSiz, src.type());
	resize(src, rFrame, ResImgSiz, INTER_LINEAR);
	//RGB转化为HSV  
	cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
	rFrame.copyTo(detectMat);
	//主要是将在两个阈值内的像素值设置为白色（255），而不在阈值区间内的像素值设置为黑色（0）
	//输出的detectMat是一幅二值化之后的图像。
	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);
	//imshow("binary", detectMat);

	//膨胀处理
	Mat getStructuringElement(int shape, Size ksize, Point anchor = Point(-1, -1));	//结构算子
	Mat dilateMat;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(13, 13), Point(-1, -1));
	dilate(detectMat, dilateMat, kernel);
	//imshow("dilateMat", dilateMat);

	vector<Vec4i>hierarchy;
	std::vector<std::vector<Point>> contours;
	findContours(dilateMat, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float radio = width / height;
		if (width * height > 280 || width > 14 || height > 11)
		{
			boundRect[i] = boundingRect(Mat(contours[i]));
			rectangle(src, boundRect[i].tl(), boundRect[i].br(), (0, 0, 255), 2, 8, 0);
		}
	}
	//imshow("rFrame", src);
}
//水柱上的点的坐标可通过二值化以及连通筛选获得。
//拟合水柱的曲线方程，可以将水柱的方程近似为一个二次方程，通过opencv中的solve函数求解方程。
//找出水柱上三个点
void find3Points(Mat& src, vector<Point>* parameter)
{
	(*parameter)[0] = Point(76, 0);
	(*parameter)[1] = Point(0, 0);
	(*parameter)[2] = Point(0, 0);
	Mat imageROI;
	int cnt = 1;
	/*在帧图像中选择ROI*/
	Mat srcROI = src(Rect(106, 36, 165, 41));
	/*二值化*/
	cvtColor(srcROI, srcROI, COLOR_BGR2GRAY);
	dilate(srcROI,srcROI, Mat(3, 3, CV_8UC1));
	threshold(srcROI, srcROI, 200, 255,0);
	/*保存下来*/
	imwrite("srcROI.jpg", srcROI);
	//连通域筛选
	for (int i = srcROI.rows - 1; i > 0; i = i / 2)
	{
		for (int j = srcROI.cols - 1; j > 0; j--)
		{
			/*从下向上,从右向左,遇到白色认为是水柱*/
			if (srcROI.at<uchar>(i, j) == 255)
			{
				(*parameter)[cnt] = Point(j, i);
				cnt++;
				break;
			}
		}
		/*找到三个点就break*/
		if (cnt == 3)
			break;
	}

	/*将相对于ROI的坐标变成相对于整个图像的坐标*/
	for (int i = 0; i < 3; i++) 
	{
		(*parameter)[i].y += 35;
		(*parameter)[i].x += 100;
	}
}
//根据三个点拟合抛物线
//根据公式  a*x1*x1 + b*x1 + c = y1，
//          a*x2*x2 + b*x2 + c = y2，
//          a*x3*x3 + b*x3 + c = y3。
//其中x1、x2、x3为那三个点的X坐标；
//y1、y2、y3为那三个点的Y坐标；a、b、c为被拟合的抛物线参数。
//填充矩阵：A[3][3] = [[x1*x1, x1, 1], [x2*x2, x2, 1], [x3*x3, x3, 1]]
//B[3] = [y1, y2, y3];
//将矩阵A、B作为输入参数，生成抛物线参数a、b、c, 保存到matC中。
void drawLine(Mat& src, const vector<Point>* parameter)
{
	int x0 = (*parameter)[0].x;
	int x1 = (*parameter)[1].x;
	int x2 = (*parameter)[2].x;

	int y0 = (*parameter)[0].y;
	int y1 = (*parameter)[1].y;
	int y2 = (*parameter)[2].y;
	
	float A[3][3] = { {x0 * x0, x0, 1}, {x1 * x1, x1, 1}, {x2 * x2, x2, 1} };
	float B[3] = { y0, y1,y2 };
	float C[3] = { 0, 0, 0 };

	size_t i = 0;
	//创建矩阵
	CvMat* matA = cvCreateMat(3, 3, CV_32FC1);
	CvMat* matB = cvCreateMat(3, 1, CV_32FC1);
	CvMat* matC = cvCreateMat(3, 1, CV_32FC1);

	cvSetData(matA, A, CV_AUTOSTEP);
	cvSetData(matB, B, CV_AUTOSTEP);
	//核心函数,二次曲线的参数存到了matC里
	cvSolve(matA, matB, matC, CV_LU);

	int result = 0;

	for (i = 175; i < src.cols ; i++) 
	{
		/*根据上面求出来的参数算出点的坐标*/
		result = (int)(i * i * matC->data.fl[0]) + i * matC->data.fl[1] + matC->data.fl[2];
		if (result < src.rows )
		{
			circle(src, cvPoint(i, result), 2, Scalar(0, 255, 255), -1);			
		}
	}
}
int main()
{
	vector<Point>* parameter = new vector<Point>;

	(*parameter).push_back(Point(76, 0));
	(*parameter).push_back(Point(0, 0));
	(*parameter).push_back(Point(0, 0));

	VideoCapture cap("C:/Users/滕曼/Desktop/video.mp4");

	while (1)
	{
		Mat frame;
		cap >> frame;
		if (frame.empty())
			break;
		//识别火焰
		checkFire(frame);
		//找出3个点
		find3Points(frame, parameter);
		//根据三个点画抛物线
		drawLine(frame, parameter);

		imshow("result", frame);
		waitKey(30);

	}
	/*释放内存*/
	delete parameter;
	waitKey(0);
	system("pause");
	return 0;
}