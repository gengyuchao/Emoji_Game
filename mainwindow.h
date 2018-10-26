#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTime"
#include "huaji_emoji.h"
#include "QTimer"
#include <vector>
#include "seting_windows.h"
#include "QSettings"

namespace Ui {
class MainWindow;
}

class MainWindow :  /*public QThread ,*/ public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Delay_Ms(int xms);
    std::vector<Huaji_emoji> emoji_vector;
    QPixmap pixmap;
    QPixmap pixmap_mirror;
    QTimer *timer;
    void Set_Max_Emoji(int Max_num);
    void Set_Max_Speed(int Max_num);
    void Set_Min_Speed(int Min_num);
    void Set_Frame_Time(int Rate);
    void Load_Picture();




private slots:

    void Timerupdate();

    void on_actionStart_triggered();

    void on_actionClose_triggered();

    void on_actionClear_triggered();

    void on_actionSet_triggered();

    //void on_Btn_Set_Confirm_clicked();

    void on_actionWindowsSet_triggered();

    void Update_Settings();

    void on_actionNew_Achieve_triggered();

    void on_actionSkin_triggered();

private:
    Ui::MainWindow *ui;

    Seting_Windows *Seting_Dialog;

    int Max_Emoji=5;
    int Max_Speed=10;
    int Min_Speed=2;
    int Max_Size=100;
    int Frame_Time=1000/60;

    QSettings *settings;
    int History_Num=0;

    QLabel *Face=NULL;



protected:
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H

