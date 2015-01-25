#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <sstream>>

static int set = 0;
static int player = 0;

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

void MainWindow::cross( int i){
    if (i==1){
       // ui->quantum1->setText(player + " ");
        ui->quantum1->setFont(QFont ("Courier", 29));
//        classicalboard.played(1, 3);
    }
    if (set == 0){
        set += 1;
        ui->quantum1->setText(" " + set);
    }
    else{
        set = 0;
        player = 1 - player;
    }
}

void MainWindow::on_quantum1_clicked()
{
    MainWindow::cross(1);
//    ui->quantum1->setText("X");
//    ui->quantum1->setFont(QFont ("Arial", 100));
}

void MainWindow::on_quantum2_clicked()
{
    ui->quantum2->setText("O");
    ui->quantum2->setFont(QFont ("Arial", 100));

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

class ClassicalBoard
