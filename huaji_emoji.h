#ifndef HUAJI_EMOJI_H
#define HUAJI_EMOJI_H
//#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include "QLabel"
#include "QImage"
#include "QPixmap"


class Huaji_emoji
{
public:
    Huaji_emoji(QWidget *parent);
    QWidget *father;//父窗体
    int pos_x,pos_y;
    int Flag_diry,Flag_dirx,Flag_Create_new,Flag_Delete;
    int new_Seed;
    QLabel *Picture;


    void set_start_pos(int pos_x_init,int pos_y_init);
    void set_seed(int seed);
    void update();
    int my_Rand(int Seed=1);
    int my_Rand_y(int Seed);
    int Max_Size;
private:
    int Delete_count=15;
    int Flag_in=0;

};

#endif // HUAJI_EMOJI_H
