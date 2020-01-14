#include "mainwindow.h"
#include "ui_mainwindow.h"
int radius;
int xc=260,yc=190;
QImage image(521,381,QImage::Format_RGB888);
QRgb green=qRgb(0,255,0);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::bresenhamCircle(){
    int x=0,y=radius;
    int d=3-2*radius;
    drawCircle(x,y);
    while(y>=x){
        x++;
        if(d>0){
            y--;
            d=d+4*(x-y)+10;
        }
        else
            d=d+4*x+6;
       drawCircle(x,y);
    }
}
void MainWindow::drawCircle(int x,int y){
    image.setPixel(xc+x,yc+y,green);
    image.setPixel(xc-x,yc+y,green);
    image.setPixel(xc+x,yc-y,green);
    image.setPixel(xc-x,yc-y,green);
    image.setPixel(xc+y,yc+x,green);
    image.setPixel(xc-y,yc+x,green);
    image.setPixel(xc+y,yc-x,green);
    image.setPixel(xc-y,yc-x,green);
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_textChanged()
{
    QString str=ui->textEdit->toPlainText();
    radius=str.toInt();
}

void MainWindow::on_pushButton_clicked()
{
    bresenhamCircle();
}
