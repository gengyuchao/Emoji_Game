#ifndef SETING_WINDOWS_H
#define SETING_WINDOWS_H

#include <QDialog>


namespace Ui {
class Seting_Windows;
}

class Seting_Windows : public QDialog
{
    Q_OBJECT

public:
    explicit Seting_Windows(QWidget *parent = 0);

    ~Seting_Windows();

    int Max_Emoji;
    int Max_Size;
    int Max_Speed;
    int Min_Speed;
    int Frame_Rate;
    int Frame_Time;
    int My_Score;

    void Set_Score(int score);

private slots:
    void on_Btn_Set_Confirm_clicked();

private:
    Ui::Seting_Windows *ui;

signals:
    void Click_Confirm();
};

#endif // SETING_WINDOWS_H
