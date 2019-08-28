#include<iostream>
#include"БъЭЗ.h"
using namespace std;



int main(void){

	string LEDPicName = "8.bmp";



	Point2f srcCorner[4] = { Point2f(4089, 2135), Point2f(625, 2139), Point2f(622, 855), Point2f(4096, 873) };

	Size picSize;
	picSize.width = sqrt((srcCorner[0].x - srcCorner[1].x)*(srcCorner[0].x - srcCorner[1].x) + (srcCorner[0].y - srcCorner[1].y)*(srcCorner[0].y - srcCorner[1].y));
	picSize.height = sqrt((srcCorner[2].x - srcCorner[1].x)*(srcCorner[2].x - srcCorner[1].x) + (srcCorner[2].y - srcCorner[1].y)*(srcCorner[2].y - srcCorner[1].y));

	picSize = picSize + Size(picSize.width / (resolution.width - 1), picSize.height / (resolution.height - 1));

	srcCorner[0] = srcCorner[0] + Point2f(picSize.width / (2 * (resolution.width - 1)), picSize.height / (2 * (resolution.height - 1)));
	srcCorner[1] = srcCorner[1] + Point2f(-picSize.width / (2 * (resolution.width - 1)), picSize.height / (2 * (resolution.height - 1)));
	srcCorner[2] = srcCorner[2] + Point2f(-picSize.width / (2 * (resolution.width - 1)), -picSize.height / (2 * (resolution.height - 1)));
	srcCorner[3] = srcCorner[3] + Point2f(picSize.width / (2 * (resolution.width - 1)), -picSize.height / (2 * (resolution.height - 1)));




	Point2f dstCorner[4] = { Point2f(picSize.width, picSize.height), Point2f(0, picSize.height), Point2f(0, 0),Point2f(picSize.width, 0) };


	Point3 init;
	init.LT = Point(0, 0);
	init.Center = Point(0, 0);
	init.RB = Point(0, 0);


	Mat H33(3, 3, CV_32FC1);
	H33 = getPerspectiveTransform(srcCorner, dstCorner);
	//cout << H33;
	Mat aa = imread(LEDPicName, 1);
	//GaussianBlur(aa, aa, Size(5, 15), 0.5);
	Mat qq = Mat::zeros(aa.size(), aa.type());
	warpPerspective(aa, qq, H33, picSize);
	imwrite("WCUT.bmp", qq);


	Point3** dotMatrix;
	dotMatrix = (Point3**)malloc(sizeof(Point3*)*resolution.height);
	for (int i = 0; i < resolution.height; i++)
		dotMatrix[i] = (Point3*)malloc(sizeof(Point3)*resolution.width);

	for (int i = 0; i < resolution.height; i++)
		for (int j = 0; j < resolution.width; j++)
			dotMatrix[i][j] = init;

	Point3** dstDotMatrix;
	dstDotMatrix = (Point3**)malloc(sizeof(Point3*)*resolution.height);
	for (int i = 0; i < resolution.height; i++)
		dstDotMatrix[i] = (Point3*)malloc(sizeof(Point3)*resolution.width);

	for (int i = 0; i < resolution.height; i++)
		for (int j = 0; j < resolution.width; j++)
			dstDotMatrix[i][j] = init;

	dotDetect(qq, 1, dotMatrix,resolution);
	sortEveryRow(dotMatrix, dstDotMatrix, picSize, resolution);


	Mat cc;
	qq.copyTo(cc);
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 80; j++){
			//circle(cc, dstDotMatrix[i][j], 4, Scalar(255), 1);
			if (sum(qq(Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB)))(0)<20)
				rectangle(cc, Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB), Scalar(0, 255, 0), 1);
			else
				rectangle(cc, Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB), Scalar(255, 0, 0), 1);
		}
	imwrite("check.bmp", cc);

	free(dotMatrix);
	free(dstDotMatrix);


	return 0;
}