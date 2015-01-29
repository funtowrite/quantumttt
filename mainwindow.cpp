#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "quantumgraph.h"
#include "classical_board.h"
#include <string>
#include <sstream>
#include <vector>
#include <QDebug>
#include <sstream>
using namespace std;
static int player = 1;
static int turn =0;
static vector<int> chosen;
//static vector<Ui*> boxes;
QGraph graph(9);
Board board(3);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    boxes={ui->quantum1, ui->quantum2};
}

MainWindow::~MainWindow()
{
//    delete graph;
    delete ui;
    chosen.clear();

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

void MainWindow::markClassical(string n, int k){
    QString m = QString::fromStdString(n);
    switch(k){
        case 1:
            ui->classical1->setText(m);
            break;
        case 2:
            ui->classical2->setText(m);
            break;
        case 3:
            ui->classical3->setText(m);
            break;
        case 4:
            ui->classical4->setText(m);
            break;
        case 5:
            ui->classical5->setText(m);
            break;
        case 6:
            ui->classical6->setText(m);
            break;
        case 7:
            ui->classical7->setText(m);
            break;
        case 8:
            ui->classical8->setText(m);
            break;
        case 9:
            ui->classical9->setText(m);
            break;
    }
}

void MainWindow::translate(vector<int> moves){
    for (int i = 0; i < moves.size(); i++){
        if (moves[i] == 1){
            MainWindow::markClassical("X", i+1);
        }
        else if (moves[i] == 2){
            MainWindow::markClassical("O", i+1);
        }

    }
}

void MainWindow::mark( int i){
    string symbol;
    if (player == 1){
        symbol = "X";
    }
    else {
        symbol = "O";
    }
    //symbol += QString::number(turn);

    stringstream ss;
    ss << turn;
    string str = ss.str();

    symbol += str;
    QString symbol2;// = QString::fromStdString(symbol);
    switch(i){
        case 1:
            //TBD: getText from Square and setText
            board.add(symbol, 0);
            //s = board.get_squares()[0];
            symbol2 = QString::fromStdString(board.get_squares()[0].format_string());
            ui->quantum1->setText(symbol2);
            break;
        case 2:
            board.add(symbol, 1);
            symbol2 = QString::fromStdString(board.get_squares()[1].format_string());
            ui->quantum2->setText(symbol2);

            break;
        case 3:
            board.add(symbol, 2);
            symbol2 = QString::fromStdString(board.get_squares()[2].format_string());
            ui->quantum3->setText(symbol2);

            break;
        case 4:
            board.add(symbol, 3);
            symbol2 = QString::fromStdString(board.get_squares()[3].format_string());
            ui->quantum4->setText(symbol2);
            break;
        case 5:
            board.add(symbol, 4);
            symbol2 = QString::fromStdString(board.get_squares()[4].format_string());
            ui->quantum5->setText(symbol2);
            break;
        case 6:
            board.add(symbol, 5);
            symbol2 = QString::fromStdString(board.get_squares()[5].format_string());
            ui->quantum6->setText(symbol2);
            break;
        case 7:
            board.add(symbol, 6);
            symbol2 = QString::fromStdString(board.get_squares()[6].format_string());
            ui->quantum7->setText(symbol2);
            break;
        case 8:
            board.add(symbol, 7);
            symbol2 = QString::fromStdString(board.get_squares()[7].format_string());
            ui->quantum8->setText(symbol2);
            break;
        case 9:
            board.add(symbol, 8);
            symbol2 = QString::fromStdString(board.get_squares()[8].format_string());
            ui->quantum9->setText(symbol2);
//            ui->comboBox->removeItem(0);
            break;
        default:
            break;
    }

    chosen.push_back(i);
    MainWindow::enable(i, false);

    //if two squares have been selected: reset count and change players
    if (chosen.size() == 2){
        player = 3 - player;
        ui->player->setText(QString::number(player));
        turn += 1;
        graph.addEdge(chosen[0]-1, chosen[1]-1);
            MainWindow::enable(chosen[0], true);
            MainWindow::enable(chosen[1], true);
            chosen.clear();        
            if (graph.isCyclic()){
                for (int y=1; y<10; y++){
                    MainWindow::enable(y, false);
                }
                MainWindow::collapseCycle();
            }
//                ui->comboBox->addItem("item " + QString::number(i));

    }

   /* vector<int> moves;
    moves.push_back(1);
    moves.push_back(2);
    moves.push_back(0);
    moves.push_back(1);
    moves.push_back(2);
    moves.push_back(0);
    moves.push_back(1);
    moves.push_back(2);
    moves.push_back(0);

    MainWindow::translate(moves);*/
    //if cycle is detected: populate the dropdown, disable all buttons, enable the submitbutton

}

void MainWindow::collapseCycle(){
    //getfromcycle the two ways to collapse
    //iterate through the two lists until they are not the same
    //call enable that box, let the user choose who is and submit
    //pass chosen list to
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
