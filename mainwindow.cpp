#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "quantumgraph.h"
#include "classical_board.h"
#include "quantumboard.h"
#include <string>
#include <sstream>
#include <vector>
#include <QDebug>
#include <sstream>
#include <algorithm>

using namespace std;
static int player = 1;
static int turn =0;
static vector<int> chosen;
//static vector<Ui*> boxes;
QGraph graph(9);
Board board(3);
tictactoe_game game;
static int first;
static int second;
int squareToChoose;
array<int[9], 2> superqboard;
//typedef array<int[9], 2> superqboard_status;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
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

void MainWindow::markQuantum(string n, int k){
    QString m = QString::fromStdString(n);
    switch(k){
        case 1:
            ui->quantum1->setText(m);
            break;
        case 2:
            ui->quantum2->setText(m);
            break;
        case 3:
            ui->quantum3->setText(m);
            break;
        case 4:
            ui->quantum4->setText(m);
            break;
        case 5:
            ui->quantum5->setText(m);
            break;
        case 6:
            ui->quantum6->setText(m);
            break;
        case 7:
            ui->quantum7->setText(m);
            break;
        case 8:
            ui->quantum8->setText(m);
            break;
        case 9:
            ui->quantum9->setText(m);
            break;
    }
}

void MainWindow::markClassical(string n, int k){
    QString m = QString::fromStdString(n);
    switch(k){
        case 1:
            ui->classical1->setText(m);
            ui->classical1->setFont(QFont ("Arial", 100));
            break;
        case 2:
            ui->classical2->setText(m);
            ui->classical2->setFont(QFont ("Arial", 100));
            break;
        case 3:
            ui->classical3->setText(m);
            ui->classical3->setFont(QFont ("Arial", 100));
            break;
        case 4:
            ui->classical4->setText(m);
            ui->classical4->setFont(QFont ("Arial", 100));
            break;
        case 5:
            ui->classical5->setText(m);
            ui->classical5->setFont(QFont ("Arial", 100));
            break;
        case 6:
            ui->classical6->setText(m);
            ui->classical6->setFont(QFont ("Arial", 100));
            break;
        case 7:
            ui->classical7->setText(m);
            ui->classical7->setFont(QFont ("Arial", 100));
            break;
        case 8:
            ui->classical8->setText(m);
            ui->classical8->setFont(QFont ("Arial", 100));
            break;
        case 9:
            ui->classical9->setText(m);
            ui->classical9->setFont(QFont ("Arial", 100));
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
    QString x = QString::fromStdString("X");
    QString o = QString::fromStdString("O");
    int p1 = MainWindow::num_wins(moves, x);
    int p2 = MainWindow::num_wins(moves, o);
    ui->p1score->setText(QString::number(p1));
    ui->p2score->setText(QString::number(p2));
    qDebug()<<"Player 1 Score: "<<p1;
    qDebug()<<"Player 2 Score: "<<p2;
}

int MainWindow::num_wins(vector<int> moves, QString c){
    int wins = 0;
    QString val0 = ui->classical1->text();
    QString val1 = ui->classical2->text();
    QString val2 = ui->classical3->text();
    QString val3 = ui->classical4->text();
    QString val4 = ui->classical5->text();
    QString val5 = ui->classical6->text();
    QString val6 = ui->classical7->text();
    QString val7 = ui->classical8->text();
    QString val8 = ui->classical9->text();
    qDebug()<<val0<<val1<<val2<<val3<<val4<<val5<<val6<<val7<<val8;

    if (val0 == val1 && val1 == val2 && val0 == c){
        wins++;
    }
    if (val3 == val4 && val4 == val5 && val3 == c){
        wins++;
    }
    if (val6 == val7 && val7 == val8 && val6 == c){
        wins++;
    }
    if (val0 == val3 && val3 == val6 && val0 == c){
        wins++;
    }
    if (val1 == val4 && val4 == val7 && val1 == c){
        wins++;
    }
    if (val2 == val5 && val5 == val8 && val2 == c){
        wins++;
    }
    if (val0 == val4 && val4 == val8 && val0 == c){
        wins++;
    }
    if (val2 == val4 && val4 == val6 && val2 == c){
        wins++;
    }
    return wins;
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
        cout<<"line 232 of main"<<endl;
        player = 3 - player;
        ui->player->setText(QString::number(player));
        turn += 1;
        graph.addEdge(chosen[0]-1, chosen[1]-1);
        MainWindow::enable(chosen[0], true);
        MainWindow::enable(chosen[1], true);
        chosen.push_back(turn);

        int chose[3];
        chose[0] = chosen[0]-1;
        chose[1] = chosen[1]-1;
        chose[2] = chosen[2];
        cout<<"calling update"<<endl;
        game.update(chose, player, graph); //takes in a vector??
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
    //enable dropdown and submit button
    //getfromcycle the two ways to collapse
    //iterate through the two lists until they are not the same
    //call enable that box, let the user choose who is and submit
    //pass chosen list to
    //re-enable all squares that are left

    superqboard = game.player_chooses_collapse(graph.nodelist);
    for(int u= 0 ;  u < 9; u++){
        cout << "matching" <<superqboard[0][u] <<"   "<< u<<"   "<< superqboard[1][u]<<endl;
        if (superqboard[0][u] !=superqboard[1][u]){
            squareToChoose = u;
            break;
        }
    }
    first = superqboard[0][squareToChoose];
    second = superqboard[1][squareToChoose];
    cout<<"square to choose"<<squareToChoose<<endl;
    MainWindow::markQuantum("Choose a\nmark for\nthis board", squareToChoose+1);
    ui->comboBox->addItem("X");
    ui->comboBox->addItem("O");
    ui->comboBox->setEnabled(true);
    ui->submitBtn->setEnabled(true);


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
//onclick: disable button and clear and disable dropdown, change classical board text, disable quantum board squares
void MainWindow::on_submitBtn_clicked()
{
   //cout << ui->comboBox->itemData(ui->comboBox->currentIndex())<<endl;
    int selected = ui->comboBox->currentIndex();
    //    graph.reset_graph();
    vector<int> vec1;
    vector<int> vec2;
    //superqboard_status = game.player_chooses_collapse(graph.nodelist);

    qDebug()<<"First option"<<endl;
    for(int u= 0 ;  u < 9; u++){
        vec1.push_back(superqboard[0][u]);
        MainWindow::enable(u+1, true);
        qDebug()<<superqboard[0][u]<<endl;
    }

    for(int u= 0 ;  u < 9; u++){
        if(superqboard[0][u]!=0){
            MainWindow::enable(u+1, false);
        }
        if (superqboard[0][u] == 0){
            qDebug()<< "its *** "<< u;
            MainWindow::enable(u+1, true);
        }
        else{
            MainWindow::markQuantum("cleared", u+1);
        }
        vec2.push_back(superqboard[1][u]);
    }
    if (selected == first-1){
       //std::copy_n(superqboard_status[0], 9, buf);
        MainWindow::translate(vec1);

    }
    else{
       MainWindow::translate(vec2);
    }
    ui->submitBtn->setEnabled(false);
    ui->comboBox->clear();
    ui->comboBox->setEnabled(false);
    graph.resetgraph(9);



}
