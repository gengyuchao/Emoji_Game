#include "huaji_emoji.h"

#include "windows.h"
#include "QMouseEvent"
extern QPoint GLOBAL_Point;
extern int GLOBAL_Frame_Rate;
Huaji_emoji::Huaji_emoji(QWidget *parent)
{
    //父窗体
    father = parent;
    //设置起点
    pos_x=father->width()/2;
    pos_y=father->height()/2;
    new_Seed=rand()%5;
    new_Seed=new_Seed/3+new_Seed/4+1;

    Flag_diry=1;
    Flag_dirx=1;
    Flag_Create_new=0;
    Flag_Delete=0;
    Max_Size=100;

}

int Huaji_emoji::my_Rand(int Seed)
{

    static int x=2;
    int temp1=Seed*x*x+x;
    x++;
    int temp2=Seed*x*x+x;
    if(temp2>4000)
        x=0;
    return temp2-temp1;

}
int Huaji_emoji::my_Rand_y(int Seed)
{
    static int x=10;
    int temp1=Seed*x*x+x;
    x++;
    int temp2=Seed*x*x+x;
    if(temp2>40000)
        x=0;

    return temp2-temp1;

}
void Huaji_emoji::set_start_pos(int pos_x_init,int pos_y_init)
{
    pos_x=pos_x_init;
    pos_y=pos_y_init;
}
void Huaji_emoji::set_seed(int seed)
{

    new_Seed=seed;

}
void Huaji_emoji::update()
{
    QPoint p;//定义一个POINT变量，用于存储鼠标的坐标
//    POINT p1;
//    GetCursorPos(&p1);//获取鼠标位置
//    p.setX(p1.x);
//    p.setY(p1.y);
    p=GLOBAL_Point;

    int Half_Size=Max_Size/2;


    //static int Flag_in=0;
    if((pos_x+Half_Size-p.x())*(pos_x+Half_Size-p.x())+(pos_y+Half_Size-p.y())*(pos_y+Half_Size-p.y())<=((Half_Size+50)*(Half_Size+50)))
    {
//        if(Flag_in==0&&(pos_x+Half_Size-p.x())*(pos_x+Half_Size-p.x())+(pos_y+Half_Size-p.y())*(pos_y+Half_Size-p.y())>=((Half_Size+2*new_Seed)*(Half_Size+2*new_Seed)))
//        {
            Flag_dirx=-Flag_dirx;
            Flag_diry=-Flag_diry;

//        }

//        Flag_in=1;

        if(abs(pos_x+Half_Size-p.x())<Half_Size+10)
        {
            new_Seed=new_Seed<4?(new_Seed+1):new_Seed;
        }
        if(abs(pos_y+Half_Size-p.y())<Half_Size+10)
        {
            new_Seed=new_Seed<4?(new_Seed+1):new_Seed;
        }

        pos_x+=Flag_dirx*new_Seed*6;
        pos_y+=Flag_diry*new_Seed*6;

        if((pos_x+Half_Size-p.x())*(pos_x+Half_Size-p.x())+(pos_y+Half_Size-p.y())*(pos_y+Half_Size-p.y())<(Half_Size*Half_Size/2))
        {
            if(Delete_count<=0)
            {
                Flag_Delete=1;
            }
            else
            {
                Delete_count--;
            }
        }
//        int temp_x= pos_x+Flag_dirx*(new_Seed*144/(float)GLOBAL_Frame_Rate+(my_Rand(1)%(new_Seed+1)/3));
//        int temp_y= pos_y+Flag_diry*(new_Seed*144/(float)GLOBAL_Frame_Rate+(my_Rand_y(2)%(new_Seed+1)/3));
//        if((temp_x+Half_Size-p.x())*(temp_x+Half_Size-p.x())+(temp_y+Half_Size-p.y())*(temp_y+Half_Size-p.y())<=((Half_Size+50)*(Half_Size+50)))//如果还没跑出圈 则改变方向以便下一次方向正确
//        {
//            Flag_dirx=-Flag_dirx;
//            Flag_diry=-Flag_diry;
//        }

    }
//    else
//    {
//        Flag_in=0;
//    }



    pos_x+=Flag_dirx*(new_Seed*144/(float)GLOBAL_Frame_Rate+(my_Rand(1)%(new_Seed+1)/3));
    pos_y+=Flag_diry*(new_Seed*144/(float)GLOBAL_Frame_Rate+(my_Rand_y(2)%(new_Seed+1)/3));
    Flag_Create_new=0;//重置新创建允许标志位


    if(pos_y<0||pos_y>father->height()-Max_Size-40)
    {

        Flag_diry=-Flag_diry;
    }
    if(pos_x<0||pos_x>father->width()-Max_Size)
    {

        Flag_dirx=-Flag_dirx;
        Flag_Create_new=1;
    }



    if(pos_y>father->height()-Max_Size-40)
        pos_y=father->height()-Max_Size-40-1;
    if(pos_y<0)
        pos_y=1;

    if(pos_x>father->width()-Max_Size)
        pos_x=father->width()-Max_Size-1;
    if(pos_x<0)
        pos_x=1;


}
