#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

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

//void cross( int i){
//    if (i==1){
//        ui->quantum1->setText("clicked");
//        ui->quantum1->setFont(QFont ("Courier", 29))
//    }
//}

void MainWindow::on_quantum1_clicked()
{
//    cross(1);
    ui->quantum1->setText("X    \n \n");
    string a = ui->quantum1->getText();

//    ui->quantum1->set;
}

void MainWindow::on_quantum2_clicked()
{
    ui->quantum2->setText("X \n \n");
    ui->quantum2->setEnabled(false);
}

void MainWindow::on_quantum3_clicked()
{

}

void MainWindow::on_quantum4_clicked()
{

}

void MainWindow::on_quantum5_clicked()
{

}

void MainWindow::on_quantum6_clicked()
{

}

void MainWindow::on_quantum7_clicked()
{

}

void MainWindow::on_quantum8_clicked()
{

}

void MainWindow::on_quantum9_clicked()
{

}
