#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
#define AOIAPI extern "C" __declspec(dllexport)

#define W 123+6
#define H 140+6

typedef struct Point3{
	Point LT;
	Point Center;
	Point RB;
}Point3;



int calNumCol(vector<int> y){
	vector<int> y1;
	y1.push_back(y[0]);
	for (int i = 0; i < y.size() - 1; i++){
		y1.push_back(y[i]);
	}

	vector<int> y2;
	int maxVal = 0;
	for (int i = 0; i < y1.size(); i++){
		int tt = y1[i] - y[i];
		y2.push_back(tt);
		if (tt > maxVal)
			maxVal = tt;
	}
	int SUM = 0;
	for (int i = 0; i < y2.size(); i++){
		double k = double(y2[i]) / maxVal;
		if (k > 0.5)
			SUM++;
	}
	
	return SUM+1;
}

void calColIdx(vector<int> y, int* out){
	vector<int> y1;
	y1.push_back(y[0]);
	for (int i = 0; i < y.size() - 1; i++){
		y1.push_back(y[i]);
	}

	vector<int> y2;
	int maxVal = 0;
	for (int i = 0; i < y1.size(); i++){
		int tt = y1[i] - y[i];
		y2.push_back(tt);
		if (tt > maxVal)
			maxVal = tt;
	}
	int SUM = 0;
	for (int i = 0; i < y2.size(); i++){
		double k = double(y2[i]) / maxVal;
		if (k>0.3)
		out[i]=1;
		else
			out[i]=0;
	}
	out[0] = 1;
}

void dotDetect(cv::Mat src,int p,Point3 dotMatrix[][18]){

	cv::Size s = src.size();
	cv::Mat gray(s,CV_32FC1);
	cv::Mat edge(s, CV_32FC1);
	vector<Point2f> center;
	vector<int> x;
	vector<int> y;
	vector<vector<Point>> contours;
	vector<Vec4i> h;

	vector<Point> MINP(contours.size());
	vector<Point> MAXP(contours.size());
	


	cvtColor(src, edge, CV_RGB2GRAY);
	
	threshold(edge, edge, 0, 255, CV_THRESH_OTSU);

	findContours(edge, contours, h, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point>> poly(contours.size());
	for (int i = 0; i < poly.size(); i++){
		approxPolyDP(Mat(contours[i]), poly[i], 5, true);
	}

	
	for (int i = 0; i < contours.size(); i++){
		int minX = 10000, maxX = 0;
		int minY = 10000, maxY = 0;
		for (int j = 0; j < contours[i].size(); j++){
			if (minX > contours[i][j].x)
				minX = contours[i][j].x;
			if (minY > contours[i][j].y)
				minY = contours[i][j].y;
			if (maxX<contours[i][j].x)
				maxX = contours[i][j].x;
			if (maxY<contours[i][j].y)
				maxY = contours[i][j].y;
		}
		MINP.push_back(Point(minX,minY));
		MAXP.push_back(Point(maxX, maxY));
	}
	
	

	for (int i = 0; i < contours.size(); i++){
		Point temp(0, 0);
		for (int j = 0; j < contours[i].size(); j++){
			temp.x += contours[i][j].x;
			temp.y += contours[i][j].y;

		}
		temp.x /= contours[i].size();
		temp.y /= contours[i].size();
		center.push_back(temp);
		x.push_back(temp.x);
		y.push_back(temp.y);
	}

	
	//int mm=calNumCol(y);
	//printf("%d\n", mm);

	if (p == 1){
		int k = 20;
		int l = 0;
		int aaa[360];
		calColIdx(y,aaa);
		//vector<vector<Point>> dotMatrix;
		for (int i = 0; i < 360 &&i<center.size(); i++){
			if (aaa[i] == 1){
				k--;
				l=0;
			}
				
			dotMatrix[k][l].Center=center[i];
			dotMatrix[k][l].LT = MINP[i];
			dotMatrix[k][l].RB = MAXP[i];
			l++;
		}
		
	}
}

int calGap(Point data[],int dimension){
	int res = 10000;
	switch (dimension){
	case 1:
		for (int j = 1; j < 18; j++){
			if (data[j].x == 0) break;
			if (res>abs(data[j].x - data[j - 1].x))
				res = abs(data[j].x - data[j - 1].x);

		}
		return res;
	case 2:
		for (int j = 19; j >=0; j--){
			if (data[j-1].y == 0) break;
			if (res>abs(data[j].y - data[j - 1].y))
				res = abs(data[j].y - data[j - 1].y);

		}
		return res;
	}
	
}

void sortEveryRow(Point3 dotMatrix[][18], Point3 dstDotMatrix[][18],Size picSize){

	vector<int> index;

	Point3 ttmp ;
	ttmp.Center = Point(0,0);
	ttmp.LT = Point(0, 0);
	ttmp.RB = Point(0, 0);
	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 18-1; ++j){
			for (int k = 0; k < 18 - 1 - j; ++k){
				if (dotMatrix[i][k].Center.x > dotMatrix[i][k + 1].Center.x && dotMatrix[i][k + 1].Center.x != 0 && dotMatrix[i][k].Center.x != 0){
					ttmp = dotMatrix[i][k];
					dotMatrix[i][k] = dotMatrix[i][k + 1];
					dotMatrix[i][k + 1] = ttmp;
					/*dotMatrix[i][k] = dotMatrix[i][k] + dotMatrix[i][k+1];
					dotMatrix[i][k + 1] = dotMatrix[i][k] - dotMatrix[i][k + 1];
					dotMatrix[i][k] = dotMatrix[i][k] - dotMatrix[i][k + 1];*/
				}
			}
		}
	}
	Point tmppp[18] = {Point(0,0)};
	for (int i = 0; i < 18; i++){
		tmppp[i] = dotMatrix[19][i].Center;
	}
	int ColGap = calGap(tmppp, 1);
	Point row[20] = {Point(0,0)};
	for (int i = 0; i < 20; i++)
		row[i] = dotMatrix[i][0].Center;
	int RowGap = calGap(row,2);

	int MINy = 10000;
	int MAXy = 0;
	for (int i = 0; i < 20 ; i++){

		if (MINy > dotMatrix[i][0].Center.y && dotMatrix[i][0].Center.y != 0)
			MINy = dotMatrix[i][0].Center.y;
		if (MAXy < dotMatrix[i][0].Center.y &&  dotMatrix[i][0].Center.y != 0)
			MAXy = dotMatrix[i][0].Center.y;
	}

	int topGap = floor((MINy - 0) /RowGap);
	int bottomGap = floor((picSize.height - MAXy) / RowGap);






	int MINx = 10000;
	for (int i = 0; i < 20 ; i++){
		if (MINx > dotMatrix[i][0].Center.x&& dotMatrix[i][0].Center.x != 0)
			MINx = dotMatrix[i][0].Center.x;
	}

	int MAXx = 0;
	for (int i = 0; i < 20; i++){
		for (int j = 17; j >= 0; j--){
			if (dotMatrix[i][j].Center.x != 0)
				if (MAXx < dotMatrix[i][j].Center.x)
					MAXx = dotMatrix[i][j].Center.x;
		}
		
	}

	int leftGap = floor((MINx - 0)/ColGap);
	int rightGap = floor((picSize.width - MAXx)/ColGap);

	int sum_midd_row = 0;
	for (int i = 18; i >0; i--){
		if (dotMatrix[i][0].Center.y != 0){
			sum_midd_row += round((dotMatrix[i+1][0].Center.y - dotMatrix[i][0].Center.y)/RowGap -1);
		}
	}

	int midd_gap = 0;

	for (int i = 0+topGap+bottomGap+sum_midd_row; i < 20 ; i++){

		//cout << endl;
		if (i > 1){
			midd_gap += round((dotMatrix[i][0].Center.y - dotMatrix[i - 1][0].Center.y) / RowGap) - 1;
		}


		if (dotMatrix[i][17].Center.x != 0)
		{
			//cout << "第" << i + 1<<"行无缺失";
			for (int j = 0; j < 18; j++){
				dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][j].Center = dotMatrix[i][j].Center;
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT = dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center-Point(ColGap/2,RowGap/2);
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB = dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center + Point(ColGap / 2, RowGap / 2);
				if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT.x < 0) dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT.x = 0;
				if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT.y < 0) dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT.y = 0;
				if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB.x>W) dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB.x = W;
				if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB.y >H) dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB.y = H;
			}
			continue;
		}
		
		//cout << "第" << i + 1<<"有缺失，缺失的列标为：" ;

		int k = round(abs(dotMatrix[i][0].Center.x - MINx) / ColGap) ;
		k = k + leftGap;
		/*计算起始位置缺失个数以及缺失位置坐标*/
		for (int j = 0; j < k; ++j){
			dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][j].Center = Point(dotMatrix[i][0].Center.x - round((k - j)*ColGap), dotMatrix[i][0].Center.y);

			dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x - ColGap / 2),
				(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y - RowGap / 2));
			dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x + ColGap / 2),
				(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y + RowGap / 2));

		}

		/*计算中间位置缺失个数以及缺失位置坐标*/
		int nn = 0;
		dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k] = dotMatrix[i][nn];
		dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].LT = Point((dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center.x - ColGap / 2),
			(dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center.y - RowGap / 2));
		dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].RB = Point((dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center.x + ColGap / 2),
			(dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center.y + RowGap / 2));
		k++;
		nn++;


		while (k<18 && dotMatrix[i][nn].Center.x!=0){

				int gapNum = round((dotMatrix[i][nn].Center.x - dotMatrix[i][nn - 1].Center.x) / ColGap);
				for (int m = 1; m < gapNum; m++){
					dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k].Center = Point(dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][k - 1].Center.x + ColGap, dotMatrix[i][nn].Center.y);
					dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x - ColGap / 2),
						(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y - RowGap / 2));
					dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x + ColGap / 2),
						(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y + RowGap / 2));
					k++;
					//cout << k << ",";
				}

				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center = dotMatrix[i][nn].Center;
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x - ColGap / 2),
					(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y - RowGap / 2));
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x + ColGap / 2),
					(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y + RowGap / 2));

				k++;
				nn++;
		}


		/*计算结尾处缺失个数及其坐标*/
		for (int j = 0; j < 18; j++){
			if (dstDotMatrix[i - bottomGap-sum_midd_row + midd_gap][j].Center.x == 0){
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center = dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j - 1].Center+Point(ColGap,0);
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x - ColGap / 2),
					(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y - RowGap / 2));
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x + ColGap / 2),
					(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y + RowGap / 2));
				//cout << j+1 << ",";
			}
		}


	}

	//top缺失整行补全
	for (int i = topGap-1; i >=0; i--){
		for (int j = 0; j < 18; j++){
			dstDotMatrix[i][j].Center.x = dstDotMatrix[i + 1][j].Center.x;
			dstDotMatrix[i][j].Center.y = dstDotMatrix[i + 1][j].Center.y - RowGap;
			dstDotMatrix[i - bottomGap-sum_midd_row][j].LT = Point((dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.x - ColGap / 2),
				(dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.y - RowGap / 2));
			dstDotMatrix[i - bottomGap-sum_midd_row][j].RB = Point((dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.x + ColGap / 2),
				(dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.y + RowGap / 2));
		}
	}



	//bottom缺失整行补全
	for (int i = 20-bottomGap; i <20 ; i++){
		for (int j = 0; j < 18; j++){
			dstDotMatrix[i][j].Center.x = dstDotMatrix[i - 1][j].Center.x;
			dstDotMatrix[i][j].Center.y = dstDotMatrix[i - 1][j].Center.y + RowGap;
			dstDotMatrix[i - bottomGap-sum_midd_row][j].LT = Point((dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.x - ColGap / 2),
				(dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.y - RowGap / 2));
			dstDotMatrix[i - bottomGap-sum_midd_row][j].RB = Point((dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.x + ColGap / 2),
				(dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap-sum_midd_row][j].Center.y + RowGap / 2));
		}
	}


	for (int i = 0; i < 20; i++){
		for (int j = 0; j < 18; j++){
			if (dstDotMatrix[i][j].Center.x == 0){
				dstDotMatrix[i][j].Center.x = dstDotMatrix[i - 1][j].Center.x ;
				dstDotMatrix[i][j].Center.y = dstDotMatrix[i - 1][j].Center.y + RowGap;
				dstDotMatrix[i][j].LT = dstDotMatrix[i][j].Center - Point(ColGap/2, RowGap/2);
				dstDotMatrix[i][j].RB = dstDotMatrix[i][j].Center + Point(ColGap/2, RowGap/2);
				if (dstDotMatrix[i][j].LT.x < 0) dstDotMatrix[i][j].LT.x = 0;
				if (dstDotMatrix[i][j].LT.y < 0) dstDotMatrix[i][j].LT.y = 0;
				if (dstDotMatrix[i][j].RB.x>W) dstDotMatrix[i][j].RB.x = W;
				if (dstDotMatrix[i][j].RB.y >H) dstDotMatrix[i][j].RB.y = H;
			}
		}
	}


}



typedef struct _Thres{
	int high;
	int middle;
	int low;
}Thres;
typedef struct _ExportInfo{
	char* strId;
	char* saveFname;
	char* time;
}ExportInfo;
typedef struct _MarkPoints{
	int x1, y1;
	int x2, y2;
	int x3, y3;
	int x4, y4;
}MarkPoints;

double fac[3248][4872] = { 0 };
bool isFirstCall = true;
#define BYTE unsigned char
AOIAPI BYTE* Analysis(char* markPic, char* srcPic, Thres thres, float& uniform,char* strId,char* time,char* saveFName);
//如果图片不符合，sort则会出错，然后返回的数的第一个数为5.作为标记
AOIAPI BYTE* Analysis_1(char* markPic, int srcPicWidth, int srcPicHeight, BYTE* srcPicData, Thres thres, float& uniform, char* strId, char* time, char* saveFName);
//鼠标选择mark
AOIAPI BYTE* Analysis_2(char* markPic, int srcPicWidth, int srcPicHeight, BYTE* srcPicData, Thres thres, MarkPoints markpoints, float& uniform, char* strId, char* time, char* saveFNameOnline,char* saveFNameLocal);
//Draw circle on image @srcData @srcPicWidth @srcPicHeight with color @R @G @B , center @px @py and radius @radius.
AOIAPI void circleOnImg(BYTE* srcData, int srcPicWidth, int srcPicHeight, int px, int py, int radius, int R, int G, int B, int thickness);
AOIAPI BYTE* ImageHist(BYTE* data, int srcwidth, int srcheight, int srcstep, int srcchannel, int &dstwidth, int &dstheight, int& step, int &dstchannel);

AOIAPI BYTE* ImageRead(char* fname, int& width, int& height, int& step, int& channel);
AOIAPI BYTE* AOIHist(int srcPicWidth, int srcPicHeight, BYTE* srcPicData, MarkPoints markpoints, int& dstwidth, int& dstheight, int& dststep);
AOIAPI BYTE* ImageSC(int srcPicWidth, int srcPicHeight, BYTE* srcPicData, MarkPoints markpoints, int& dstwidth, int& dstheight, int& dststep);
AOIAPI int* statistic(BYTE* srcdata, int srcwidth, int srcheight);
AOIAPI Scalar getColor(int min, int max, int current);
AOIAPI Scalar getColor_1(int min, int max, int current);

