#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include "QLabel"
#include <QLayout>
#include <QFile>
#include <QPainter>
#include <pixitem.h>
#include <QLayoutItem>
#include <QMessagebox>
#include "globalvar.h"
#include <QDebug>
#include "imageAlgorithm.h"
#include "func.h"
#include "qpicturebox.h"

PixItem *m_pixItem;
PixItem *m_pixItem1;

Camera* camera;
bool isSnap = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	
    ui->setupUi(this);
#ifdef _DEBUG
	mytime.start();
	qDebug() << "timer start:" << mytime.elapsed() << "ms" << endl;
#endif // _DEBUG

	//this->loadStyleSheet(":/miniLED_vs/myStyleSheet.qss");
	this->loadStyleSheet(":/miniLED_vs/QSS-master/ElegantDark.qss");
    //QLayout* layout_Pic=new QLayout(widget3);
	ui->stackedWidget->setCurrentIndex(0);

    ui->lineEdit_ExposureTime->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->lineEdit_Aperture->setValidator(new QRegExpValidator(QRegExp("[0-9]+\.+[0-9]+$")));

    ui->statusBar->showMessage("就绪",3000);

	/*
    QGraphicsScene *m_graphicsScene=new QGraphicsScene;
    m_graphicsScene->setSceneRect(0,0,ui->verticalLayout_11->geometry().x(), ui->verticalLayout_11->geometry().y());
    QPixmap *pixmap=new QPixmap(":/miniLED_vs/CachedImage_1920_1080_POS3.jpg");
    m_pixItem=new PixItem(pixmap);
    m_graphicsScene->addItem(m_pixItem);
    m_pixItem->setPos(0,0);
    m_graphicsView=new QGraphicsView();
    m_graphicsView->setScene(m_graphicsScene);
    m_graphicsView->setMinimumSize(ui->verticalLayout_11->geometry().x(), ui->verticalLayout_11->geometry().y());
    ui->verticalLayout_11->addWidget(m_graphicsView);

	
    QGraphicsScene *m_graphicsScene1=new QGraphicsScene;
    m_graphicsScene1->setSceneRect(0, 0, ui->verticalLayout_11->geometry().x(), ui->verticalLayout_11->geometry().y());
    QPixmap *pixmap1=new QPixmap(":/miniLED_vs/CachedImage_1920_1080_POS3.jpg");
    m_pixItem1=new PixItem();
	m_pixItem1->setPixmap(pixmap1);
    m_graphicsScene1->addItem(m_pixItem1);
    m_pixItem1->setPos(0,0);
    m_graphicsView1=new QGraphicsView();
    m_graphicsView1->setScene(m_graphicsScene1);
    m_graphicsView1->setMinimumSize(ui->verticalLayout_11->geometry().x(), ui->verticalLayout_11->geometry().y());
    ui->verticalLayout_12->addWidget(m_graphicsView1);
	*/
	QPixmap *pixmap1 = new QPixmap(":/miniLED_vs/pic/图片1.png");
	QPixmap *pixmap2 = new QPixmap(":/miniLED_vs/pic/图片2.png");
	ui->pictureBox_Capture->setPixmap(pixmap2);
	ui->pictureBox_CameraShow->setPixmap(pixmap1);
	QPixmap icon1(":/pic/pic/d1.png");
	QPixmap icon2(":/pic/pic/d2.png");
	QPixmap icon3(":/pic/pic/d3.png");
	QPixmap icon4(":/pic/pic/d4.png");
	const QSize iconSize(60, 60);
	ui->pushButton_Direction1->setIcon(icon1);
	ui->pushButton_Direction1->setIconSize(iconSize);

	ui->pushButton_Direction2->setIcon(icon2);
	ui->pushButton_Direction2->setIconSize(iconSize);

	ui->pushButton_Direction3->setIcon(icon3);
	ui->pushButton_Direction3->setIconSize(iconSize);
	
	ui->pushButton_Direction4->setIcon(icon4);
	ui->pushButton_Direction4->setIconSize(iconSize);
	
	ui->pictureBox_Capture->setIsDrawMarkPoints(true);
    camera=new Camera();
    //connect(camera,SIGNAL(cameraImgReady(QPixmap*)),this->m_pixItem,SLOT(on_CameraReceived(QPixmap*)));
	camera->QSetCallback(mCameraCallback);

	client = new Client(this);
	
	if (client->ConnectedSuccess())ui->statusBar->showMessage("Server connectd success", 3000);
	else ui->statusBar->showMessage("Server connectd failed", 3000);

	

	colorRdoGroup = new QButtonGroup(this);
	colorRdoGroup->addButton(ui->radioButton_testBlack);
	colorRdoGroup->addButton(ui->radioButton_testWhite);
	colorRdoGroup->addButton(ui->radioButton_testRed);
	colorRdoGroup->addButton(ui->radioButton_testGreen);
	colorRdoGroup->addButton(ui->radioButton_testBlue);

	colorRdoGroup->setId(ui->radioButton_testRed, 0);
	colorRdoGroup->setId(ui->radioButton_testGreen, 1);
	colorRdoGroup->setId(ui->radioButton_testBlue, 2);
	colorRdoGroup->setId(ui->radioButton_testWhite, 3);
	colorRdoGroup->setId(ui->radioButton_testBlack, 4);
	connect(colorRdoGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(on_colorRdoGroup_check(int, bool)));

	colorBtnGroup = new QButtonGroup(this);
	colorBtnGroup->addButton(ui->pushButton_Normal, 0);
	colorBtnGroup->addButton(ui->pushButton_Red, 1);
	colorBtnGroup->addButton(ui->pushButton_Green, 2);
	colorBtnGroup->addButton(ui->pushButton_Blue, 3);
	colorBtnGroup->addButton(ui->pushButton_White, 4);
	connect(colorBtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_colorBtnGroup_checked(int)));

	addSubBtnGroup = new QButtonGroup(this);
	addSubBtnGroup->addButton(ui->pushButton_Plus, 0);
	addSubBtnGroup->addButton(ui->pushButton_Sub, 1);
	connect(addSubBtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_addSubBtnGroup_Clicked(int)));

	sndColor = new QColor(0, 0, 0);
	//调试使用过的。
#if 0
	this->arrayR = new float[globalVar.ScreenWidth*globalVar.ScreenHeight];
	this->arrayG = new float[globalVar.ScreenWidth*globalVar.ScreenHeight];
	this->arrayB = new float[globalVar.ScreenWidth*globalVar.ScreenHeight];
	this->arrayW = new float[globalVar.ScreenWidth*globalVar.ScreenHeight];
	for (int i = 0; i < globalVar.ScreenWidth*globalVar.ScreenHeight; i++) { arrayR[i] = 1.0; arrayG[i] = 1.0;arrayB[i] = 1.0;arrayW[i] = 1.0;	}
#endif
	myModel = new MyTableModel(this,QColor(255,0,0),globalVar.ScreenWidth,globalVar.ScreenHeight,globalVar.arrayW);
	selectModle = new QItemSelectionModel(myModel);
	bool isCon=connect(selectModle, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(on_tableView_CurrentChanged(QModelIndex, QModelIndex)));
	qDebug() << ui->pushButton_Red->isCheckable();
	//调试算法时使用过的
#if 0
	qDebug() << isCon << endl;
	qDebug() << "Aolgrithm start:" << mytime.elapsed() << "ms" << endl;
	QImage imgIn("test.bmp"), imgOut;
	int target;
	ImageAlgorithm::GL_compensation(imgIn, 100, 2.8f, imgOut, target);
	qDebug() << "Aolgrithm end" << mytime.elapsed() << "ms" << endl;
#endif
}
void MainWindow::loadStyleSheet(const QString &styleSheetFile)
{
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if(file.isOpen())
    {
        QString styleSheet=this->styleSheet();
        styleSheet +=QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
        file.close();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_OutlineGap_clicked(bool checked)
{
    ui->lineEdit_OutlineUp->setEnabled(checked);
    ui->lineEdit_OutlineDown->setEnabled(checked);
    ui->lineEdit_OutlineLeft->setEnabled(checked);
    ui->lineEdit_OutlineRight->setEnabled(checked);
}

void MainWindow::on_pushButton_ParameterSet_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_CameraCalibration_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_PickPicture_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_CalibrationResult_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
bool firstDrawTable = true;

void MainWindow::on_pushButton_PointsCalibration_clicked()
{
	ui->stackedWidget->setCurrentIndex(4);

	//表格显示：设置表格的行列数。

	//if (firstDrawTable) {
	//	ui->tableWidget_ShowEveryPoint->setColumnCount(globalVar.ScreenWidth);
	//	ui->tableWidget_ShowEveryPoint->setRowCount(globalVar.ScreenHeight);
	//	ui->tableWidget_ShowEveryPoint->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	//	ui->tableWidget_ShowEveryPoint->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	//	this->arrayR = new Array2D<float>(globalVar.ScreenWidth, globalVar.ScreenHeight, 1.0);
	//	this->arrayG = new Array2D<float>(globalVar.ScreenWidth, globalVar.ScreenHeight, 1.0);
	//	this->arrayB = new Array2D<float>(globalVar.ScreenWidth, globalVar.ScreenHeight, 1.0);
	//	//给系数赋值


	//	//
	//	firstDrawTable = false;
	//}

	if (firstDrawTable) {

		ui->tableView_everyPoint->setModel(this->myModel);
		ui->tableView_everyPoint->setSelectionModel(this->selectModle);
		firstDrawTable = false;
	}


}


void MainWindow::on_comboBox_SelectConnectWay_currentIndexChanged(int index)
{
    ui->stackedWidget_ConnectWay->setCurrentIndex(index);
}

void MainWindow::on_horizontalSlider_ExposureTime_sliderMoved(int position)
{
    ui->lineEdit_ExposureTime->setText(QString::number(position));

}

void MainWindow::on_lineEdit_Aperture_editingFinished()
{
    //Aperture must be in range(1.0,23.0);
    float setValue=ui->lineEdit_Aperture->text().toFloat();
    if(setValue>23.0f)setValue=23.0f;
    else if(setValue<1.0f)setValue=1.0f;
    ui->lineEdit_Aperture->setText(QString("%1").arg(double(setValue)));
}


void MainWindow::on_dial_brightness_sliderMoved(int position)
{
    ui->lineEdit_brightness->setText(QString::number(position));
}

void MainWindow::on_pushButton_ConnectCamera_clicked()
{
    
    if(ui->pushButton_ConnectCamera->text()=="连接相机")
    {

		//cwt.start();
		if (!camera->QOpen()) {
			ui->statusBar->showMessage("Failed when connected to camera!");
			return;
		}
		//QThread::msleep(4000);
		camera->QGrabbing();
        int expNum=camera->QGetExposureTime();
		if (expNum == -1) 
		{
			QMessageBox::warning(this, "READ ERROR", "读取曝光时间出错!");
			return;
		}

        ui->lineEdit_ExposureTime->setText(QString::number(expNum));
        ui->lineEdit_ExposureTime_2->setText(QString::number(expNum));
        ui->lineEdit_ExposureTime_3->setText(QString::number(expNum));
        ui->pushButton_ConnectCamera->setText("断开相机");
    }
    else
    {
		if (camera->QAbort())
		{
		
			if (camera->QClose()) 
			{
				ui->pushButton_ConnectCamera->setText("连接相机");

			}
			else QMessageBox::warning(this, "CLOSE ERROR", "无法关闭相机!");
			return;
		}
		else
		{
			QMessageBox::warning(this, "ABORT ERROR", "无法停止相机采集!");
		}

    }
}

void mCameraCallback(byte *imgData, int width, int height)
{
	//pbx1->setData(imgData,width,height);
	//if (isSnap) {
	//	globalVar.snapData = imgData;
	//	pbx2->setData(imgData, width, height);
	//	isSnap = false;
	//}
}

void MainWindow::on_lineEdit_ExposureTime_returnPressed()
{
    QString expNumStr=ui->lineEdit_ExposureTime->text();
    if(expNumStr=="")
    {
        QMessageBox::warning(this,"NULL ERROR","曝光时间不能为空!");
    }
    else
    {
        int expNum=expNumStr.toInt();
        if(expNum<0 || expNum>1000000)
        {
            QMessageBox::warning(this,"VALUE ERROR","曝光时间必须在0~1000000之间!");
            ui->lineEdit_ExposureTime->setText("1000");
        }
        else
        {
            camera->QSetExposureTime(expNum);
            ui->lineEdit_ExposureTime_2->setText(expNumStr);
            ui->lineEdit_ExposureTime_3->setText(expNumStr);
        }
    }
}

void MainWindow::on_pushButton_Confirm_clicked()
{

}
void setColor(QColor &color, int r, int g, int b) {
	color.setRed(r); color.setGreen(g); color.setBlue(b);
}
void MainWindow::on_colorRdoGroup_check(int id, bool isChecked)
{
	uchar value = ui->lineEdit_brightness->text().toUInt();

	switch (id) {
	case 0:
		setColor(*sndColor, value, 0, 0);
		break;
	case 1:
		setColor(*sndColor, 0, value, 0);
		break;
	case 2:
		setColor(*sndColor, 0, 0, value);
		break;
	case 3:
		setColor(*sndColor, value, value, value);
		break;
	case 4:
		setColor(*sndColor, 0, 0, 0);
		break;
	default:
		break;

	}
	if (isChecked)this->client->sendShowColor(*sndColor);
}

void MainWindow::on_lineEdit_brightness_textChanged(QString)
{
	int id = colorRdoGroup->checkedId();
	uchar value = ui->lineEdit_brightness->text().toUInt();

	switch (id) {
	case 0:
		setColor(*sndColor, value, 0, 0);
		break;
	case 1:
		setColor(*sndColor, 0, value, 0);
		break;
	case 2:
		setColor(*sndColor, 0, 0, value);
		break;
	case 3:
		setColor(*sndColor, value, value, value);
		break;
	case 4:
		setColor(*sndColor, 0, 0, 0);
		break;
	default:
		break;

	}
	
	this->client->sendShowColor(*sndColor);

	
}
//0->正常（不变） ， 1->红  ，2->绿 ， 3->蓝， 4->白。
void MainWindow::on_colorBtnGroup_checked(int id)
{
	switch (id) {
	case 0:
		this->myModel->setFacData(globalVar.ScreenWidth,globalVar.ScreenHeight,globalVar.arrayR);
		this->myModel->setBgColor(QColor(255, 0, 0));
		ui->tableView_everyPoint->setModel(this->myModel);
		break;
	case 1:
		this->myModel->setFacData(globalVar.ScreenWidth, globalVar.ScreenHeight,globalVar.arrayR);
		this->myModel->setBgColor(QColor(255, 0, 0));
		ui->tableView_everyPoint->setModel(this->myModel);
		break;
	case 2:
		this->myModel->setFacData(globalVar.ScreenWidth, globalVar.ScreenHeight, globalVar.arrayG);
		this->myModel->setBgColor(QColor(0, 255, 0));
		ui->tableView_everyPoint->setModel(this->myModel);
		break;
	case 3:
		this->myModel->setFacData(globalVar.ScreenWidth, globalVar.ScreenHeight, globalVar.arrayB);
		this->myModel->setBgColor(QColor(0, 0, 255));
		ui->tableView_everyPoint->setModel(this->myModel);
		break;
	case 4:
		this->myModel->setFacData(globalVar.ScreenWidth, globalVar.ScreenHeight, globalVar.arrayW);
		this->myModel->setBgColor(QColor(255, 255, 255));
		ui->tableView_everyPoint->setModel(this->myModel);
		break;
	}
	ui->tableView_everyPoint->setFocus();

	//QTableWidgetItem *twi = new QTableWidgetItem("0");

	//switch (id) {
	//	//Normal:显示当前屏幕画面。目前先用R代替。
	//case 0:
	//	for (int i = 0; i < arrayR->getWidth(); i++)
	//	{
	//		for (int j = 0; j < arrayR->getHeight(); j++)
	//		{
	//			QTableWidgetItem *twi= new QTableWidgetItem(QString("1%").arg(arrayR->get(i, j)));
	//			twi->setBackgroundColor(QColor(255, 0, 0));
	//			ui->tableWidget_ShowEveryPoint->setItem(i, j, twi);
	//		}
	//	}
	//	break;
	//case 1:

	//	for (int i = 0; i < arrayR->getWidth(); i++)
	//	{
	//		for (int j = 0; j < arrayR->getHeight(); j++)
	//		{
	//			QTableWidgetItem *twi = new QTableWidgetItem(QString::number(arrayR->get(i, j)));
	//			twi->setBackgroundColor(QColor(255, 0, 0));
	//			twi->setSizeHint(QSize(30, 30));
	//			ui->tableWidget_ShowEveryPoint->setColumnWidth(i, 30);
	//			ui->tableWidget_ShowEveryPoint->setItem(j, i, twi);
	//		}
	//	}
	//	break;
	//case 2:
	//	for (int i = 0; i < arrayG->getWidth(); i++)
	//	{
	//		for (int j = 0; j < arrayG->getHeight(); j++)
	//		{
	//			QTableWidgetItem *twi = new QTableWidgetItem(QString::number(arrayG->get(i, j)));
	//			twi->setBackgroundColor(QColor(0, 255, 0));
	//			twi->setSizeHint(QSize(30, 30));
	//			ui->tableWidget_ShowEveryPoint->setColumnWidth(i, 30);
	//			ui->tableWidget_ShowEveryPoint->setItem(j,i, twi);
	//		}
	//	}
	//	break;
	//case 3:
	//	for (int i = 0; i < arrayB->getWidth(); i++)
	//	{
	//		for (int j = 0; j < arrayB->getHeight(); j++)
	//		{
	//			QTableWidgetItem *twi = new QTableWidgetItem(QString::number(arrayB->get(i, j)));
	//			twi->setBackgroundColor(QColor(0, 0, 255));
	//			twi->setSizeHint(QSize(30, 30));
	//			ui->tableWidget_ShowEveryPoint->setColumnWidth(i, 30);
	//			ui->tableWidget_ShowEveryPoint->setItem(j,i, twi);
	//		}
	//	}
	//	break;
	//}

}

void MainWindow::on_pushButton_Plus_clicked()
{
	//QString curValue = ui->comboBox_SelectDeltaValue->currentText();
	//float delta = 0.0f;
	//if (curValue == "0.02" || curValue == "0.01" || curValue == "0.005")delta = curValue.toFloat();
	//else if (curValue == "5%")delta = 5.0f / 100.0f;
	//else if (curValue == "2%")delta = 2.0f / 100.0f;
	//else if (curValue == "1%")delta = 1.0f / 100.0f;
	//else if (curValue == "1/63")delta = 1.0f / 63.0f;
	//else if (curValue == "1/255")delta = 1.0f / 255.0f;
	//else;

	//QString curText = ui->tableWidget_ShowEveryPoint->currentItem()->text();
	//float curValueFloat = curText.toFloat();
	//curValueFloat += delta;
	//QTableWidgetItem *item = new QTableWidgetItem(QString::number(curValueFloat));

}
void MainWindow::on_pushButton_Sub_clicked()
{

}

void MainWindow::on_tableView_CurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
	float fac;
	fac = this->myModel->data(current, Qt::DisplayRole).toFloat();
	ui->lineEdit_CurValue->setText(QString::number(fac));
}

void MainWindow::on_LineEdit_CurValue_Edited()
{
	QString content = ui->lineEdit_CurValue->text();
	QModelIndexList indexList = this->selectModle->selectedIndexes();
	float fac = content.toFloat();
	for each (QModelIndex i in indexList)
	{
		this->myModel->setData(i, fac, Qt::DisplayRole);
	}
	ui->tableView_everyPoint->setFocus();
}

void MainWindow::on_addSubBtnGroup_Clicked(int id)
{
	char sign = '+';
	//先确认是上调还是下调。
	//'+'->上调，'-'->下调。
	switch (id) {
	case 0:
		sign = '+';
		break;
	case 1:
		sign = '-';
		break;
	default:
		sign = '+';
	}
	QString val_str=ui->comboBox_SelectDeltaValue->currentText();
	QString val_str1;
	float val,val_privous;
	if (val_str.endsWith("%")) {
		val_str = val_str.section('%', 0, 0);
		val = val_str.toFloat() / 100.0f;
		if (sign == '+') {
			val += 1.0;
			sign = '*';
		}
		else if (sign == '-') {
			val = 1.0 - val;
			sign = '*';
		}
	}
	else if (val_str.contains("/")) {
		val_str1 = val_str.section('/', 0, 0);
		val_str = val_str.section('/', 1, 1);
		val = val_str1.toFloat() / val_str.toFloat();
		if (sign == '+') {
			val += 1.0;
			sign = '*';
		}
		else if (sign == '-') {
			val = 1.0 - val;
			sign = '*';
		}
	}
	else {
		val = val_str.toFloat();
	}
	QModelIndexList indexList = this->selectModle->selectedIndexes();
	for each (QModelIndex i in indexList)
	{
		this->myModel->alterData(i, sign, val);
	}
	ui->tableView_everyPoint->setFocus();
}

void MainWindow::on_pushButton_snap_Clicked()
{
	isSnap = true;
	ui->statusBar->showMessage("Snap ready.",1500);
}

void MainWindow::on_pushButton_analysis_Clicked()
{
	//QPixmap *pix = pbx2->getPixmap();
	//MarkPoints markpoints;
	//markpoints.x1 = pix->width()*globalVar.markPointFacxRD;
	//markpoints.y1 = pix->height()*globalVar.markPointFacyRD;
	//markpoints.x2 = pix->width()*globalVar.markPointFacxLD;
	//markpoints.y2 = pix->height()*globalVar.markPointFacyLD;
	//markpoints.x3 = pix->width()*globalVar.markPointFacxLU;
	//markpoints.y3 = pix->height()*globalVar.markPointFacyLU;
	//markpoints.x4 = pix->width()*globalVar.markPointFacxRU;
	//markpoints.y4 = pix->height()*globalVar.markPointFacyRU;
	//if (globalVar.snapData == nullptr)return;
	//int* lightData = getLightSum(pix->width(), pix->height(), globalVar.snapData, markpoints);
	//int target;
	//ImageAlgorithm::GL_compensation(lightData, COLS, ROWS, 100, 2.8, globalVar.arrayW, target);
}

