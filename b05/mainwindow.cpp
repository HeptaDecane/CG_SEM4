#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
#include "iostream"
using namespace std;

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

/***********Global Variables**********/
QRgb black=qRgb(0,0,0);
QRgb red=qRgb(255,0,0);
QRgb green=qRgb(0,255,0);
QRgb blue=qRgb(0,0,255);
QRgb white=qRgb(255,255,255);

QImage image(941,691,QImage::Format_RGB888);

int startX=0.75*670+135;
int startY=0.75*670+10;

/************************************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image.fill(white);
    current=new QPoint(startX,startY);
    level=1;
    strokeSize=ceil(670/pow(2,level));
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::drawGrid()
{
    int step=ceil(670/pow(2,level));
    int side=step*pow(2,level);

    for(int i=0;i<=side;i+=step){
        for(int j=0;j<=side;j+=4){
         image.setPixel(135+j,i+10,black);
         image.setPixel(135+i,j+10,black);
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();

    /*
        (135,10)                (805,10)
            *-----------------------*
            |                       |
            |                       |
            |                       |
            |                       |
            |                       |
            *-----------------------*
        (135,690)               (805,690)
     */
}

void MainWindow::drawStroke(int direction)
{
    int x=current->x();
    int y=current->y();
    cout<<x<<" "<<y<<"\n";
    switch (direction) {
    case UP:
        for(int i=0;i<strokeSize;i++)
            image.setPixel(x,y--,red);
        break;
    case LEFT:
        for(int i=0;i<strokeSize;i++)
            image.setPixel(x--,y,red);
        break;
    case DOWN:
        for(int i=0;i<strokeSize;i++)
            image.setPixel(x,y++,red);
        break;
    case RIGHT:
        for(int i=0;i<strokeSize;i++)
            image.setPixel(x++,y,red);
        break;
    default:
        break;
    }
    current=new QPoint(x,y);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
    level=arg1.toInt();
    strokeSize=ceil(670/pow(2,level));
//    cout<<level<<"\n";
}

void MainWindow::on_radioButton_clicked()
{
    direction=UP;
//    cout<<direction<<"\n";
}

void MainWindow::on_radioButton_2_clicked()
{
    direction=LEFT;
//    cout<<direction<<"\n";
}

void MainWindow::on_radioButton_3_clicked()
{
    direction=DOWN;
//    cout<<direction<<"\n";
}

void MainWindow::on_radioButton_4_clicked()
{
    direction=RIGHT;
//    cout<<direction<<"\n";
}

void MainWindow::on_pushButton_clicked()
{
    drawGrid();
    drawStroke(UP);
    drawStroke(LEFT);
    drawStroke(DOWN);
}

void MainWindow::on_pushButton_2_clicked()
{

}
