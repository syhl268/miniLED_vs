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
#include <QDir>
#include <QFileDialog>


PixItem *m_pixItem;
PixItem *m_pixItem1;

Camera* camera;
bool isSnap = false;

QPictureBox *picBox_Show, *picBox_Capture;

void MainWindow::init()
{
	myModel = new MyTableModel(this, QColor(255, 0, 0), globalVar.ScreenWidth, globalVar.ScreenHeight, globalVar.arrayRK);
	selectModle = new QItemSelectionModel(myModel);
	bool isCon = connect(selectModle, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(on_tableView_CurrentChanged(QModelIndex, QModelIndex)));
	ui->tableView_everyPoint->setModel(this->myModel);
	ui->tableView_everyPoint->setSelectionModel(this->selectModle);
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	
    ui->setupUi(this);
#ifdef _DEBUG
	mytime.start();
	qDebug() << "timer start:" << mytime.elapsed() << "ms" << endl;
	qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss") << endl;
#endif // _DEBUG

	//this->loadStyleSheet(":/miniLED_vs/myStyleSheet.qss");
	this->loadStyleSheet(":/miniLED_vs/QSS-master/ElegantDark.qss");
    //QLayout* layout_Pic=new QLayout(widget3);
	ui->stackedWidget->setCurrentIndex(0);

    ui->lineEdit_ExposureTime->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->lineEdit_Aperture->setValidator(new QRegExpValidator(QRegExp("[0-9]+\.+[0-9]+$")));

    ui->statusBar->showMessage("Ready",3000);

	setAllConfigValue();
	picBox_Show = ui->pictureBox_CameraShow;
	picBox_Capture = ui->pictureBox_Capture;
	pixmap1 = new QPixmap(":/miniLED_vs/pic/图片1.png");
	pixmap2 = new QPixmap(":/miniLED_vs/pic/图片2.png");
	//当离线测试开启，但是本地没有测试图片时，通知用户并且将globalVar.isOfflineTest->false;
	Mat m = imread("photo/photo/test.bmp");
	QImage *img = new QImage(m.data, m.cols, m.rows, QImage::Format_RGB888);
	pixmap3 = new QPixmap(QPixmap::fromImage(*img));
	ui->pictureBox_Capture->setPixmap(pixmap2);
	ui->pictureBox_CameraShow->setPixmap(pixmap1);
	QPixmap icon1(":/pic/pic/d1.png");
	QPixmap icon2(":/pic/pic/d2.png");
	QPixmap icon3(":/pic/pic/d3.png");
	QPixmap icon4(":/pic/pic/d4.png");
	for (int i = 0; i < 6; i++) {
		icon_snapSign[i] = QPixmap(QString().sprintf(":/pic/pic/%d.png", i + 1));
	}

	const QSize iconSize(60, 60);
	ui->pushButton_Direction1->setIcon(icon1);
	ui->pushButton_Direction1->setIconSize(iconSize);

	ui->pushButton_Direction2->setIcon(icon2);
	ui->pushButton_Direction2->setIconSize(iconSize);

	ui->pushButton_Direction3->setIcon(icon3);
	ui->pushButton_Direction3->setIconSize(iconSize);
	
	ui->pushButton_Direction4->setIcon(icon4);
	ui->pushButton_Direction4->setIconSize(iconSize);

	ui->pushButton_R1->setIcon(icon_snapSign[0]);
	ui->pushButton_R1->setIconSize(iconSize);
	ui->pushButton_R2->setIcon(icon_snapSign[0]);
	ui->pushButton_R2->setIconSize(iconSize);
	ui->pushButton_G1->setIcon(icon_snapSign[2]);
	ui->pushButton_G1->setIconSize(iconSize);
	ui->pushButton_G2->setIcon(icon_snapSign[2]);
	ui->pushButton_G2->setIconSize(iconSize);
	ui->pushButton_B1->setIcon(icon_snapSign[4]);
	ui->pushButton_B1->setIconSize(iconSize);
	ui->pushButton_B2->setIcon(icon_snapSign[4]);
	ui->pushButton_B2->setIconSize(iconSize);
	ui->pictureBox_Capture->setIsDrawMarkPoints(true);
    camera=new Camera();
    //connect(camera,SIGNAL(cameraImgReady(QPixmap*)),this->m_pixItem,SLOT(on_CameraReceived(QPixmap*)));
	camera->QSetCallback(mCameraCallback);

	client = new Client(this);
	
	if (client->ConnectedSuccess())ui->statusBar->showMessage("Server connectd success", 3000);
	else ui->statusBar->showMessage("Server connectd failed", 3000);

	mainMenuBtnGroup = new QButtonGroup(this);
	mainMenuBtnGroup->addButton(ui->pushButton_ParameterSet, 0);
	mainMenuBtnGroup->addButton(ui->pushButton_CameraCalibration, 1);
	mainMenuBtnGroup->addButton(ui->pushButton_PickPicture, 2);
	mainMenuBtnGroup->addButton(ui->pushButton_CalibrationResult, 3);
	mainMenuBtnGroup->addButton(ui->pushButton_PointsCalibration, 4);
	
	colorRdoGroup = new QButtonGroup(this);
	//colorRdoGroup->addButton(ui->radioButton_testBlack);
	//colorRdoGroup->addButton(ui->radioButton_testWhite);
	colorRdoGroup->addButton(ui->radioButton_testRed,0);
	colorRdoGroup->addButton(ui->radioButton_testGreen,1);
	colorRdoGroup->addButton(ui->radioButton_testBlue,2);

	connect(colorRdoGroup, SIGNAL(buttonToggled(int, bool)), this, SLOT(on_colorRdoGroup_check(int, bool)));

	colorBtnGroup = new QButtonGroup(this);
	colorBtnGroup->addButton(ui->pushButton_SwitchKandB, 0);
	colorBtnGroup->addButton(ui->pushButton_Red, 1);
	colorBtnGroup->addButton(ui->pushButton_Green, 2);
	colorBtnGroup->addButton(ui->pushButton_Blue, 3);
	connect(colorBtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_colorBtnGroup_checked(int)));

	addSubBtnGroup = new QButtonGroup(this);
	addSubBtnGroup->addButton(ui->pushButton_Plus, 0);
	addSubBtnGroup->addButton(ui->pushButton_Sub, 1);
	connect(addSubBtnGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_addSubBtnGroup_Clicked(int)));
	connect(ui->pushButton_Analysis, SIGNAL(clicked()), this, SLOT(on_pushButton_analysis_Clicked()));
	sndColor = new QColor(0, 0, 0);

	checkColorRadioButtonGroup = new QButtonGroup(this);
	checkColorRadioButtonGroup->addButton(ui->radioButton_R1, 0);
	checkColorRadioButtonGroup->addButton(ui->radioButton_R2, 1);
	checkColorRadioButtonGroup->addButton(ui->radioButton_G1, 2);
	checkColorRadioButtonGroup->addButton(ui->radioButton_G2, 3);
	checkColorRadioButtonGroup->addButton(ui->radioButton_B1, 4);
	checkColorRadioButtonGroup->addButton(ui->radioButton_B2, 5);
	connect(checkColorRadioButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_checkRadioButtonGroup_Clicked(int)));

	checkOptionRadioButtonGroup = new QButtonGroup(this);
	checkOptionRadioButtonGroup->addButton(ui->radioButton_PhotoSrc, 0);
	checkOptionRadioButtonGroup->addButton(ui->radioButton_PhotoSrcWarp, 1);
	checkOptionRadioButtonGroup->addButton(ui->radioButton_PhotoSrcLight, 2);
	checkOptionRadioButtonGroup->addButton(ui->radioButton_PhotoRst, 3);
	connect(checkOptionRadioButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_checkRadioButtonGroup_Clicked(int)));

	//调试使用过的。

#if 0
	this->arrayR = new float[globalVar.ScreenWidth*globalVar.ScreenHeight];
	this->arrayG = new float[globalVar.ScreenWidth*globalVar.ScreenHeight];
	this->arrayB = new float[globalVar.ScreenWidth*globalVar.ScreenHeight];
	this->arrayW = new float[globalVar.ScreenWidth*globalVar.ScreenHeight];
	for (int i = 0; i < globalVar.ScreenWidth*globalVar.ScreenHeight; i++) { arrayR[i] = 1.0; arrayG[i] = 1.0;arrayB[i] = 1.0;arrayW[i] = 1.0;	}
#endif
	/*
	myModel = new MyTableModel(this,QColor(255,0,0),globalVar.ScreenWidth,globalVar.ScreenHeight,globalVar.arrayRK);
	selectModle = new QItemSelectionModel(myModel);
	bool isCon=connect(selectModle, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(on_tableView_CurrentChanged(QModelIndex, QModelIndex)));
	ui->tableView_everyPoint->setModel(this->myModel);
	ui->tableView_everyPoint->setSelectionModel(this->selectModle);
	*/
	init();
	//调试算法时使用过的
#if 0
	qDebug() << isCon << endl;
	qDebug() << "Aolgrithm start:" << mytime.elapsed() << "ms" << endl;
	QImage imgIn("test.bmp"), imgOut;
	int target;
	ImageAlgorithm::GL_compensation(imgIn, 100, 2.8f, imgOut, target);
	qDebug() << "Aolgrithm end" << mytime.elapsed() << "ms" << endl;
#endif

	imgAlm = new ImageAlgorithm(globalVar.ScreenWidth,globalVar.ScreenHeight);
	globalVar.photoFileManager.setMainPath(globalVar.WorkPath);
	colorCali = new QColorCali(this);
	
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
	delete client;
	delete colorBtnGroup;
	delete sndColor;
	delete pixmap1, pixmap2, pixmap3;
	delete selectModle;
	delete myModel;

	//delete progressDialog;
	delete imgAlm;
}

void MainWindow::setAllConfigValue()
{
	ui->comboBox_SelectConnectWay->setCurrentText(globalVar.Proto);
	ui->lineEdit_Ip->setText(globalVar.Ip);
	ui->lineEdit_Port->setText(QString::number(globalVar.Port));
	ui->lineEdit_ScreenWidth->setText(QString::number(globalVar.ScreenWidth));
	ui->lineEdit_ScreenHeight->setText(QString::number(globalVar.ScreenHeight));
	ui->lineEdit_BoxWidth->setText(QString::number(globalVar.BoxWidth));
	ui->lineEdit_BoxHeight->setText(QString::number(globalVar.BoxHeight));
	ui->lineEdit_ModuleWidth->setText(QString::number(globalVar.ModuleWidth));
	ui->lineEdit_ModuleHeight->setText(QString::number(globalVar.ModuleHeight));
	ui->checkBox_OutlineGap->setChecked(globalVar.isOutlineGap);
	ui->lineEdit_OutlineUp->setText(QString::number(globalVar.GapUp));
	ui->lineEdit_OutlineDown->setText(QString::number(globalVar.GapDown));
	ui->lineEdit_OutlineLeft->setText(QString::number(globalVar.GapLeft));
	ui->lineEdit_OutlineRight->setText(QString::number(globalVar.GapRight));
	ui->lineEdit_PartWidth->setText(QString::number(globalVar.PartWidth));
	ui->lineEdit_PartHeight->setText(QString::number(globalVar.PartHeight));
	ui->lineEdit_PartHoriNum->setText(QString::number(globalVar.HoriPartNums));
	ui->lineEdit_PartVertiNum->setText(QString::number(globalVar.VertPartNums));
	ui->checkBox_AutoDeleteLocalPhoto->setChecked(globalVar.isAutodeleteLocalPhoto);
	ui->checkBox_OfflineTest->setChecked(globalVar.isOfflineTest);
	ui->lineEdit_FirstGL->setText(QString::number(globalVar.firstGL));
	ui->lineEdit_SecondGL->setText(QString::number(globalVar.secondGL));
	ui->lineEdit_WorkPath->setText(globalVar.WorkPath);
}

void MainWindow::getAllConfigValueToGlobal()
{
	globalVar.Proto = ui->comboBox_SelectConnectWay->currentText();
	globalVar.Ip = ui->lineEdit_Ip->text();
	globalVar.Port = ui->lineEdit_Port->text().toInt();
	globalVar.ScreenWidth = ui->lineEdit_ScreenWidth->text().toInt();
	globalVar.ScreenHeight = ui->lineEdit_ScreenHeight->text().toInt();
	globalVar.BoxWidth = ui->lineEdit_BoxWidth->text().toInt();
	globalVar.BoxHeight = ui->lineEdit_BoxHeight->text().toInt();
	globalVar.ModuleWidth = ui->lineEdit_ModuleWidth->text().toInt();
	globalVar.ModuleHeight = ui->lineEdit_ModuleHeight->text().toInt();
	globalVar.isOutlineGap = ui->checkBox_OutlineGap->isChecked();
	globalVar.GapUp = ui->lineEdit_OutlineUp->text().toInt();
	globalVar.GapDown = ui->lineEdit_OutlineDown->text().toInt();
	globalVar.GapLeft = ui->lineEdit_OutlineLeft->text().toInt();
	globalVar.GapRight = ui->lineEdit_OutlineRight->text().toInt();
	globalVar.PartWidth = ui->lineEdit_PartWidth->text().toInt();
	globalVar.PartHeight = ui->lineEdit_PartHeight->text().toInt();
	globalVar.HoriPartNums = ui->lineEdit_PartHoriNum->text().toInt();
	globalVar.VertPartNums = ui->lineEdit_PartVertiNum->text().toInt();
	globalVar.isOfflineTest = ui->checkBox_OfflineTest->isChecked();
	globalVar.isAutodeleteLocalPhoto = ui->checkBox_AutoDeleteLocalPhoto->isChecked();
	globalVar.firstGL = ui->lineEdit_FirstGL->text().toInt();
	globalVar.secondGL = ui->lineEdit_SecondGL->text().toInt();
	globalVar.WorkPath = ui->lineEdit_WorkPath->text();
	globalVar.photoFileManager.setMainPath(globalVar.WorkPath);


}

void MainWindow::setPhotoStatus()
{
	QPushButton *btns[] = { ui->pushButton_R1,ui->pushButton_R2 ,ui->pushButton_G1 ,ui->pushButton_G2 ,ui->pushButton_B1 ,ui->pushButton_B2 };
	//2*(i/2+1)-1:i/2为整除:0,1,2,3,4,5->1,1,3,3,5,5;   2*(i/2): 0,1,2,3,4,5->0,0,2,2,4,4;
	for (int i = 0; i < 6; i++) {
		if (i < globalVar.photorgb) {
			btns[i]->setIcon(icon_snapSign[2 * (i / 2 + 1) - 1]);
			btns[i]->setDown(false);
		}
		if (i >= globalVar.photorgb) {
			btns[i]->setIcon(icon_snapSign[2 * (i / 2)]);
			btns[i]->setDown(false);
		}
		if (i == globalVar.photorgb)btns[i]->setDown(true);
	}
}


void MainWindow::closeEvent(QCloseEvent * event)
{
	globalVar.writeFile();
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
	//if (globalVar.isOfflineTest && (!QFile("photo/photo/test.bmp").exists())) {
	//	QMessageBox::StandardButton bn = QMessageBox::information(this, "Warnning", "File photo/photo/test.bmp is not exists. Continue?", QMessageBox::Yes, QMessageBox::No);
	//	if (bn == QMessageBox::Yes) {
	//		globalVar.isOfflineTest = false;
	//		ui->checkBox_OfflineTest->setChecked(globalVar.isOfflineTest);
	//	}
	//	if (bn == QMessageBox::No) {
	//		this->close();
	//	}
	//}
	//本地测试，使用测试用图；
	if (globalVar.isOfflineTest)
		ui->pictureBox_CameraShow->setPixmap(pixmap3);
	//未连接相机，使用《请连接相机》图
	else if(!globalVar.isConnectCameraSuccess)
		ui->pictureBox_CameraShow->setPixmap(pixmap1);
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
    //ui->lineEdit_brightness->setText(QString::number(position));
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
	//有回传图像证明相机连接成功。
	if(!globalVar.isConnectCameraSuccess)globalVar.isConnectCameraSuccess = true;
	picBox_Show->setData(imgData, width, height);

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
	getAllConfigValueToGlobal();
	globalVar.init();
	this->init();
}
void MainWindow::on_pushButton_Cancel_clicked()
{
	setAllConfigValue();

}
void setColor(QColor &color, int r, int g, int b) {
	color.setRed(r); color.setGreen(g); color.setBlue(b);
}
void MainWindow::on_colorRdoGroup_check(int id, bool isChecked)
{
	uchar value = ui->spinBox_GL->value();
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

void MainWindow::on_SpinBox_changed_textChanged(int value)
{
	int id = colorRdoGroup->checkedId();

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
		if (ui->pushButton_SwitchKandB->text() == "切换到k") {
			ui->pushButton_SwitchKandB->setText("切换到b");
			ui->label_CurFac->setText("系数-k");
			globalVar.fackind = K;
			globalVar.facrgb = FacRGB(globalVar.facrgb - 1);
		}
		else {
			ui->pushButton_SwitchKandB->setText("切换到k");
			ui->label_CurFac->setText("系数-b");
			globalVar.fackind = B;
			globalVar.facrgb = FacRGB(globalVar.facrgb + 1);

		}
		break;
	case 1:
		if (globalVar.fackind == K)
			globalVar.facrgb = FACRK;
		else
			globalVar.facrgb = FACRB;
		this->myModel->setBgColor(QColor(255, 0, 0));
		break;
	case 2:
		if (globalVar.fackind == K)
			globalVar.facrgb = FACGK;
		else
			globalVar.facrgb = FACGB;
		this->myModel->setBgColor(QColor(0, 255, 0));
		break;
	case 3:
		if (globalVar.fackind == K)
			globalVar.facrgb = FACBK;
		else
			globalVar.facrgb = FACBB;

		this->myModel->setBgColor(QColor(0, 0, 255));
		break;
	}
	this->myModel->setFacData(globalVar.ScreenWidth, globalVar.ScreenHeight, globalVar.getFacData(globalVar.facrgb));

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
	ui->statusBar->showMessage("Snaping", 1500);
	QPixmap *pmp = ui->pictureBox_CameraShow->getPixmap();
	//1. 给PictureBox赋值图片。
	ui->pictureBox_Capture->setPixmap(pmp);
	ui->pictureBox_Capture->update();
	QDir dir("photo");
	if (!dir.exists())dir.mkpath("photo");
	//2. 保存图片到本地。
	pmp->save("photo/"+globalVar.getCurBmpName());
	//3. 图片的标识（R1-B2)移动到下一个。
	globalVar.movePhotoRGBToNext();
	//4. 界面的状态显示photorgb。
	setPhotoStatus();
	//5. 有6张图才可以点击开始分析。
	if (QFile("photo/R1.bmp").exists() && QFile("photo/R2.bmp").exists() && QFile("photo/G1.bmp").exists() && QFile("photo/G2.bmp").exists() && QFile("photo/B1.bmp").exists() && QFile("photo/B2.bmp").exists()) {
		ui->pushButton_Analysis->setEnabled(true);
	}
	else ui->pushButton_Analysis->setEnabled(false);
}

void MainWindow::on_pushButton_analysis_Clicked()
{
	//QPixmap *pix = pbx2->getPixmap();
	if (!(QFile("photo/R1.bmp").exists() && QFile("photo/R2.bmp").exists() && QFile("photo/G1.bmp").exists() && QFile("photo/G2.bmp").exists() && QFile("photo/B1.bmp").exists() && QFile("photo/B2.bmp").exists())) {
		QMessageBox::information(this, "错误", "文件缺失", QMessageBox::Ok);
		return;
	}
	QString fnames[] = { "photo/R1.bmp","photo/R2.bmp","photo/G1.bmp","photo/G2.bmp","photo/B1.bmp","photo/B2.bmp" };
	float* facsArray[] = { globalVar.arrayRK,globalVar.arrayRB,globalVar.arrayGK,globalVar.arrayGB,globalVar.arrayBK,globalVar.arrayBB };
	MarkPoints markpoints;
	Mat temp = imread("photo/R1.bmp");
	markpoints.x1 = temp.cols*globalVar.markPointFacxLU;
	markpoints.y1 = temp.rows*globalVar.markPointFacyLU;
	markpoints.x2 = temp.cols*globalVar.markPointFacxRU;
	markpoints.y2 = temp.rows*globalVar.markPointFacyRU;
	markpoints.x3 = temp.cols*globalVar.markPointFacxLD;
	markpoints.y3 = temp.rows*globalVar.markPointFacyLD;
	markpoints.x4 = temp.cols*globalVar.markPointFacxRD;
	markpoints.y4 = temp.rows*globalVar.markPointFacyRD;
	temp.release();
	//一次完整的流程设置一个时间mark。
	globalVar.photoFileManager.setDateTime(QDateTime::currentDateTime());
	imgAlm->setCoreResolution(globalVar.ScreenWidth, globalVar.ScreenHeight);
	imgAlm-> CalcFacsFromSixPic(fnames, markpoints,globalVar.firstGL,globalVar.secondGL, facsArray);

	QPoint pos(ui->pushButton_CalibrationResult->width() / 2,  ui->pushButton_CalibrationResult->height() / 2);
	QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::sendEvent(ui->pushButton_CalibrationResult, &event0);
	QMouseEvent event1(QEvent::MouseButtonRelease, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::sendEvent(ui->pushButton_CalibrationResult, &event1);

	//if (globalVar.snapData == nullptr)return;
	//int* lightData = getLightSum(pix->width(), pix->height(), globalVar.snapData, markpoints);
	//int target;
	//ImageAlgorithm::GL_compensation(lightData, COLS, ROWS, 100, 2.8, globalVar.arrayW, target);
}


void MainWindow::on_pushButton_Scan_clicked()
{
	QString path=QFileDialog::getExistingDirectory(this,"选择工作目录",globalVar.WorkPath);
	ui->lineEdit_WorkPath->setText(path);
}

void MainWindow::on_checkRadioButtonGroup_Clicked(int id)
{
	QString fname=globalVar.photoFileManager.getPhotoFileName((PhotoRGB)checkColorRadioButtonGroup->checkedId(), (PhotoFileManager::PhotoFileType)checkOptionRadioButtonGroup->checkedId());
	if (QFile(fname).exists()) {

		if (checkOptionRadioButtonGroup->checkedId() == 0) {
			qDebug() << "读取bmp失败" << endl;
			Mat m = imread(fname.toStdString());
			QImage *img = new QImage(m.data, m.cols, m.rows, QImage::Format_RGB888);
			pixmap3 = new QPixmap(QPixmap::fromImage(*img));
			ui->pictureBox_ResultShow->setPixmap(pixmap3);
			ui->pictureBox_ResultShow->update();
			delete img;
			m.release();

		}
		if (checkOptionRadioButtonGroup->checkedId() == 1) {

			pixmap3 = new QPixmap(fname);
			ui->pictureBox_ResultShow->setPixmap(pixmap3);
			ui->pictureBox_ResultShow->update();
		}

	}
}

void MainWindow::on_MenuBar_toggled(QAction * action)
{
	QString actionText = action->text();
	if (actionText == "色度校正") {
		colorCali->show();
	}
}


void MainWindow::del()
{
}
