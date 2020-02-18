#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "iostream"
using namespace std;

/**************Global Variables**************/
QImage image(701,441,QImage::Format_RGB888);
QRgb white=qRgb(255,255,255);
QRgb black=qRgb(0,0,0);
int xMin,xMax,yMin,yMax,n=0;
bool box=false,line=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *events)
{
    if(box==true){
        if(events->button()==Qt::LeftButton){
            xMax=events->pos().x();
            yMax=events->pos().y();
        }
    }
    if(line==true){
        if(events->button()==Qt::LeftButton){
            coordinates[n][0]=events->pos().x();
            coordinates[n][1]=events->pos().y();
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *events)
{
    if(box==true){
        if(events->button()==Qt::LeftButton){
            xMin=events->pos().x();
            yMin=events->pos().y();
            drawBox();
        }
    }
    if(line==true){
        if(events->button()==Qt::LeftButton){
            coordinates[n][2]=events->pos().x();
            coordinates[n][3]=events->pos().y();
            ddaLine(coordinates[n][0],coordinates[n][1],coordinates[n][2],coordinates[n][3]);
            n++;
        }
    }
}

void MainWindow::drawBox()
{
    ddaLine(xMin,yMin,xMax,yMin);
    ddaLine(xMin,yMin,xMin,yMax);
    ddaLine(xMax,yMin,xMax,yMax);
    ddaLine(xMin,yMax,xMax,yMax);

    int x1=xMin;
    int y1=yMin;
    int x2=xMax;
    int y2=yMax;

    xMin=min(x1,x2);
    xMax=max(x1,x2);

    yMin=min(y1,y2);
    yMax=max(y1,y2);


    cout<<"\n"<<xMin<<","<<yMin;
    cout<<"\n"<<xMax<<","<<yMax;

    box=false;
}

void MainWindow::ddaLine(int x1, int y1, int x2, int y2)
{
    float dx,dy,steps,xinc,yinc;
    dx=x2-x1;
    dy=y2-y1;

    steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    xinc=dx/steps;
    yinc=dy/steps;

    float x=x1;
    float y=y1;

    for(int i=0;i<=steps;i++){
        image.setPixel(x,y,white);
        x=x+xinc;
        y=y+yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_pushButton_clicked()    //Box
{
    box=true;
    line=false;
}

void MainWindow::on_pushButton_2_clicked()      //Line
{
    line=true;
    box=false;
}

void MainWindow::on_pushButton_3_clicked()      //Clip
{
    //Business Logic!
}

void MainWindow::on_pushButton_4_clicked()      //Clear
{
    image.fill(black);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
    n=0;
}
