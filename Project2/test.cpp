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
		Mat getStructuringElement(int shape, Size ksize, Point anchor = Point(-1,-1));	//�ṹ����
		Mat dst;
		Mat kernel = getStructuringElement(MORPH_RECT, Size (3,3), Point(-1, -1));
		//��ʴ
		/*erode(src,dst,kernel);
		imshow("fushi", dst);*/
		//����
		/*dilate(src, dst, kernel);
		imshow("pengzhang", dst);*/
		//������
		//morphologyEx(src, dst, 2, kernel, Point(-1, -1));
		//imshow("open", dst);
		//������
		morphologyEx(src, dst, 3, kernel, Point(-1, -1));
		imshow("close", dst);
		waitKey(0); 
}

void test2()
{
    Mat src = imread("E:/C++demo/Project2/04/1.jpg", 0);
	Mat image;
	threshold(src, image, 100, 255, THRESH_BINARY);//��ֵ��
	imshow("image", image);
	Mat labels;
	Mat stats;
	Mat centroids;
	int num = connectedComponentsWithStats(image, labels, stats, centroids,8,CV_32S);
	imshow("labels", labels);
	cout << "Ӳ����=" << num - 1 << endl;
	
	
}



void test3()
{
	Mat src = imread("E:/C++demo/Project2/04/2.jpg", 0);
	Mat image;
	threshold(src, image, 100, 255, THRESH_OTSU);//��ֵ��
	imshow("image", image);

	
	
	
	waitKey(0); //�ȴ��û�����
	system("pause");
}


int main()
{
	//test1();
	test2();
	//test3();
	system("pause");
	return 0;
}
