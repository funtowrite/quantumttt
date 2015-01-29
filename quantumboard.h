#include <array>
#include <iostream>
#include <list>
#include <limits.h>
#include <algorithm>
#include <vector>
#include "quantumgraph.h"
#include <stdio.h>

using namespace std;

enum class tictactoe_player : int
{
    none = 0,
    player1 = 1,
    player2 = 2,
};

typedef array<int[9], 9> qboard_status;
typedef array<int[9], 2> superqboard_status;

class tictactoe_game //controls the game
{
public:
    tictactoe_game();
    qboard_status qstatus; // initalizes the array that records the status of the quantum board
    superqboard_status player_chooses_collapse(list<int> list);//

    void start(tictactoe_player const player);
    void update(int[3] , int, QGraph );
    int findstartingelem(int i, int nextnode);
};

tictactoe_game::tictactoe_game(){
    cout << "Initialized game" << endl;
};

void tictactoe_game::start(tictactoe_player const player)
{
    for (int j=0; j<9; ++j)
    {
        for (int k=0; k<9; ++k)
        {
            qstatus[j][k]=0; // assign 0 to each cell (means no one has made a move)
        }
    }
};

struct tictactoe_cell //indexes each vector representing a cell by its row and column
{
    int row;
    int col;

    tictactoe_cell(int r = INT_MAX, int c = INT_MAX):row(r), col(c) // initializes row(r) and col(c) to INT_MAX (because the value
        // cannot be changed inside a constructor).
    {}

    bool is_valid() const
    {
        return row != INT_MAX && col != INT_MAX;
    }
};

void tictactoe_game::update(int getplayermove[3], int player, QGraph qgraph)
{
    cout<<"update has been called"<<endl;
    int cell1=getplayermove[0];
    int cell2=getplayermove[1];
    int turnnumber=getplayermove[2]; //get info about what the player did
    qstatus[cell1][turnnumber] = player;
    qstatus[cell2][turnnumber] = player;
};

superqboard_status tictactoe_game::player_chooses_collapse(list<int> nodelist)
{
    //This function generates two options for how to collapse the quantum board
    superqboard_status twooptions;
    for (int o=0; o<2; o++){
        for(int w=0; w<9; w++){
            twooptions[o][w] = 0;
        }
    }
        cout<<"line 83"<<endl;
    int nextnode;
    list <int>::iterator it;
    it=nodelist.begin();
    //iterate thorugh all nodes in the nodelist
    for (int k=0; k<nodelist.size(); k++)
    {
        cout<<"line 90"<<endl;
        int currentnode= *it;
        qDebug()<<"the iterator is pointing at"<<*it<<endl;
        qDebug()<<"k is"<<k<<endl;
        if (k<nodelist.size()-1)
        {
            advance(it,1);
            nextnode=*it;
            qDebug()<<"line 87, next node is"<<nextnode<<endl;
        }
        else if (k==nodelist.size()-1)
        {
            it=nodelist.begin();
            nextnode=*it;
        }
        int startfromhere=findstartingelem(currentnode, nextnode);

        qDebug()<<"qstatus is"<<endl;
        for (int o=0; o<9; o++){
            for(int w=0; w<9; w++){
                qDebug()<< qstatus[o][w];
            }
            qDebug()<<endl;
        }

        qDebug()<<"currentnode is "<<currentnode<<endl;
            qDebug()<<"nextnode is "<<nextnode<< " startfrom here"<<startfromhere << "Will print the following symbol "<<qstatus[currentnode][startfromhere]<< " &&&&&&&" << qstatus[currentnode][startfromhere]<< endl;
        twooptions[0][currentnode]=qstatus[currentnode][startfromhere];
        twooptions[1][nextnode]=qstatus[currentnode][startfromhere];
        cout<<"after currentnode is "<<currentnode<<endl;
            cout<<"after nextnode is "<<nextnode<<endl;
    }


    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            qstatus[i][j] = 0;
        }
    }
    //qstatus.fill(0);
//    for (int p=0; p<9; p++){
//        qstatus[p].fill(0);
//    }
//    memset(qstatus, 0, sizeof(qstatus[0][0]) * 9 * 9);

    return twooptions;
}

int tictactoe_game::findstartingelem(int i, int nextnode)
{
    int startfromhere;
    //for each box, find the element that is not None,
    for (int j=0; j<9; ++j)
    {
        if (qstatus[i][j]!=0 && (qstatus[nextnode][j]==qstatus[i][j]))
        {
            startfromhere=j;
        }
    }
    return startfromhere;
}
