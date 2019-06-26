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

PixItem *m_pixItem;
PixItem *m_pixItem1;
    Camera* camera;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->loadStyleSheet(":/miniLED_vs/myStyleSheet.qss");
    //QLayout* layout_Pic=new QLayout(widget3);
    ui->lineEdit_ExposureTime->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->lineEdit_Aperture->setValidator(new QRegExpValidator(QRegExp("[0-9]+\.+[0-9]+$")));

    ui->statusBar->showMessage("就绪",3000);



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

	/*
    QGraphicsScene *m_graphicsScene1=new QGraphicsScene;
    m_graphicsScene1->setSceneRect(0, 0, ui->verticalLayout_11->geometry().x(), ui->verticalLayout_11->geometry().y());
    QPixmap *pixmap1=new QPixmap(":/miniLED_vs/CachedImage_1920_1080_POS3.jpg");
    m_pixItem1=new PixItem(pixmap1);
    m_graphicsScene1->addItem(m_pixItem1);
    m_pixItem1->setPos(0,0);
    m_graphicsView1=new QGraphicsView();
    m_graphicsView1->setScene(m_graphicsScene1);
    m_graphicsView1->setMinimumSize(ui->verticalLayout_11->geometry().x(), ui->verticalLayout_11->geometry().y());
    ui->verticalLayout_12->addWidget(m_graphicsView1);
	*/

    camera=new Camera();
    //connect(camera,SIGNAL(cameraImgReady(QPixmap*)),this->m_pixItem,SLOT(on_CameraReceived(QPixmap*)));
	camera->QSetCallback(mCameraCallback);

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
		camera->QOpen();
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

    QImage mImage(imgData,width,height,QImage::Format_RGB888);
    QPixmap mPixmap=QPixmap::fromImage(mImage);
    m_pixItem->setPixmap(&mPixmap);
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
