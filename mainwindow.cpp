#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QMouseEvent"
#include "QMessageBox"

#include "QFont"

#include "windows.h"



QPoint GLOBAL_Point;
int GLOBAL_Frame_Rate=60;

#define min(x,y) ((x)<(y)?(x):(y))

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //                   无窗体                 窗口位于最顶端
    setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);
    //setAttribute(Qt::WA_TranslucentBackground,true); //透明化
    setAutoFillBackground(true);

    ui->setupUi(this);

    setStyleSheet("#MainWindow { background-image: url(:/Background/praedestinatio.jpg);}");

    ui->mainToolBar->setWindowFlag(Qt::WindowStaysOnTopHint,true);

    ui->widget->hide();

    Seting_Dialog=new Seting_Windows(this);

    Max_Emoji=Seting_Dialog->Max_Emoji;
    Max_Speed=Seting_Dialog->Max_Speed;
    Min_Speed=Seting_Dialog->Min_Speed;
    Max_Size=Seting_Dialog->Max_Size;
    Frame_Time=Seting_Dialog->Frame_Time;

    settings = new QSettings("MyScore",QSettings::IniFormat);
    History_Num = settings->value("YOU_LOVE").toInt();
    Seting_Dialog->Set_Score(History_Num);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Timerupdate()));
    connect(Seting_Dialog, SIGNAL(Click_Confirm()), this, SLOT(Update_Settings()));
    timer->start(Frame_Time);

    setWindowState(Qt::WindowMaximized);

    QImage image_Huaji(":/icon/huaji.png");

    image_Huaji = image_Huaji.mirrored(true, false);
    pixmap = QPixmap::fromImage(image_Huaji);
    image_Huaji = image_Huaji.mirrored(true, false);
    pixmap_mirror = QPixmap::fromImage(image_Huaji);

    setAttribute( Qt::WA_Hover,true);
    setMouseTracking(true);

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    GLOBAL_Point=e->pos();
}
void MainWindow::Update_Settings()
{
    Max_Emoji=Seting_Dialog->Max_Emoji;
    Min_Speed=Seting_Dialog->Min_Speed;
    Frame_Time=Seting_Dialog->Frame_Time;
    Max_Size=Seting_Dialog->Max_Size;
    timer->start(Frame_Time);
    GLOBAL_Frame_Rate=Seting_Dialog->Frame_Rate;

}

void MainWindow::Timerupdate()
{

    if(Face!=NULL)
    {
        Face->setGeometry(GLOBAL_Point.x()-60,GLOBAL_Point.y()-60,120,120);
    }

    if(emoji_vector.empty())
    {
        if(Max_Emoji==-1)//如果是分裂禁止时候（游戏中） 滑稽剩余数量为0 则重置最大允许值
        {
            Max_Emoji=Seting_Dialog->Max_Emoji;

            ui->widget->show();
            History_Num=History_Num+Max_Emoji;
            settings->setValue("YOU_LOVE",History_Num);
            if(History_Num>90)
            {
                ui->Congratulation->setMinimumSize(666,500);
                ui->Congratulation->setPixmap(QPixmap(":/icon/Love.png"));
                Delay_Ms(4000);
            }
            Seting_Dialog->Set_Score(History_Num);
            if(Face!=NULL) Face->hide();
            ui->actionNew_Achieve->setEnabled(false);
            Delay_Ms(2000);
            ui->widget->hide();
        }
        return;
    }


    for(unsigned int i=0;i<emoji_vector.size();i++)
    {
        emoji_vector[i].update();

        if(emoji_vector[i].Flag_Delete==1)
        {
            emoji_vector[i].Picture->deleteLater();
            emoji_vector.erase(emoji_vector.begin()+i);
            if(i<emoji_vector.size())
                break;
        }

//        emoji_vector[i].Picture->setGeometry(emoji_vector[i].pos_x,emoji_vector[i].pos_y,100,100);

        if(emoji_vector[i].Flag_Create_new==1)
        {
            if(emoji_vector[i].Flag_dirx==1)
            {
                emoji_vector[i].Picture->setPixmap(pixmap);
            }
            else
            {
                emoji_vector[i].Picture->setPixmap(pixmap_mirror);
            }
        }

        if(emoji_vector[i].Flag_Create_new==1)
        {
            if( (int)emoji_vector.size() < Max_Emoji )
            {
                Huaji_emoji *newemoji= new Huaji_emoji(this);
                newemoji->Picture=new QLabel(this);
                newemoji->Max_Size=(100+((Max_Size-100)>0?(rand()%(Max_Size-100)):0));
                newemoji->Flag_dirx=emoji_vector[i].Flag_dirx;
                newemoji->set_start_pos(emoji_vector[i].pos_x+(newemoji->Max_Size/2+2)*emoji_vector[i].Flag_dirx,emoji_vector[i].pos_y);
                newemoji->Picture->setScaledContents(true);
                newemoji->Picture->setMouseTracking(true);
                newemoji->Picture->setPixmap(pixmap_mirror);
                newemoji->Picture->show();
                if(emoji_vector[i].new_Seed==newemoji->new_Seed)
                    newemoji->new_Seed++;

                emoji_vector.push_back(*newemoji);
                if(emoji_vector[i].new_Seed>3)
                    emoji_vector[i].new_Seed--;
            }
            else
            {
                Max_Emoji=-1;//分裂禁止
                if(emoji_vector[i].new_Seed>Min_Speed)
                    emoji_vector[i].new_Seed--;
            }
        }

    }

    for(unsigned int i=0;i<emoji_vector.size();i++)
    {
        emoji_vector[i].Picture->setGeometry(emoji_vector[i].pos_x,emoji_vector[i].pos_y,emoji_vector[i].Max_Size,emoji_vector[i].Max_Size);
    }



}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Delay_Ms(int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

}



void MainWindow::Set_Max_Emoji(int Max_num)
{
    Max_Emoji=Max_num;
}

void MainWindow::Set_Max_Speed(int Max_num)
{
    Max_Speed=Max_num;
}
void MainWindow::Set_Min_Speed(int Min_num)
{
    Min_Speed=Min_num;
}
void MainWindow::Set_Frame_Time(int Rate)
{
    Frame_Time=Rate;
}


void MainWindow::on_actionStart_triggered()
{
    Huaji_emoji *newemoji= new Huaji_emoji(this);
    newemoji->Picture=new QLabel(this);
    newemoji->set_start_pos(this->width()/2,this->height()/2);
    newemoji->Picture->setMouseTracking(true);
    newemoji->Picture->setScaledContents(true);
    newemoji->Picture->setPixmap(pixmap);
    newemoji->set_seed(3);
    newemoji->Picture->show();
    emoji_vector.push_back(*newemoji);
    ui->actionNew_Achieve->setEnabled(true);
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}

void MainWindow::on_actionClear_triggered()
{
    if(emoji_vector.empty())
        return;
    for(unsigned int i=0;i<emoji_vector.size();i++)
    {
        emoji_vector[i].Picture->deleteLater();

    }
    emoji_vector.clear();
}




void MainWindow::on_actionSet_triggered()
{

    if(Seting_Dialog==NULL)
    {
        QMessageBox::warning(this,"警告","Seting_Dialog创建失败，请检查内存是否充足。\n该问题一般情况下不会出现，\n可以尝试重新点击此按钮或者重启程序\n如果问题反复出现请联系管理员！");
        Seting_Dialog=new Seting_Windows(this);
    }
    else
    {
        Seting_Dialog->show();
    }

}


void MainWindow::on_actionWindowsSet_triggered()
{
    if(ui->mainToolBar->iconSize().width()<36)
        ui->mainToolBar->setIconSize(QSize(36,36));
    else if(ui->mainToolBar->iconSize().width()<48)
        ui->mainToolBar->setIconSize(QSize(48,48));
    else
        ui->mainToolBar->setIconSize(QSize(24,24));
}

void MainWindow::on_actionNew_Achieve_triggered()
{
    if(Face==NULL)
    {
        QImage image_Face(":/icon/poe_face_arf-icon.png");
        QPixmap pixmap_Face = QPixmap::fromImage(image_Face);
        Face=new QLabel(this);
        Face->setPixmap(pixmap_Face);
    }

    Face->setMouseTracking(true);
    Face->setScaledContents(true);

    Face->setAttribute(Qt::WA_TranslucentBackground,true);
    Face->show();

}



void MainWindow::on_actionSkin_triggered()
{
    static int File_Numbe=0;
    QString File_Name;
    switch (File_Numbe)
    {
        case 0: File_Name="1_aura"; break;
        case 1: File_Name="praedestinatio"; break;
        case 2: File_Name="denebola"; break;
        case 3: File_Name="earth2584-ii"; break;
        case 4: File_Name="eclipse"; break;
        case 5: File_Name="ordinary-morning"; break;
        case 6: File_Name="sojourn"; break;

        default: File_Name="1_aura"; break;


    }
    File_Numbe++;
    if(File_Numbe>6)
        File_Numbe=0;


    setStyleSheet("#MainWindow { background-image: url(:/Background/"+File_Name+");}");

}
