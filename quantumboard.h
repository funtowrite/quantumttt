#include <array>
#include <iostream>
#include <list>
#include <limits.h>
#include <algorithm>
#include <vector>
#include "quantumgraph.h"

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
    qboard_status qstatus; // initalizes the array that records the status of the quantum board
    superqboard_status player_chooses_collapse(list<int> list);//
    int findstartingelem(int, int);
    void update(int[3], tictactoe_player, QGraph);
    void start(tictactoe_player);
};

//tictactoe_game::tictactoe_game(void);

void tictactoe_game::start(tictactoe_player const player)
{
    for (int j=0; j<9; ++j)
    {
        for (int k=0; k<9; ++k)
        {
            qstatus[j][k]=0; // assign 0 to each cell (means no one has made a move)
        }
    }
    bool playing = true;
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

void tictactoe_game::update(int getplayermove[3], tictactoe_player player, QGraph qgraph)
{
    int cell1=getplayermove[1];
    int cell2=getplayermove[2];
    int turnnumber=getplayermove[3]; //get info about what the player did
    qstatus[cell1][turnnumber] = player;
    qstatus[cell2][turnnumber] = player;
}

superqboard_status tictactoe_game::player_chooses_collapse(list<int> list)
{
    //This function generates two options for how to collapse the quantum board
    superqboard_status twooptions;

    for (int k=1; k<list.size(); k++){
        int i=list(k);
        if (k<list.size()-1)
        {
            nextnode=list[i+1];
        }
        else if (k==list.size()-1)
        {
            nextnode=list[1];
        }
        int startfromhere=findstartingelem(i, nextnode);
        twooptions[1][i]=qstatus[i][startfromhere];
        twooptions[2][nextnode]=qstatus[i][startfromhere];
    }
    memset(qstatus, 0, sizeof(qstatus[0][0]) * 9 * 9);
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
