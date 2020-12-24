#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
RNG rng(123);
int main()
{
	Mat src_binary;
	Mat image_gray;
	Mat src = imread("E:/C++demo/image/final.jpg");
	// 对图像进行所有像素用 （255- 像素值）
	Mat image;//取反后的图像
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
	imshow("取反后的图像", image);
	cvtColor(image, image_gray, COLOR_BGR2GRAY);//灰度化
	threshold(image_gray, src_binary, 100, 255, THRESH_BINARY);//二值化
	//imshow("二值化后", src_binary);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(10, 10), Point(-1, -1));
	Mat dstImage_Open;
	morphologyEx(src_binary, dstImage_Open, MORPH_OPEN, kernel, Point(-1, -1));
	imshow("开运算处理后", dstImage_Open);

	Mat labels;
	Mat stats;
	Mat centroids;
	int num = connectedComponentsWithStats(dstImage_Open, labels, stats, centroids, 8, CV_32S);
	cout << "焊点个数：" << num - 1 << endl;

	//使用不同的颜色标记连通域
	//std::vector<cv::Vec3b> colors(num);
	//colors[0] = cv::Vec3b(0, 0, 0);//背景黑色

	//for (int i = 1; i < num; i++)
	//{
	//	colors[i] = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
	//}
	//Mat dst = Mat::zeros(src.size(), src.type());
	//int w = src.cols;
	//int h = src.rows;
	//for (int row = 0; row < h; row++)
	//{
	//	for (int col = 0; col < w; col++)
	//	{
	//		int label = labels.at<int>(row, col);
	//		if (label == 0) continue;
	//		dst.at<Vec3b>(row, col) = colors[label];
	//	}
	//}
	//imshow("连通域标记", dst);

	//标记连通域

	for (int i = 1; i < num; i++)
	{
		Vec2d pt = centroids.at<Vec2d>(i, 0);//二维数组
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);
		//cout << "连通域中心的矩阵" << endl;
		//cout << pt[0] << "," << pt[1] << endl;
		//cout << "状态矩阵" << endl;
		//cout << x << "," << y << "," << width << "," << height << "," << area << endl;

		rectangle(src, Rect(x, y, width, height), Scalar(0, 255, 255), 3, 8, 0);
	}
	imshow("连通域标记图像", src);

	waitKey(0);
	system("pause");
}
