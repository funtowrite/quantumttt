#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <sstream>>

static int set = 0;
static int player = 0;
static int turn =0;

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

void MainWindow::mark( int i){
    switch(i){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            break;
    }

//    if (i==1){

//    ui->quantum1->setFont(QFont ("Courier", 29));
//    }
    //counts to see whether two squares have been selected
    if (set == 0){
        set += 1;
    }
    else{
        set = 0;
        player = 1 - player;
        turn += 1;
    }
}

void MainWindow::on_quantum1_clicked()
{
//    MainWindow::mark(1);
//    ui->quantum1->setText("X1  o2  x3  \n \no4  x5  o6\n\nx7  o8  x9");
//    ui->quantum1->setFont(QFont ("Arial", 100));
}

void MainWindow::on_quantum2_clicked()
{
//    MainWindow::mark(2);
    ui->quantum2->setText("O");
    ui->quantum2->setFont(QFont ("Arial", 100));

}

void MainWindow::on_quantum3_clicked()
{
//     MainWindow::mark(3);
}

void MainWindow::on_quantum4_clicked()
{
//     MainWindow::mark(4);
}

void MainWindow::on_quantum5_clicked()
{
//     MainWindow::mark(5);
}

void MainWindow::on_quantum6_clicked()
{
//     MainWindow::mark(6);
}

void MainWindow::on_quantum7_clicked()
{
//     MainWindow::mark(7);
}

void MainWindow::on_quantum8_clicked()
{
//     MainWindow::mark(8);
}

void MainWindow::on_quantum9_clicked()
{
//     MainWindow::mark(9);
}


class ClassicalBoard{

};
