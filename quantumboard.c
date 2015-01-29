#include <array>
#include <iostream>
#include <list>
#include <limits.h>
#include <algorithm>
#include <vector>

using namespace std;

enum class tictactoe_player : int
{
    none = 0,
    player1 = 1,
    player2 = 2,
    blocked = 3, //for instance after collapse has occured.
};

class QGraph
{
    friend class tictactoe_game
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists. Each element of the array corresponds to one cell of the tic-tac-toe graph.
    bool detectCycle(int currentnode, int parentnode, bool visited[], bool *rs);  // used by isCyclic()
    list<int> nodesincycle;    // final list of nodes in the cycle

public:
    QGraph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    bool isCyclic();    // returns true if there is a cycle in this graph
    int keynode; // name of a node present within the cycle
    list<int> nodelist;    // shortlist of nodes that might be in the cycle
};


typedef array<int[9], 9> qboard_status;

class tictactoe_game //controls the game
{
public:
    friend class QGraph; //records the entanglement on a box level
    qboard_status qstatus; // initalizes the array that records the status of the quantum board
};

QGraph::QGraph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void QGraph::addEdge(int v, int w) //v is the node number. Each node has a list of adjacent nodes
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v); // Add v to w’s list.
}

bool QGraph::detectCycle(int currentnode, int parentnode, bool visited[], bool *recStack) //recursive function returns true if there is a cycle. Depth first search starting from node v.
{
    if(visited[currentnode] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[currentnode] = true;
        recStack[currentnode] = true;
        nodelist.push_back(currentnode);
//        cout<<currentnode<<" has been added to nodelist"<<endl;

        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[currentnode].begin(); i != adj[currentnode].end(); ++i) //begin returns a pointer to the first element in adj
        {
            if ( !visited[*i] && detectCycle(*i, currentnode, visited, recStack) && *i!=parentnode)
            {
                // i is a pointer to a node, n. If node n has been visited and
                return true;
            }
            else if ((recStack[*i]) && *i!=parentnode)
            {
                cout<<"Node "<<*i<<" found on recStack"<<endl;
                keynode = *i;
                cout<<"current node is "<<currentnode<<endl;
                return true;
            }
            else if ((*i==parentnode) && adj[currentnode].size()>1) //attempt to find two copies of parentnode in the adjacency list of currentnode
            {
                list<int>::iterator it;
                int count = 0 ;
                it = adj[currentnode].begin();
                for (int p=0; p<adj[currentnode].size(); ++p)
                {
                    if (*it == parentnode)
                    {
                        count+=1;
                    }

                    advance(it,1);
                    if (count==2)
                    {
                        keynode = *i;
                        return true;
                    }

                }
            }

        }
    }
    recStack[currentnode] = false;  // remove the vertex from recursion stack
    if !nodelist.empty(){
            nodelist.pop_back();
    }
    //  cout<<currentnode<<" has been removed from nodelist"<<endl;
    return false;
}

// Returns true if the graph contains a cycle, else false.
bool QGraph::isCyclic()
{
    // Starting condition; mark all the vertices as not visited and not part of recursion
    // stack
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    for(int i = 0; i < V; i++) //Examines all the nodes of the graph.
    {
        list<int>::iterator it;
        cout<<"Adjacency list for node "<<i<< " is "<< endl;
        for (it= adj[i].begin(); it != adj[i].end(); ++it)
        {
            cout<< *it <<endl;
        }
    }
    for(int i = 0; i < V; i++) //Examines all the nodes of the graph.
    {
        if (detectCycle(i, i, visited, recStack))
        {
            list<int>::iterator p;

            for (p=find(nodelist.begin(),nodelist.end(),keynode); p!=nodelist.end(); p++)
            {
                nodesincycle.push_back(*p);
                cout<<*p<<endl;
            }
            return true;
        }
    }
    return false;
}

void tictactoe_game::start(tictactoe_player const player)
{
    for (int j=0; j<9; ++j)
    {
        for (int k=0; k<9; ++k)
        {
            qstatus[j][k]=0; // assign 0 to each cell (means no one has made a move)
        }
    }
    playing = true;
}

tictactoe_game::struct tictactoe_cell //indexes each vector representing a cell by its row and column
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

bool tictactoe_game::move(tictactoe_cell const cell, tictactoe_player const player)
{
    getplayerinfo = getspookyfromplayer(player) ; //player decides where to put spooky marks
    cell1=getplayerinfo[1];
    cell2=getplayerinfo[2];
    turnnumber=getplayerinfo[3];

    if(qstatus[cell1] != 3 && qstatus[cell2] != 3)// if they're not blocked
    {
        qstatus[cell1][turnnumber] = player;
        qstatus[cell2][turnnumber] = player;
        qgraph.addEdge(cell1,cell2);

        if(qgraph.isCyclic()) // if detect a cyclic entanglement
        {
            cout << "Cyclic entanglement detected!! Choose one way to collapse!"; //now, player enters either 1 or 2
            playing = false;
            collapsing = true;
            auto newstatus = player_chooses_collapse(player, cell1, cell2);
            for (i=0; i<nodelist; i++)
            {
                qstatus[nodelist[i]]=3;
            }

            auto newgraph = reset_graph();
            //issue a call to the collapsing function
        }
        return true;
    }
    return false; //if blocked (ie. 3), return false
}

typedef array<int[9], 2> superqboard_status;

superqboard_status tictactoe_game::player_chooses_collapse(tictactoe_player player) const
{
    //This function generates two options for how to collapse the quantum board

    superqboard_status twooptions;

    for (int k=1; k<nodelist.size(), k++)
    {
        i=nodelist(k);
        if (k<nodelist.size()-1)
        {
            nextnode=nodelist[i+1];
        }
        else if (k==nodelist.size()-1)
        {
            nextnode=nodelist[1];
        }
        startfromhere=findstartingelem(i);
        twooptions[1][i]=qboard_status[i][startfromhere];
        twooptions[2][nextnode]=qboard_status[i][startfromhere];
    }
    return twooptions;
}

int findstartingelem(int i, int nextnode, qboard_status qstatus)
{
    for (int j=0; j<9; ++j)
    {
        if (qstatus[i][j]!=0 && qstatus[nextnode][j]==qstatus[i][j])
        {
            startfromhere=j;
        }
    }
    return startfromhere;
}
