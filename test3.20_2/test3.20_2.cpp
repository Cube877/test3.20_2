// test3.20_2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "stdlib.h"

using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("E:\\Picture\\coin.png");
	Mat grayMat;
	Mat srcMat_b;
	Mat dst_dilate;
	Mat labels;
	Mat stats;
	Mat centroids;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	
	cvtColor(srcMat, grayMat, COLOR_BGR2GRAY);
	threshold(grayMat, srcMat_b, 100, 255, THRESH_OTSU);
	dilate(srcMat_b, dst_dilate, kernel);
	Mat result = srcMat_b;
	int t = connectedComponentsWithStats(dst_dilate, labels, stats, centroids);
	int count = t - 1;
	for (int i = 1; i < t; i++)
	{
		Rect bndbox;
		bndbox.x = stats.at<int>(i, 0);
		bndbox.y = stats.at<int>(i, 1);
		bndbox.width = stats.at<int>(i, 2);
		bndbox.height = stats.at<int>(i, 3);
		rectangle(result, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("srcMat", srcMat);
	imshow("result", result);
	cout << "硬币数量：" << count << endl;
	waitKey();
    return 0;
}

