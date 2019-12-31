#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "iostream"
using namespace std;
/*Global Variables*/
int x1,y1;
int x2,y2;
QImage image(851,601,QImage::Format_RGB888);
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
void MainWindow::bresenhamsAlgorithm(){
    int dx=x2-x1;
    int dy=y2-y1;
    int x=x1;
    int y=y1;
    if(abs(dx)>abs(dy)){
        //int pk=2*abs(dy)-abs(dx);
        int pk=2*dy-dx;
        for(int i=0;i<abs(dx);i++){
            image.setPixel(x,y,green);
            x++;
            if(pk<0)
                //pk=pk+2*abs(dy);
                pk=pk+2*dy;
            else{
                y++;
                //pk=pk+2*abs(dy)-2*abs(dx);
                pk=pk+2*dy-2*dx;
            }
        }
    }
    else{
        //int pk=2*abs(dx)-abs(dy);
        int pk=2*dx-dy;
        for(int i=0;i<abs(dy);i++){
            image.setPixel(x,y,green);
            y++;
            if(pk<0)
                //pk=pk+2*abs(dx);
                pk=pk+2*dx;
            else{
                x++;
                //pk=pk+2*abs(dx)-2*abs(dy);
                pk=pk+2*dx-2*dy;
            }
        }
    }
    return;
}
void MainWindow::on_pushButton_clicked()
{
    bresenhamsAlgorithm();
    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
    cout<<x1<<","<<y1<<"\n";
    cout<<x2<<","<<y2<<"\n";
    return;
}
