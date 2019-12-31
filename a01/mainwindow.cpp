#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
int length,breadth;
QImage image(531,381,QImage::Format_RGB888);
QRgb value = qRgb(0,255,0);
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
    length=str.toInt();
}

void MainWindow::on_textEdit_2_textChanged()
{
    QString str=ui->textEdit->toPlainText();
    breadth=str.toInt();
}
void MainWindow::bresenham(int x1,int y1,int x2,int y2){
    int dx,dy,p;
    dx = x2-x1 ;
    dy = y2 - y1 ;
    if(abs(dx)>abs(dy))
        {
            p=2*dy-dx;
            while(x1<=x2)
            {
                 image.setPixel(x1,y1,value);
                x1++;
                if(p<0)
                {
                    p=p+2*dy;
                }
                else
                {
                    p=p+2*dy-2*dx;
                    y1++;
                }
            }
        }
        else if(abs(dx)<abs(dy))
        {
            p=2*dx-dy;
            while(y1<=y2)
            {
                 image.setPixel(x1,y1,value);
                y1++;
                if(p<0)
                {
                    p=p+2*dx;
                }
                else
                {
                    p=p+2*dx-2*dy;
                    x1++;
                }
            }
        }
        else
        {
            while(x1<=x2)
            {
                image.setPixel(x1,y1,value);
                x1++;
                y1++;
            }
    }
}
void MainWindow::on_pushButton_clicked()
{
    int x0=20,y0=20;
    int x1=20+length,y1=20;
    int x2=20+length,y2=20+breadth;
    int x3=20,y3=20+breadth;
    bresenham(20,20,100,20);
    bresenham(100,20,100,100);
    bresenham(100,100,0,100);
    bresenham(20,100,20,20);
    ui->label_3->setPixmap(QPixmap::fromImage(image));
    ui->label_3->show();
}
