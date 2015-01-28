#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quantumgraph.h"
#include <string>
#include <sstream>>
#include <vector>
#include <QDebug>
using namespace std;
static int player = 0;
static int turn =0;
static vector<int> chosen;
//static vector<auto*> boxes = ;

MainWindow::MainWindow(QWidget *parent) :
//    board = new ClassicalBoard;
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraph graph(8);
}

MainWindow::~MainWindow()
{
    delete graph;
    delete ui;
}

void MainWindow::enable(int j, bool enabled){
    switch(j){
        case 1:
            ui->quantum1->setEnabled(enabled);
            break;
        case 2:
            ui->quantum2->setEnabled(enabled);
            break;
        case 3:
            ui->quantum3->setEnabled(enabled);
            break;
        case 4:
            ui->quantum4->setEnabled(enabled);
            break;
        case 5:
            ui->quantum5->setEnabled(enabled);
            break;
        case 6:
            ui->quantum6->setEnabled(enabled);
            break;
        case 7:
            ui->quantum7->setEnabled(enabled);
            break;
        case 8:
            ui->quantum8->setEnabled(enabled);
            break;
        case 9:
            ui->quantum9->setEnabled(enabled);
            break;
        default:
            break;
    }
}

void MainWindow::mark( int i){
    switch(i){
        case 1:
            //TBD: getText from Square and setText
            ui->quantum1->setText("1");
            break;
        case 2:
            ui->quantum2->setText("2");
            break;
        case 3:
            ui->quantum3->setText("3");
            break;
        case 4:
            ui->quantum4->setText("4");
            break;
        case 5:
            ui->quantum5->setText("5");
            break;
        case 6:
            ui->quantum6->setText("6");
            break;
        case 7:
            ui->quantum7->setText("7");
            break;
        case 8:
            ui->quantum8->setText("8");
            break;
        case 9:
            ui->quantum9->setText("9");
//            ui->comboBox->removeItem(0);
            break;
        default:
            break;
    }
//    ui->comboBox->addItem("item " + QString::number(i));
    chosen.push_back(i);
    MainWindow::enable(i, false);
//    ui->quantum1->setFont(QFont ("Courier", 29));

    //if two squares have been selected: reset count and change players
    if (chosen.size() == 2){
        player = 1 - player;
        turn += 1;
        graph->addEdge(chosen[0], chosen[1]);
        for(int z=0; z<2; z++){
            int square = chosen[1-z];
            MainWindow::enable(square, true);
            chosen.pop_back();
        }
    }

    //if cycle is detected: populate the dropdown, disable all buttons, enable the submitbutton
    if (graph->isCyclic()){

    }
}

void MainWindow::on_quantum1_clicked()
{
    MainWindow::mark(1);
//    ui->quantum1->setFont(QFont ("Arial", 100));
}

void MainWindow::on_quantum2_clicked()
{
    MainWindow::mark(2);
//    ui->quantum2->setFont(QFont ("Arial", 100));

}

void MainWindow::on_quantum3_clicked()
{
     MainWindow::mark(3);
}

void MainWindow::on_quantum4_clicked()
{
     MainWindow::mark(4);
}

void MainWindow::on_quantum5_clicked()
{
     MainWindow::mark(5);
}

void MainWindow::on_quantum6_clicked()
{
     MainWindow::mark(6);
}

void MainWindow::on_quantum7_clicked()
{
     MainWindow::mark(7);
}

void MainWindow::on_quantum8_clicked()
{
     MainWindow::mark(8);
}

void MainWindow::on_quantum9_clicked()
{
     MainWindow::mark(9);
}

//will only be clicked when collapsing squares
//onclick: disable button, change classical board text, disable quantum board squares
void MainWindow::on_submitBtn_clicked()
{
//    ui->submitBtn->setEnabled(false);
}

//class ClassicalBoard{

//};
