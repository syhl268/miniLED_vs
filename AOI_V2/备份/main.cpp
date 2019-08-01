/*
 vvoltage:6.52V
 exp time: 500us
 loop:

*/
#define LOCALPATH "./Result/"

#include"func.h"
#include<fstream>
using namespace std;
using namespace cv;
#include "stb_image.h"
#include <math.h>
#include <opencv2/core.hpp>
void main(void){

	char* testFName="右下角.bmp";

	if (isFirstCall){
		Mat FFC = imread("FFC.bmp", 0);
		double sum = 0.0f;
		for (int i = 0; i < FFC.size().height; i++){
			for (int j = 0; j < FFC.size().width; j++){
				sum += (int)FFC.at<uchar>(i, j);
			}
		}
		Mat FFCout;
		FFC.copyTo(FFCout);
		sum /= double(FFC.size().height*FFC.size().width);
		//ofstream outFileFac("outFac.csv");
		for (int i = 0; i < FFC.size().height; i++){
			for (int j = 0; j < FFC.size().width; j++){
				fac[i][j] = FFC.at<uchar>(i, j) / sum;

			}
		}
		isFirstCall = false;
	}
	Mat inputMat = imread(testFName,0);
	for (int i = 0; i < inputMat.size().height; i++){
		for (int j = 0; j < inputMat.size().width; j++){
			if (inputMat.at<uchar>(i,j)!=0){
				inputMat.at<uchar >(i, j) = round(inputMat.at<uchar>(i, j)/fac[i][j]);
			}
		}
	}
	imwrite("testOut.bmp", inputMat);
	


	string markFileName = "qqq.bmp";
	string LEDPicName = "testOut.bmp";

	Point2f dstCorner[4] = { Point2f(123+6, 140+6), Point2f(0, 140+6), Point2f(0, 0), Point2f(123+6, 0) };
	Point2f srcCorner[4] = { Point2f( 4516+3, 2635+3), Point2f(4393-3,2640+3), Point2f(4389-3,2500-3), Point2f(4513+3,2495-3) };



	Point3 init;
	init.LT = Point(0, 0);
	init.Center = Point(0, 0);
	init.RB = Point(0, 0);


	Mat H33(3, 3, CV_32FC1);
	H33 = getPerspectiveTransform(srcCorner, dstCorner);
	Mat aa = imread(LEDPicName, 1);
	//GaussianBlur(aa, aa, Size(5, 15), 0.5);
	Mat qq = Mat::zeros(aa.size(), aa.type());
	warpPerspective(aa, qq, H33, Size(W, H));
	imwrite("qqqq.bmp",qq);

	cout << "end" << endl;

	//Point2f dstCorner[4] = { Point2f(3830, 1470), Point2f(0, 1470), Point2f(0, 0), Point2f(3830, 0) };
	////Point2f srcCorner[4] = { Point2f(4422, 2190), Point2f(641, 2198), Point2f(631, 777), Point2f(4416, 744) };
	////Point2f srcCorner[4] = { mark[0], mark[1], mark[3], mark[2] };
	//Point2f srcCorner[4] = { Point2f(4145+15, 2025+15), Point2f(753-15, 2085+15),Point2f(735-15, 816-15), Point2f(4128+15, 796-15) };

	//Point3 init;
	//init.LT = Point(0, 0);
	//init.Center = Point(0, 0);
	//init.RB = Point(0, 0);


	//Mat H33(3, 3, CV_32FC1);
	//H33 = getPerspectiveTransform(srcCorner, dstCorner);
	//Mat aa = imread(LEDPicName, 1);
	//GaussianBlur(aa, aa, Size(5, 15), 0.5);
	//Mat qq = Mat::zeros(aa.size(), aa.type());
	//warpPerspective(aa, qq, H33, Size(3830, 1470));

	//imwrite("wrap.bmp", qq);

	Point3 dotMatrix[20][18] = { init };

	dotDetect(qq, 1, dotMatrix);
	//dotDetect(qq.t(), 0, dotMatrix);
	
	Point3 dstDotMatrix[20][18] = { init };

	sortEveryRow(dotMatrix, dstDotMatrix, Size(W, H));
	Mat cc;
	qq.copyTo(cc);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 18; j++){
			//circle(cc, dstDotMatrix[i][j], 4, Scalar(255), 1);
			rectangle(cc, Rect(dstDotMatrix[i][j].LT , dstDotMatrix[i][j].RB), Scalar(255), 1);
		}
	imwrite("check.bmp", cc);
	//cout << (int)qq.at<Vec3b>(dstDotMatrix[4][74].y, dstDotMatrix[4][74].x)[0] << endl;
	int res[20][18] = { 0 };
	ofstream outfile, outfile1;
	outfile.open( "out0514_2.csv", ios::out);
	outfile1.open("右下角.csv", ios::out);
	//outfile << "TIME" << ',' << "MACHINENAME" << ',' << "RECEIPE" << ',' << "ID" << ',' << "NG_X" << ',' << "NG_Y" << ',' << "NG_STATUS" << endl;
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 18; j++){
			res[i][j] = sum(qq(Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB)))(0);
			outfile <<res[i][j] << ',';
			outfile1 << res[i][j] << ',';
		}
		outfile1 << endl;
	}
	outfile.close();
	outfile1.close();
//	summ = summ / numm;
//
//
//	int maxx = 0;
//	int minn = 10000;
//	int n = 0;
//	int mmm = 0;
//	cout << summ<<endl;
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//
//			if (res[i][j] > summ * 3)
//			{
//				cout << "在第" << i + 1 << "行，" << "第" << j + 1 << "列处爆灯" << endl;
//				cout << res[i][j]<<endl;
//				n++;
//			}
//			if (res[i][j] <= summ*0.05)
//			{
//				cout << "在第" << i + 1 << "行，" << "第" << j + 1 << "列处灭灯" << endl;
//				mmm++;
//			}
//			if (res[i][j] < summ / 2 && res[i][j] >= (summ / 4))
//			{
//				//cout << "在第" << i + 1 << "行，" << "第" << j + 1 << "列处亮度不达标" << endl;
//			}
//
//			if (res[i][j] < (summ*2) && res[i][j]>(summ*25/100)){
//				if (maxx < res[i][j])
//					maxx = res[i][j];
//				if (minn>res[i][j])
//					minn = res[i][j];
//			}
//		}
//	}
//	cout << n<<","<<mmm<<endl;
//	cout << float(minn) / float(maxx) << endl;
//
//
//int width, height, channel;
//BYTE* data=stbi_load("3.bmp", &width, &height, &channel, 0);
//int dstWidth, dstHeight, dstStep;
//int test[5];
//cout << sizeof(test) << endl;
//memset(test, 0, 4);
//AOIHist(data, width, height, dstWidth,dstHeight,dstStep);
	//system("Pause");
	return ;
}


AOIAPI float init(){
	/*
	Mat FFC = imread("FFC.bmp",0);
	float sum = 0.0f;
	for (int i = 0; i < FFC.size().height; i++){
		for (int j = 0; j < FFC.size().width; j++)
			sum+= (float)FFC.at<uchar>(i, j);
	}
	sum /= float(FFC.size().height*FFC.size().width);
	for (int i = 0; i < FFC.size().height; i++){
		for (int j = 0; j < FFC.size().width; j++)
			fac[i][j] = (float)FFC.at<uchar>(i, j) /sum;
	}
	return sum;
	*/

	return 0;
}

//BYTE* ImageSC(int srcPicWidth, int srcPicHeight, BYTE* srcPicData, MarkPoints markpoints, int& dstwidth, int& dstheight, int& dststep){
//	if (isFirstCall){
//		Mat FFC = imread("FFC.bmp", 0);
//		float sum = 0.0f;
//		for (int i = 0; i < FFC.size().height; i++){
//			for (int j = 0; j < FFC.size().width; j++){
//				sum += (int)FFC.at<uchar>(i, j);
//			}
//		}
//		sum /= float(FFC.size().height*FFC.size().width);
//		for (int i = 0; i < FFC.size().height; i++){
//			for (int j = 0; j < FFC.size().width; j++){
//				fac[i][j] = (int)FFC.at<uchar>(i, j) / sum;
//			}
//		}
//		isFirstCall = false;
//	}
//	Point2f dstCorner[4] = { Point2f(3830, 1470), Point2f(0, 1470), Point2f(0, 0), Point2f(3830, 0) };
//	//Point2f srcCorner[4] = { Point2f(4422, 2190), Point2f(641, 2198), Point2f(631, 777), Point2f(4416, 744) };
//	//Point2f srcCorner[4] = { mark[0], mark[1], mark[3], mark[2] };
//	Point2f srcCorner[4] = { Point2f(markpoints.x4 + 15, markpoints.y4 + 15), Point2f(markpoints.x3 - 15, markpoints.y3 + 15), Point2f(markpoints.x1 - 15, markpoints.y1 - 15), Point2f(markpoints.x2 + 15, markpoints.y2 - 15) };
//
//
//
//	Point3 init;
//	init.LT = Point(0, 0);
//	init.Center = Point(0, 0);
//	init.RB = Point(0, 0);
//
//	Mat H33(3, 3, CV_32FC1);
//	H33 = getPerspectiveTransform(srcCorner, dstCorner);
//	//mat构造来自C#的数据。BGR8格式
//	Mat aa(srcPicHeight, srcPicWidth, CV_8UC3, srcPicData);
//	
//	for (int i = 0; i < srcPicHeight; i++){
//		for (int j = 0; j < srcPicWidth; j++){
//			aa.at<Vec3b >(i, j) = aa.at<Vec3b>(i, j) / fac[i][j];
//		}
//	}
//
//	GaussianBlur(aa, aa, Size(5, 15), 0.5);
//	Mat qq = Mat::zeros(aa.size(), aa.type());
//	warpPerspective(aa, qq, H33, Size(3830, 1470));
//
//	Point3 dotMatrix[20][18] = { init };
//	dotDetect(qq, 1, dotMatrix);
//	//dotDetect(qq.t(), 0, dotMatrix);
//	Point3 dstDotMatrix[20][18] = { init };
//	sortEveryRow(dotMatrix, dstDotMatrix, Size(3830, 1470));
//
//	//cout << (int)qq.at<Vec3b>(dstDotMatrix[4][74].y, dstDotMatrix[4][74].x)[0] << endl;
//
//
//
//	CvSize cvsize; cvsize.width = 2 * 80; cvsize.height = 2*30;
//	IplImage* uu = cvCreateImage(cvsize, IPL_DEPTH_8U, 3);
//	Mat mhist = cvarrToMat(uu);
//	int res[30][80] = { 0 };
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//			res[i][j] = sum(qq(Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB)))(0);
//			Scalar rectColor = getColor(0, 40000, res[i][j]);
//			//Scalar rectColor = getColor(0, 255, (int)qq.at<Vec3b>(dstDotMatrix[i][j].Center)[0]);
//			rectangle(mhist, Rect(j * 2, i * 2, 2, 2), rectColor);
//
//		}
//	}
//
//	//imshow("aa", mhist);
//	//waitKey(0);
//
//
//	dstwidth = mhist.size().width;
//	dstheight = mhist.size().height;
//	dststep = mhist.step;
//	return mhist.data;
//}
//
//BYTE* AOIHist(int srcPicWidth, int srcPicHeight, BYTE* srcPicData, MarkPoints markpoints, int& dstwidth, int& dstheight, int& dststep){
//
//	Point2f dstCorner[4] = { Point2f(3830, 1470), Point2f(0, 1470), Point2f(0, 0), Point2f(3830, 0) };
//	//Point2f srcCorner[4] = { Point2f(4422, 2190), Point2f(641, 2198), Point2f(631, 777), Point2f(4416, 744) };
//	//Point2f srcCorner[4] = { mark[0], mark[1], mark[3], mark[2] };
//	Point2f srcCorner[4] = { Point2f(markpoints.x4 + 15, markpoints.y4 + 15), Point2f(markpoints.x3 - 15, markpoints.y3 + 15), Point2f(markpoints.x1 - 15, markpoints.y1 - 15), Point2f(markpoints.x2 + 15, markpoints.y2 - 15) };
//
//
//
//	Point3 init;
//	init.LT = Point(0, 0);
//	init.Center = Point(0, 0);
//	init.RB = Point(0, 0);
//
//
//	Mat H33(3, 3, CV_32FC1);
//	H33 = getPerspectiveTransform(srcCorner, dstCorner);
//	//mat构造来自C#的数据。BGR8格式
//	Mat aa(srcPicHeight, srcPicWidth, CV_8UC3, srcPicData);;
//	GaussianBlur(aa, aa, Size(5, 15), 0.5);
//	Mat qq = Mat::zeros(aa.size(), aa.type());
//	warpPerspective(aa, qq, H33, Size(3830, 1470));
//
//	Point3 dotMatrix[30][80] = { init };
//	dotDetect(qq, 1, dotMatrix);
//	//dotDetect(qq.t(), 0, dotMatrix);
//	Point3 dstDotMatrix[30][80] = { init };
//	sortEveryRow(dotMatrix, dstDotMatrix, Size(3830, 1470));
//
//	//cout << (int)qq.at<Vec3b>(dstDotMatrix[4][74].y, dstDotMatrix[4][74].x)[0] << endl;
//	int res[30][80] = { 0 };
//	int ls[30 * 80] = { 0 };
//
//
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//			ls[i*80+j]=(int)qq.at<Vec3b>(dstDotMatrix[i][j].Center)[0];
//		}
//	}
//	int hist[256];
//	memset(hist, 0, sizeof(hist));
//	for (int i = 0; i < 2400; i++){hist[ls[i]]++;}
//	CvSize cvsize; cvsize.width = 2 * 256; cvsize.height = 150;
//	IplImage* uu = cvCreateImage(cvsize, IPL_DEPTH_8U, 3);
//	Mat mhist = cvarrToMat(uu);
//	for (int i = 0; i < 256; i++){
//		int y = mhist.size().height - hist[i];
//		if (y < 0)y = 0;
//		rectangle(mhist, Rect(2 * i,y , 2, mhist.size().height), Scalar(0,0,0), 1);
//	}
//	//imshow("aa", mhist);
//	//waitKey(0);
//
//
//	dstwidth = mhist.size().width;
//	dstheight = mhist.size().height;
//	dststep = mhist.step;
//	return mhist.data;
//}
//
//
//
//
//
//BYTE* Analysis(char* markPic, char* srcPic, Thres thres, float& uniform, char* strId, char* time, char* saveFName){
//	
//	string markFileName(markPic);
//	string LEDPicName(srcPic);
//	/*
//	Point2f dstCorner[4] = { Point2f(3830, 1470), Point2f(0, 1470), Point2f(0, 0), Point2f(3830, 0) };
//	Point2f srcCorner[4] = { Point2f(4422, 2190), Point2f(641, 2198), Point2f(631, 777), Point2f(4416, 744) };
//	*/
//	Mat img = imread(markFileName, 1);
//	cvtColor(img, img, CV_RGB2GRAY);
//	threshold(img, img, 240, 255, THRESH_OTSU);
//
//	vector<vector<Point>> contours;
//	vector<Vec4i> h;
//	vector<Point> mark;
//	findContours(img, contours, h, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//	Point3 init;
//	init.LT = Point(0, 0);
//	init.Center = Point(0, 0);
//	init.RB = Point(0, 0);
//
//
//
//	for (int i = 0; i < h.size(); i++){
//		int sumx = 0, sumy = 0;
//		for (int j = 0; j < contours[i].size(); j++){
//			sumx += contours[i][j].x;
//			sumy += contours[i][j].y;
//		}
//		mark.push_back(Point(sumx / contours[i].size(), sumy / contours[i].size()));
//	}
//	Point2f dstCorner[4] = { Point2f(3830, 1470), Point2f(0, 1470), Point2f(0, 0), Point2f(3830, 0) };
//	//Point2f srcCorner[4] = { Point2f(4422, 2190), Point2f(641, 2198), Point2f(631, 777), Point2f(4416, 744) };
//	//Point2f srcCorner[4] = { mark[0], mark[1], mark[3], mark[2] };
//	Point2f srcCorner[4] = { Point2f(4037 + 15, 2373 + 15), Point2f(622 - 15, 2396 + 15), Point2f(643 - 15, 1156 - 15), Point2f(4003 + 15, 1134 - 15) };
//
//
//
//	Mat H33(3, 3, CV_32FC1);
//	H33 = getPerspectiveTransform(srcCorner, dstCorner);
//	Mat aa = imread(LEDPicName, 1);
//	GaussianBlur(aa, aa, Size(5, 15), 0.5);
//	Mat qq = Mat::zeros(aa.size(), aa.type());
//	warpPerspective(aa, qq, H33, Size(3830, 1470));
//
//	Point3 dotMatrix[30][80] = {init};
//	dotDetect(qq, 1, dotMatrix);
//	//dotDetect(qq.t(), 0, dotMatrix);
//	Point3 dstDotMatrix[30][80] = { init };
//	sortEveryRow(dotMatrix, dstDotMatrix, Size(3830, 1470));
//	//cout << (int)qq.at<Vec3b>(dstDotMatrix[4][74].y, dstDotMatrix[4][74].x)[0] << endl;
//	int res[30][80] = { 0 };
//	BYTE ls[30 * 80] = { 0 };
//	int index = 0;
//	int maxx = 0;
//	int minn = 1000;
//	int summ = 0;
//	int numm = 0;
//
//	Mat cc;
//	qq.copyTo(cc);
//	ofstream outfile;
//	outfile.open(string(saveFName) + ".csv", ios::out);
//
//	outfile << "TIME" << ',' << "MACHINENAME" << ',' << "RECEIPE" << ','<<"ID"<<',' << "NG_X" << ',' << "NG_Y" << ',' << "NG_STATUS" << endl;
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//			res[i][j] = sum(qq(Rect(dstDotMatrix[i][j].LT , dstDotMatrix[i][j].RB )))(0);
//				summ += res[i][j];
//				numm++;
//		}
//	}
//	summ = summ / numm;
//
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//			if (res[i][j] > thres.high*summ / 100.0)//250
//			{
//				ls[index] = 1;
//				rectangle(cc, Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB), Scalar(0, 255, 0), 1);
//				outfile << time<<','<<"Printer"<<','<<"1231021Cu"<<','<<strId<<','<< i+1 << ',' << j+1 << ',' << "High" << endl;
//
//			}
//			if (res[i][j] < thres.low*summ / 100.0)//5
//			{
//				ls[index] = 2;
//				rectangle(cc, Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB), Scalar(0, 0, 255), 1);
//				outfile << time << ',' << "Printer" << ',' << "1231021Cu" << ',' << strId << ',' << i+1 << ',' << j +1<< ',' << "Die" << endl;
//
//
//			}
//				index++;
//
//		}
//	}
//	//如果是OK，则输出一行： time "Printer" "1231021Cu" strID -0.0001 -0.0001 OK
//	if (index == 0){
//		outfile << time << ',' << "Printer" << ',' << "1231021Cu" << ',' << strId << ',' << (-0.0001) << ',' << (-0.0001) << ',' << "OK" << endl;
//
//	}
//	uniform = float(minn) / float(maxx);
//	//if (bool_except)ls[0] = 5;
//	outfile.close();
//	imwrite(string(saveFName) + ".jpg", cc);
//	return ls;
//}
//BYTE* Analysis_1(char* markPic, int srcPicWidth, int srcPicHeight, BYTE* srcPicData, Thres thres, float& uniform, char* strId, char* time, char* saveFName){
//	string markFileName(markPic);
//
//	Point2f dstCorner[4] = { Point2f(3830, 1470), Point2f(0, 1470), Point2f(0, 0), Point2f(3830, 0) };
//	//Point2f srcCorner[4] = { Point2f(4422, 2190), Point2f(641, 2198), Point2f(631, 777), Point2f(4416, 744) };
//	//Point2f srcCorner[4] = { mark[0], mark[1], mark[3], mark[2] };
//	Point2f srcCorner[4] = { Point2f(4037 + 15, 2373 + 15), Point2f(622 - 15, 2396 + 15), Point2f(643 - 15, 1156 - 15), Point2f(4003 + 15, 1134 - 15) };
//
//
//
//	Point3 init;
//	init.LT = Point(0, 0);
//	init.Center = Point(0, 0);
//	init.RB = Point(0, 0);
//	
//
//	Mat H33(3, 3, CV_32FC1);
//	H33 = getPerspectiveTransform(srcCorner, dstCorner);
//	//mat构造来自C#的数据。BGR8格式
//	Mat aa(srcPicHeight, srcPicWidth, CV_8UC3, srcPicData);;
//	GaussianBlur(aa, aa, Size(5, 15), 0.5);
//	Mat qq = Mat::zeros(aa.size(), aa.type());
//	warpPerspective(aa, qq, H33, Size(3830, 1470));
//
//	Point3 dotMatrix[30][80] = {init};
//	dotDetect(qq, 1, dotMatrix);
//	//dotDetect(qq.t(), 0, dotMatrix);
//	Point3 dstDotMatrix[30][80] = {init};
//	bool bool_except = false;//如果处理出错，就在返回值中第一个数设置为5
//	try{
//		sortEveryRow(dotMatrix, dstDotMatrix, Size(3830, 1470));
//
//	}
//	catch (Exception e){
//		bool_except = true;
//	}
//
//	//cout << (int)qq.at<Vec3b>(dstDotMatrix[4][74].y, dstDotMatrix[4][74].x)[0] << endl;
//	int res[30][80] = { 0 };
//	BYTE ls[30 * 80] = { 0 };
//	int index = 0;
//	int maxx = 0;
//	int minn = 1000;
//	int summ = 0;
//	int numm = 0;
//
//	Mat cc;
//	qq.copyTo(cc);
//	ofstream outfile;
//	outfile.open(string(saveFName) + ".csv", ios::out);
//
//	outfile << "TIME" << ',' << "MACHINENAME" << ',' << "RECEIPE" << ',' << "ID" << ',' << "NG_X" << ',' << "NG_Y" << ',' << "NG_STATUS" << endl;
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//			res[i][j] = sum(qq(Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB)))(0);
//				summ += res[i][j];
//				numm++;
//		}
//	}
//	summ = summ / numm;
//
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//			if (res[i][j] > thres.high*summ / 100.0)//250
//			{
//				ls[index] = 1;
//				rectangle(cc, Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB), Scalar(0, 255, 0), 1);
//				outfile << time << ',' << "Printer" << ',' << "1231021Cu" << ',' << strId << ',' << i+1 << ',' << j+1 << ',' << "High" << endl;
//
//			}
//			if (res[i][j] < thres.low*summ / 100.0)//5
//			{
//				ls[index] = 2;
//				rectangle(cc, Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB), Scalar(0, 0, 255), 1);
//				outfile << time << ',' << "Printer" << ',' << "1231021Cu" << ',' << strId << ',' << i+1 << ',' << j+1 << ',' << "Die" << endl;
//
//
//			}
//			index++;
//
//		}
//	}
//	//如果是OK，则输出一行： time "Printer" "1231021Cu" strID -0.0001 -0.0001 OK
//	if (index == 0){
//		outfile << time << ',' << "Printer" << ',' << "1231021Cu" << ',' << strId << ',' << (-0.0001) << ',' << (-0.0001) << ',' << "OK" << endl;
//
//	}
//	uniform = float(minn) / float(maxx);
//	//if (bool_except)ls[0] = 5;
//	outfile.close();
//	imwrite(string(saveFName) + ".jpg", cc);
//	return ls;
//}
//BYTE* Analysis_2(char* markPic, int srcPicWidth, int srcPicHeight, BYTE* srcPicData, Thres thres, MarkPoints markpoints, float& uniform, char* strId, char* time, char* saveFNameOnline, char* saveFNameLocal){
//	string markFileName(markPic);
//
//	Point2f dstCorner[4] = { Point2f(3830, 1470), Point2f(0, 1470), Point2f(0, 0), Point2f(3830, 0) };
//	//Point2f srcCorner[4] = { Point2f(4422, 2190), Point2f(641, 2198), Point2f(631, 777), Point2f(4416, 744) };
//	//Point2f srcCorner[4] = { mark[0], mark[1], mark[3], mark[2] };
//	Point2f srcCorner[4] = { Point2f(markpoints.x4 + 15, markpoints.y4 + 15), Point2f(markpoints.x3 - 15, markpoints.y3 + 15), Point2f(markpoints.x1 - 15, markpoints.y1 - 15), Point2f(markpoints.x2 + 15, markpoints.y2 - 15) };
//
//
//
//	Point3 init;
//	init.LT = Point(0, 0);
//	init.Center = Point(0, 0);
//	init.RB = Point(0, 0);
//
//
//	Mat H33(3, 3, CV_32FC1);
//	H33 = getPerspectiveTransform(srcCorner, dstCorner);
//	//mat构造来自C#的数据。BGR8格式
//	Mat aa(srcPicHeight, srcPicWidth, CV_8UC3, srcPicData);
//	
//	/*for (int i = 0; i < srcPicHeight; i++){
//		for (int j = 0; j < srcPicWidth; j++){
//			aa.at<uchar >(i, j) = (int)(aa.at<uchar>(i, j) / fac[i][j]);
//		}
//	}*/
//	imwrite(string(saveFNameLocal) + ".bmp", aa);
//	GaussianBlur(aa, aa, Size(5, 15), 0.5);
//	Mat qq = Mat::zeros(aa.size(), aa.type());
//	warpPerspective(aa, qq, H33, Size(3830, 1470));
//
//	Point3 dotMatrix[30][80] = { init };
//	dotDetect(qq, 1, dotMatrix);
//	//dotDetect(qq.t(), 0, dotMatrix);
//	Point3 dstDotMatrix[30][80] = { init };
//	bool bool_except = false;//如果处理出错，就在返回值中第一个数设置为5
//	try{
//		sortEveryRow(dotMatrix, dstDotMatrix, Size(3830, 1470));
//
//	}
//	catch (Exception e){
//		bool_except = true;
//	}
//
//	//cout << (int)qq.at<Vec3b>(dstDotMatrix[4][74].y, dstDotMatrix[4][74].x)[0] << endl;
//	int res[30][80] = { 0 };
//	BYTE ls[30 * 80] = { 0 };
//	int index = 0;
//	int maxx = 0;
//	int minn = 1000;
//	int summ = 0;
//	int numm = 0;
//
//	Mat cc;
//	qq.copyTo(cc);
//	ofstream outfile,outfile1;
//	outfile.open(string(saveFNameOnline) + ".csv", ios::out);
//	outfile1.open(string(saveFNameLocal) + "_亮度.csv", ios::out);
//
//	outfile << "TIME" << ',' << "MACHINENAME" << ',' << "RECEIPE" << ',' << "ID" << ',' << "NG_X" << ',' << "NG_Y" << ',' << "NG_STATUS" << endl;
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//			res[i][j] = sum(qq(Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB)))(0);
//			outfile1 << i << ',' << j << ',' << (int)qq.at<Vec3b>(dstDotMatrix[i][j].Center)[0] <<','<< res[i][j]<<endl;
//
//				summ += res[i][j];
//				numm++;
//		}
//	}
//	outfile1.close();
//	summ = summ / numm;
//	int ngCounter = 0;
//	for (int i = 0; i < 30; i++){
//		for (int j = 0; j < 80; j++){
//			if (res[i][j] > thres.high*summ / 100.0)//250
//			{
//				ngCounter++;
//				ls[index] = 1;
//				rectangle(cc, Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB), Scalar(0, 255, 0), 1);
//				outfile << time << ',' << "IMAGE" << ',' << "1231021Cu" << ',' << strId << ',' << i+1 << ',' << j+1 << ',' << "SHORT" << endl;
//
//			}
//			if (res[i][j] < thres.low*summ / 100.0)//5
//			{
//				ngCounter++;
//				ls[index] = 2;
//				rectangle(cc, Rect(dstDotMatrix[i][j].LT, dstDotMatrix[i][j].RB), Scalar(0, 0, 255), 1);
//				outfile << time << ',' << "IMAGE" << ',' << "1231021Cu" << ',' << strId << ',' << i+1 << ',' << j +1<< ',' << "OPEN" << endl;
//
//
//			}
//			index++;
//
//		}
//	}
//	//如果是OK，则输出一行： time "Printer" "1231021Cu" strID -0.0001 -0.0001 OK
//	if (ngCounter == 0){
//		outfile << time << ',' << "IMAGE" << ',' << "1231021Cu" << ',' << strId << ',' << (-0.0001) << ',' << (-0.0001) << ',' << "OK" << endl;
//
//	}
//	uniform =0;
//	//if (bool_except)ls[0] = 5;
//	outfile.close();
//	imwrite(string(saveFNameLocal) + ".jpg", cc);
//	return ls;
//}
//
//void circleOnImg(BYTE* srcData, int srcPicWidth, int srcPicHeight, int px, int py, int radius, int R, int G, int B, int thickness){
//	Mat srcImg(srcPicHeight, srcPicWidth, CV_8UC3, srcData);
//	circle(srcImg, Point(px, py), radius, Scalar(R, G, B), thickness);
//}
//BYTE* ImageRead(char* fname, int& width, int& height, int& step, int& channel){
//	IplImage* uu = cvLoadImage(fname);
//	IplImage* dst1 = cvCreateImage(cvSize(uu->width, uu->height), 8, 1);
//	cvCvtColor(uu, dst1, CV_RGB2GRAY);
//	Mat ss = cvarrToMat(uu);
//	uchar* data = new uchar[uu->width*uu->height * 3];
//	data = ss.data;
//	width = ss.size().width;
//	height = ss.size().height;
//	step = ss.step;
//	channel = ss.channels();
//	return data;
//}
//BYTE* ImageHist(BYTE* data, int srcwidth, int srcheight, int srcstep, int srcchannel, int &dstwidth, int &dstheight, int& step, int &dstchannel){
//	CvSize cvsize; cvsize.width = 2 * 256; cvsize.height = 700;
//	IplImage* uu = cvCreateImage(cvsize, IPL_DEPTH_8U, 3);
//	Mat hist = cvarrToMat(uu);
//
//	Mat src(srcheight, srcwidth, CV_8UC3, data);
//	int max = 0, r, g, b, pixel;
//	int histArray[256];
//	memset(histArray, 0, sizeof(histArray));
//	int nr = src.rows;
//	int nc = src.cols*src.channels();
//	for (int i = 0; i < nr; i++){
//		uchar* rowdata = src.ptr<uchar>(i);
//		for (int j = 0; j < nc; j += 3){
//			b = (int)rowdata[j + 0];
//			g = (int)rowdata[j + 1];
//			r = (int)rowdata[j + 2];
//			pixel = int(r*0.3 + g*0.59 + b*0.11);
//			histArray[pixel]++;
//			if (max < histArray[pixel])max = histArray[pixel];
//		}
//	}
//	Rect rect[256];
//	for (int i = 0; i < 256; i++){
//		histArray[i] = int(cvsize.height*histArray[i] / (float)max);
//		rect[i] = Rect(2 * i, cvsize.height - histArray[i], 2, histArray[i]);
//		rectangle(hist, rect[i], Scalar(0, 0, 0));
//	}
//	dstwidth = hist.size().width;
//	dstheight = hist.size().height;
//	dstchannel = hist.channels();
//	step = hist.step;
//	return hist.data;
//}
////y(x)=512.0f*sin(float(x-10000)/(10000.0f)*pi/2)+512.0f;
//AOIAPI Scalar getColor(int min, int max, int current){
//	int strider = max - min+1;
//	float ds = 1024.0f / float(strider);
//	float currentIndex = (current - min)*ds;
//
//	//颜色阶梯分为5个阶段：(0,0,0,)->(0,0,255)->(0,255,255)->(255,255,0)->(255,0,0)->(0,0,0)
//	if (0 <= currentIndex && currentIndex < 256){
//		return Scalar(currentIndex, 0,0 );
//	}
//	else if (256 <= currentIndex && currentIndex < 256 * 2){
//		currentIndex -= 256;
//		return Scalar(255, currentIndex, 0);
//	}
//	else if (256 * 2 <= currentIndex && currentIndex < 256 * 3){
//		currentIndex -= 2 * 256;
//		return Scalar( 255 - currentIndex, 255,currentIndex);
//	}
//	else if (256 * 3 <= currentIndex && currentIndex < 256 * 4){
//		currentIndex -= 3 * 256;
//		return Scalar(0, 255 - currentIndex, 255);
//	}
//	//else {
//	//	currentIndex -= 4 * 256;
//	//	return Scalar( 0, 0,255 - currentIndex);
//	//}
//
//
//}
//Scalar getColor_1(int min, int max, int current){
//	float current_d = 512.0*sin(float(current - 10000) / 30000.0f*3.1415926 / 2.0f) + 512.0;
//	return getColor(1, 1024, (int)current_d);
//}