#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
//限定最大类别
const int MAX_CLUSTERS = 5;
//生成五种颜色
Scalar colorTab[] =
{
	Scalar(0,0,255),
	Scalar(0,255,0),
	Scalar(255,100,100),
	Scalar(255, 0, 255),
	Scalar(0,255,255)
};
//生成二维空间
Mat img(500, 500, CV_8UC3);
//随机数生成类
RNG rng(12345);
//K-means
int test1() 
{
	for (;;)
	{
		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1);
		int i, sampleCount = rng.uniform(1, 1001);
		Mat points(sampleCount, 1, CV_32FC2), labels;

		clusterCount = MIN(clusterCount, sampleCount);
		std::vector<Point2f> centers;

		/* generate random sample from multigaussian distribution */
		for (k = 0; k < clusterCount; k++)
		{
			Point center;
			center.x = rng.uniform(0, img.cols);
			center.y = rng.uniform(0, img.rows);
			Mat pointChunk = points.rowRange(k*sampleCount / clusterCount,
				k == clusterCount - 1 ? sampleCount :
				(k + 1)*sampleCount / clusterCount);
			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
		}

		randShuffle(points, 1, &rng);

		double compactness = kmeans(points, clusterCount, labels,
			TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

		img = Scalar::all(0);

		for (i = 0; i < sampleCount; i++)
		{
			int clusterIdx = labels.at<int>(i);
			Point ipt = points.at<Point2f>(i);
			circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
		}
		for (i = 0; i < (int)centers.size(); ++i)
		{
			Point2f c = centers[i];
			circle(img, c, 40, colorTab[i], 1, LINE_AA);
		}
		cout << "Compactness: " << compactness << endl;

		imshow("clusters", img);

		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}
	return 0;
}
//抠图
int createMaskByKmeans(cv::Mat src, cv::Mat & mask)
{
	if ((mask.type() != CV_8UC1) || (src.size() != mask.size()))
		return 0;

	int width = src.cols;
	int height = src.rows;

	int pixNum = width * height;
	int clusterCount = 2;
	Mat labels;
	Mat centers;

	//制作kmeans用的数据
	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	//执行kmeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	//制作mask
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			mask.at<uchar>(row, col) = fg[labels.at<int>(row*width + col)];
		}
	}
		return 0;
}
void segColor()
{
	Mat src = imread("E:/C++demo/image/15.jpg");

	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	createMaskByKmeans(src, mask);

	imshow("src", src);
	imshow("mask", mask);

	waitKey(0);

}
//特效
//融合算法

int test3()
{
	VideoCapture capture, capture_TV;
	capture.open("E:/C++demo/小猫.mp4");
	capture_TV.open("E:/C++demo/小鞠.mp4");
	double scale = 0.5;
	VideoWriter writer;
	writer.open("./my1.flv", writer.fourcc('F', 'L', 'V', '1'), 30, Size(1366, 768), true);//CAP_OPENCV_MJPEG

	Mat frame;
	Mat hsv, green_mask, green_mask_bin;
	vector<Vec4i>hierarchy;
	std::vector<std::vector<Point>> contours;
	Mat result, background, mask;

	while (capture.read(frame))
	{
		//寻找绿幕
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), green_mask);
		threshold(green_mask, green_mask_bin, 100, 255, THRESH_OTSU);
		findContours(green_mask_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));

		vector <vector<Point>>::iterator iter = contours.begin();
		for (; iter != contours.end();)
		{
			double g_dConArea = contourArea(*iter);
			if (g_dConArea < 290000 || g_dConArea > 320000)
			{
				iter = contours.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		if (contours.size() == 0)
		{
			frame.copyTo(result);

			imshow("ImageShow2", frame);
			imshow("ImageShow", result);
			writer.write(result);
		}

		capture_TV.read(background);
		drawContours(mask, contours, -1, Scalar(255), CV_FILLED);
		
		for (int i = 0; i < (int)contours.size(); i++)
		{
			Rect rect1 = boundingRect(Mat(contours[i]));
			resize(background, background, rect1.size());
			int h = frame.rows;
			int w = frame.cols;
			//int bg_row = 0;
			//dims = frame.channels();
			for (int row = 0; row < h; row++)
			{
				uchar* current = frame.ptr<uchar>(row);
				//uchar* bgrow = background.ptr<uchar>(bg_row);
				uchar* maskrow = mask.ptr<uchar>(row);
				uchar* targetrow = result.ptr<uchar>(row);
				int m;
				for (int col = 0; col < w; col++)
				{
					m = *maskrow++;
					if (m == 255)
					{
						*targetrow++ = background.at<Vec3b>(row - rect1.y, col - rect1.x)[0];
						*targetrow++ = background.at<Vec3b>(row - rect1.y, col - rect1.x)[1];
						*targetrow++ = background.at<Vec3b>(row - rect1.y, col - rect1.x)[2];
						current += 3;

					}
					else if (m == 0)
					{
						*targetrow++ = *current++;
						*targetrow++ = *current++;
						*targetrow++ = *current++;
					}
				}
			}
		}
		waitKey(2);
		//imshow("ImageShow2", frame);
		//imshow("ImageShow1", background);
		imshow("ImageShow", result);
		writer.write(result);
	}

	return 0;

}
void main()
{
	//test1();
	//segColor();
	test3();
}

