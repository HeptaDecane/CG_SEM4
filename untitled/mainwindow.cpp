#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
using namespace std;
/*Global Variables*/
int x1,y1;
int x2,y2;
QImage image(571,381,QImage::Format_RGB888);
QRgb green=qRgb(0,255,0);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_textEdit_textChanged()
{
    QString str=ui->textEdit->toPlainText();
    x1=str.toInt();
}

void MainWindow::on_textEdit_2_textChanged()
{
    QString str=ui->textEdit_2->toPlainText();
    y1=str.toInt();
}

void MainWindow::on_textEdit_3_textChanged()
{
    QString str=ui->textEdit_3->toPlainText();
    x2=str.toInt();
}

void MainWindow::on_textEdit_4_textChanged()
{
    QString str=ui->textEdit_4->toPlainText();
    y2=str.toInt();
}

void MainWindow::on_pushButton_clicked()
{
    //Thick Line
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    float dx,dy,steps,xinc,yinc;
    dx=x2-x1;
    dy=y2-y1;

    steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    xinc=dx/steps;
    yinc=dy/steps;

    float x=x1;
    float y=y1;

    for(int i=0;i<=steps/3;i++){
        image.setPixel(x,y,green);
        x=x+3*xinc;
        y=y+3*yinc;
    }
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_4_clicked()
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
        if(i%5)
            image.setPixel(x,y,green);
        x=x+xinc;
        y=y+yinc;
    }
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow::on_pushButton_3_clicked()
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
         if(i%10<5)
            image.setPixel(x,y,green);
         if(i%10==7)
             image.setPixel(x,y,green);
         x=x+xinc;
         y=y+yinc;
     }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}
