#include <array>
#include <iostream>
#include <list>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <quantumgraph.h>
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

tictactoe_game::tictactoe_game(void){};

void tictactoe_game::start(tictactoe_player const player)
{
    for (int j=0; j<9; ++j)
    {
        for (int k=0; k<9; ++k)
        {
            qstatus[j][k]=0; // assign 0 to each cell (means no one has made a move)
        }
    }
}

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
    int cell1=getplayermove[1];
    int cell2=getplayermove[2];
    int turnnumber=getplayermove[3]; //get info about what the player did
    qstatus[cell1][turnnumber] = player;
    qstatus[cell2][turnnumber] = player;
}

superqboard_status tictactoe_game::player_chooses_collapse(list<int> nodelist)
{
    //This function generates two options for how to collapse the quantum board
    superqboard_status twooptions;

    int nextnode;
    for (int k=0; k<nodelist.size(); k++)
    {
        list <int>::iterator it;
        it=nodelist.begin();
        int currentnode=*it;
        if (k<nodelist.size()-1)
        {
            advance(it,1);
            nextnode=*it;
        }
        else if (k==nodelist.size()-1)
        {
            it=nodelist.begin();
            nextnode=*it;
        }
        int startfromhere=findstartingelem(currentnode, nextnode);
        twooptions[1][currentnode]=qstatus[currentnode][startfromhere];
        twooptions[2][nextnode]=qstatus[currentnode][startfromhere];
    }
//    qstatus.fill(0);
    for (int p=0; p<9; p++){
        for (int q=0; q<9; q++){
            qstatus[p][q]=0;
        }
    }
    return twooptions;
}

int tictactoe_game::findstartingelem(int i, int nextnode)
{
    int startfromhere;
    for (int j=0; j<9; ++j)
    {
        if (qstatus[i][j]!=0 && qstatus[nextnode][j]==qstatus[i][j])
        {
            startfromhere=j;
        }
    }
    return startfromhere;
}
