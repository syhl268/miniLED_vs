#include<iostream>
#include<opencv2\opencv.hpp>
using namespace cv;
using namespace std;
#define AOIAPI extern "C" __declspec(dllexport)

//#define W 969+16
//#define H 1107+16
//
//#define W 3537
//#define H 1312
#define resolution Size(80 ,30)


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

	return SUM + 1;
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
			out[i] = 1;
		else
			out[i] = 0;
	}
	out[0] = 1;
}

void dotDetect(cv::Mat src, int p, Point3** dotMatrix, Size Resolution){

	cv::Size s = src.size();
	cv::Mat gray(s, CV_32FC1);
	cv::Mat edge(s, CV_32FC1);
	vector<Point> center;
	vector<int> x;
	vector<int> y;
	vector<vector<Point>> contours;
	vector<Vec4i> h;

	vector<Point> MINP(contours.size());
	vector<Point> MAXP(contours.size());



	cvtColor(src, edge, CV_RGB2GRAY);

	threshold(edge, edge, 10, 255, THRESH_BINARY);//100   50 50 20 20 50 50 50 50 10

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
		MINP.push_back(Point(minX, minY));
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
		int k = Resolution.height;
		int l = 0;
		int* aaa = (int *)malloc(sizeof(int)*Resolution.height*Resolution.width);

		calColIdx(y, aaa);
		//vector<vector<Point>> dotMatrix;
		for (int i = 0; i < (Resolution.height*Resolution.width) && i<center.size(); i++){
			if (aaa[i] == 1){
				k--;
				l = 0;
			}
			
			dotMatrix[k][l].Center = center[i];
			dotMatrix[k][l].LT = MINP[i];
			dotMatrix[k][l].RB = MAXP[i];
			l++;
		}

	}
}

int calGap(Point data[], int dimension, Size Resolution){
	int res = 10000;
	switch (dimension){
	case 1:
		for (int j = 1; j < Resolution.width; j++){
			if (data[j].x == 0) break;
			if (res>abs(data[j].x - data[j - 1].x))
				res = abs(data[j].x - data[j - 1].x);

		}
		return res;
	case 2:
		for (int j = Resolution.height; j >= 0; j--){
			if (data[j - 1].y == 0) break;
			if (res>abs(data[j].y - data[j - 1].y))
				res = abs(data[j].y - data[j - 1].y);

		}
		return res;
	}

}

void sortEveryRow(Point3** dotMatrix, Point3** dstDotMatrix, Size picSize, Size Resolution){

	int W = picSize.width;
	int H = picSize.height;
	vector<int> index;

	Point3 ttmp;
	ttmp.Center = Point(0, 0);
	ttmp.LT = Point(0, 0);
	ttmp.RB = Point(0, 0);
	for (int i = 0; i < Resolution.height; i++){
		for (int j = 0; j < Resolution.width - 1; ++j){
			for (int k = 0; k < Resolution.width - 1 - j; ++k){
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
	//Point tmppp[79] = { Point(0, 0) };
	Point* tmppp = (Point*)malloc(sizeof(Point)*Resolution.width);
	for (int i = 0; i < Resolution.width; i++){
		tmppp[i] = dotMatrix[Resolution.height - 1][i].Center;
	}
	int ColGap = calGap(tmppp, 1,resolution);

	//Point row[90] = { Point(0, 0) };
	Point* row = (Point*)malloc(sizeof(Point)*Resolution.height);

	for (int i = 0; i <Resolution.height; i++)
		row[i] = dotMatrix[i][0].Center;
	int RowGap = calGap(row, 2, resolution);

	int MINy = 10000;
	int MAXy = 0;
	for (int i = 0; i < Resolution.height; i++){

		if (MINy > dotMatrix[i][0].Center.y && dotMatrix[i][0].Center.y != 0)
			MINy = dotMatrix[i][0].Center.y;
		if (MAXy < dotMatrix[i][0].Center.y &&  dotMatrix[i][0].Center.y != 0)
			MAXy = dotMatrix[i][0].Center.y;
	}

	int topGap = floor((MINy - 0) / RowGap);
	int bottomGap = floor((picSize.height - MAXy) / RowGap);






	int MINx = 10000;
	for (int i = 0; i < Resolution.height; i++){
		if (MINx > dotMatrix[i][0].Center.x&& dotMatrix[i][0].Center.x != 0)
			MINx = dotMatrix[i][0].Center.x;
	}

	int MAXx = 0;
	for (int i = 0; i < Resolution.height; i++){
		for (int j = Resolution.width - 1; j >= 0; j--){
			if (dotMatrix[i][j].Center.x != 0)
				if (MAXx < dotMatrix[i][j].Center.x)
					MAXx = dotMatrix[i][j].Center.x;
		}

	}

	int leftGap = floor((MINx - 0) / ColGap);
	int rightGap = floor((picSize.width - MAXx) / ColGap);

	int sum_midd_row = 0;
	for (int i = Resolution.height - 2; i >0; i--){
		if (dotMatrix[i][0].Center.y != 0){
			sum_midd_row += round((dotMatrix[i + 1][0].Center.y - dotMatrix[i][0].Center.y) / RowGap - 1);
		}
	}

	int midd_gap = 0;

	for (int i = 0 + topGap + bottomGap + sum_midd_row; i < Resolution.height; i++){

		//cout << endl;
		if (i > 1){
			midd_gap += round((dotMatrix[i][0].Center.y - dotMatrix[i - 1][0].Center.y) / RowGap) - 1;
		}


		if (dotMatrix[i][Resolution.width - 1].Center.x != 0)
		{
			//cout << "第" << i + 1<<"行无缺失";
			for (int j = 0; j < Resolution.width; j++){
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center = dotMatrix[i][j].Center;
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT = dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center - Point(ColGap / 2, RowGap / 2);
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB = dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center + Point(ColGap / 2, RowGap / 2);
				if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT.x < 0) dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT.x = 0;
				if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT.y < 0) dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT.y = 0;
				if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB.x>W) dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB.x = W;
				if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB.y >H) dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB.y = H;
			}
			continue;
		}

		//cout << "第" << i + 1<<"有缺失，缺失的列标为：" ;

		int k = round(abs(dotMatrix[i][0].Center.x - MINx) / ColGap);
		k = k + leftGap;
		/*计算起始位置缺失个数以及缺失位置坐标*/
		for (int j = 0; j < k; ++j){
			dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center = Point(dotMatrix[i][0].Center.x - round((k - j)*ColGap), dotMatrix[i][0].Center.y);

			dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x - ColGap / 2),
				(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y - RowGap / 2));
			dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x + ColGap / 2),
				(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y + RowGap / 2));

		}

		/*计算中间位置缺失个数以及缺失位置坐标*/
		int nn = 0;
		dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k] = dotMatrix[i][nn];
		dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x - ColGap / 2),
			(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y - RowGap / 2));
		dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.x + ColGap / 2),
			(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center.y + RowGap / 2));
		k++;
		nn++;


		while (k<Resolution.width && dotMatrix[i][nn].Center.x != 0){

			int gapNum = round((dotMatrix[i][nn].Center.x - dotMatrix[i][nn - 1].Center.x) / ColGap);
			for (int m = 1; m < gapNum; m++){
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k].Center = Point(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][k - 1].Center.x + ColGap, dotMatrix[i][nn].Center.y);
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
		for (int j = 0; j < Resolution.width; j++){
			if (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x == 0){
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center = dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j - 1].Center + Point(ColGap, 0);
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x - ColGap / 2),
					(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y - RowGap / 2));
				dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.x + ColGap / 2),
					(dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row + midd_gap][j].Center.y + RowGap / 2));
				//cout << j+1 << ",";
			}
		}


	}

	//top缺失整行补全
	for (int i = topGap - 1; i >= 0; i--){
		for (int j = 0; j < Resolution.width; j++){
			dstDotMatrix[i][j].Center.x = dstDotMatrix[i + 1][j].Center.x;
			dstDotMatrix[i][j].Center.y = dstDotMatrix[i + 1][j].Center.y - RowGap;
			dstDotMatrix[i - bottomGap - sum_midd_row][j].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.x - ColGap / 2),
				(dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.y - RowGap / 2));
			dstDotMatrix[i - bottomGap - sum_midd_row][j].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.x + ColGap / 2),
				(dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.y + RowGap / 2));
		}
	}



	//bottom缺失整行补全
	for (int i = Resolution.height - bottomGap; i <Resolution.height; i++){
		for (int j = 0; j < Resolution.width; j++){
			dstDotMatrix[i][j].Center.x = dstDotMatrix[i - 1][j].Center.x;
			dstDotMatrix[i][j].Center.y = dstDotMatrix[i - 1][j].Center.y + RowGap;
			dstDotMatrix[i - bottomGap - sum_midd_row][j].LT = Point((dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.x - ColGap / 2) < 0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.x - ColGap / 2),
				(dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.y - RowGap / 2)<0 ? 0 : (dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.y - RowGap / 2));
			dstDotMatrix[i - bottomGap - sum_midd_row][j].RB = Point((dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.x + ColGap / 2)>W ? W : (dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.x + ColGap / 2),
				(dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.y + RowGap / 2)>H ? H : (dstDotMatrix[i - bottomGap - sum_midd_row][j].Center.y + RowGap / 2));
		}
	}


	for (int i = 0; i < Resolution.height; i++){
		for (int j = 0; j < Resolution.width; j++){
			if (dstDotMatrix[i][j].Center.x == 0){
				dstDotMatrix[i][j].Center.x = dstDotMatrix[i - 1][j].Center.x;
				dstDotMatrix[i][j].Center.y = dstDotMatrix[i - 1][j].Center.y + RowGap;
				dstDotMatrix[i][j].LT = dstDotMatrix[i][j].Center - Point(ColGap / 2, RowGap / 2);
				dstDotMatrix[i][j].RB = dstDotMatrix[i][j].Center + Point(ColGap / 2, RowGap / 2);
				if (dstDotMatrix[i][j].LT.x < 0) dstDotMatrix[i][j].LT.x = 0;
				if (dstDotMatrix[i][j].LT.y < 0) dstDotMatrix[i][j].LT.y = 0;
				if (dstDotMatrix[i][j].RB.x>W) dstDotMatrix[i][j].RB.x = W;
				if (dstDotMatrix[i][j].RB.y >H) dstDotMatrix[i][j].RB.y = H;
			}
		}
	}


}




double fac[3248][4872] = { 0 };
