#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixitem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QVBoxLayout>
#include "camera.h"
#include "client.h"
#include <QButtonGroup>
#include "mytablemodel.h"
#include "globalvar.h"
#include "array2d.h"
#include <QItemSelectionModel>

void mCameraCallback(byte* imgData,int width,int height);
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_OutlineGap_clicked(bool checked);

    void on_pushButton_ParameterSet_clicked();


    void on_pushButton_CameraCalibration_clicked();

    void on_pushButton_PickPicture_clicked();

    void on_pushButton_CalibrationResult_clicked();

	void on_pushButton_PointsCalibration_clicked();

    void on_comboBox_SelectConnectWay_currentIndexChanged(int index);

    void on_horizontalSlider_ExposureTime_sliderMoved(int position);

    void on_lineEdit_Aperture_editingFinished();

    void loadStyleSheet(const QString &styleSheetFile);

    void on_dial_brightness_sliderMoved(int position);

    void on_pushButton_ConnectCamera_clicked();

    void on_lineEdit_ExposureTime_returnPressed();

	void on_pushButton_Confirm_clicked();

	void on_colorRdoGroup_check(int, bool);

	void on_lineEdit_brightness_textChanged(QString);

	void on_colorBtnGroup_checked(int);

	void on_pushButton_Plus_clicked();

	void on_pushButton_Sub_clicked();

	void on_tableView_CurrentChanged(const QModelIndex&, const QModelIndex&);

	void on_LineEdit_CurValue_Edited();
	
	void on_addSubBtnGroup_Clicked(int);

	void on_pushButton_snap_Clicked();

	void on_pushButton_analysis_Clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *m_graphicsScene1;
    QGraphicsScene *m_graphicsScene;
    QGraphicsView *m_graphicsView;
    QGraphicsView *m_graphicsView1;

    int m_timerID;
    int m_flag;

	Client *client;
	QButtonGroup *colorRdoGroup;
	QColor *sndColor;

	QButtonGroup *colorBtnGroup;
	
	MyTableModel *myModel;
	QItemSelectionModel *selectModle;

	QButtonGroup *addSubBtnGroup;
};

#endif // MAINWINDOW_H
