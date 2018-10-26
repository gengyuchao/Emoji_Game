#include "seting_windows.h"
#include "ui_seting_windows.h"
#include "QMessageBox"
Seting_Windows::Seting_Windows(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Seting_Windows)
{
//    my_parent=parent;
    ui->setupUi(this);

    Max_Emoji=(ui->lineEdit_Max_Num->text().toInt());
    Max_Speed=(ui->lineEdit_Max_Speed->text().toInt());
    Min_Speed=(ui->lineEdit_Min_Speed->text().toInt());
    Max_Size=(ui->lineEdit_Max_Size->text().toInt());
    Frame_Rate=60;
    Frame_Time=(1000/Frame_Rate);
    My_Score=0;
    emit Click_Confirm();
}

Seting_Windows::~Seting_Windows()
{

    delete ui;
}

void Seting_Windows::Set_Score(int score)
{
    My_Score=score;
    if(My_Score<100)
        ui->LOVE_progress->setValue(My_Score);
    else
        ui->LOVE_progress->setValue(100);
}

void Seting_Windows::on_Btn_Set_Confirm_clicked()
{
    Max_Emoji=(ui->lineEdit_Max_Num->text().toInt());
    Min_Speed=(ui->lineEdit_Min_Speed->text().toInt());
    Frame_Rate=ui->Frame_Ratr_Slider->value();
    Max_Size=(ui->lineEdit_Max_Size->text().toInt());
    Frame_Time=(1000/Frame_Rate);
    this->hide();
    emit Click_Confirm();
}
