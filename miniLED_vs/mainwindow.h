#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pixitem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QVBoxLayout>
#include "camera.h"

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


    void on_comboBox_SelectConnectWay_currentIndexChanged(int index);

    void on_horizontalSlider_ExposureTime_sliderMoved(int position);

    void on_lineEdit_Aperture_editingFinished();
    void loadStyleSheet(const QString &styleSheetFile);

    void on_dial_brightness_sliderMoved(int position);

    void on_pushButton_ConnectCamera_clicked();

    void on_lineEdit_ExposureTime_returnPressed();

	void on_pushButton_Confirm_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *m_graphicsScene1;
    QGraphicsScene *m_graphicsScene;
    QGraphicsView *m_graphicsView;
    QGraphicsView *m_graphicsView1;

    int m_timerID;
    int m_flag;
};

#endif // MAINWINDOW_H
