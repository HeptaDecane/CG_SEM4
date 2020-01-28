#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColorDialog"
#include "iostream"
using namespace std;

QImage image(541,381,QImage::Format_RGB888);
QImage pallete(71,31,QImage::Format_RGB888);
QColor color;
QRgb green=qRgb(0,255,0);
int i=0,x1,y1,x2,y2,r,g,b;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
    vertices=0;
    start=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::mousePressEvent(QMouseEvent *events){
    int x,y;
    if(!start)return;
    if(i<vertices){
        x=events->pos().x();
        y=events->pos().y();

        coordinates[i][0]=x;
        coordinates[i][1]=y;
        cout<<x<<" "<<y<<"\n";
        image.setPixel(x,y,green);
        i++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}
void MainWindow::on_plainTextEdit_textChanged()
{
    QString str=ui->plainTextEdit->toPlainText();
    vertices=str.toInt();
    start=true;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0;i<vertices-1;i++){
        x1=coordinates[i][0];
        y1=coordinates[i][1];
        x2=coordinates[i+1][0];
        y2=coordinates[i+1][1];
        ddaLine(x1,y1,x2,y2);
    }
    x1=coordinates[0][0];
    y1=coordinates[0][1];
    ddaLine(x1,y1,x2,y2);
}
void MainWindow::ddaLine(int x1, int y1, int x2, int y2){
    float dx,dy,steps,xinc,yinc;
    dx=x2-x1;
    dy=y2-y1;

    steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    xinc=dx/steps;
    yinc=dy/steps;

    float x=x1;
    float y=y1;

    for(int i=0;i<=steps;i++){
        image.setPixel(x,y,green);
        x=x+xinc;
        y=y+yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
    ui->label->show();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    r=value;

    ui->label_2->setPixmap(QPixmap::fromImage(pallete));
    ui->label_2->show();
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    g=value;
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    b=value;
}
