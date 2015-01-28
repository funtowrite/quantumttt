// A C++ Program to detect cycle in an undirected graph
#include <iostream>
#include <list>
#include <limits.h>
#include <algorithm>
#include <QDebug>

using namespace std;

class QGraph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists. Each element of the array corresponds to one cell of the tic-tac-toe graph.
    bool detectCycle(int currentnode, int parentnode, bool visited[], bool *rs);  // used by isCyclic()
public:
    QGraph(int V);   // Constructor
    void addEdge(int v, int w);   // to add an edge to graph
    bool isCyclic();    // returns true if there is a cycle in this graph
    int keynode; // name of a node present within the cycle
    list<int> nodelist;    // shortlist of nodes that might be in the cycle
    list<int> nodesincycle;    // final list of nodes in the cycle
    ~QGraph();
};

QGraph::QGraph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

QGraph::~QGraph()
{
    for(int z=0; z < V; z++){
        adj[z].clear();
    }
    adj->clear();
    nodelist.clear();
    nodesincycle.clear();
}

void QGraph::addEdge(int v, int w) //v is the node number. Each node has a list of adjacent nodes
{
    adj[v].push_back(w); // Add w to vs list.
    adj[w].push_back(v); // Add v to ws list.
}

bool QGraph::detectCycle(int currentnode, int parentnode, bool visited[], bool *recStack) //recursive function returns true if there is a cycle. Depth first search starting from node v.
{
    if(visited[currentnode] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[currentnode] = true;
        recStack[currentnode] = true;
        nodelist.push_back(currentnode);
        qDebug()<<currentnode<<" has been added to nodelist"<<endl;

        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for(i = adj[currentnode].begin(); i != adj[currentnode].end(); ++i) //begin returns a pointer to the first element in adj
        {
            if ( !visited[*i] && detectCycle(*i, currentnode, visited, recStack) && *i!=parentnode)
            {
                // i is a pointer to a node, n. If node n has been visited and
                qDebug()<<"Node "<<*i<<" has been visited"<<endl;
                return true;
            }
            else if ((recStack[*i]) && *i!=parentnode)
            {
                qDebug()<<"Node "<<*i<<" found on recStack"<<endl;
                keynode = *i;
                qDebug()<<"current node is "<<currentnode<<endl;
                //nonreciprocal_cycle.push_back(*i);
                return true;
            }
            else if ((*i==parentnode) && adj[currentnode].size()>1) //attempt to find two copies of parentnode in the adjacency list of currentnode
            {
                list<int>::iterator it;
                int count = 0 ;
                qDebug()<<"count is "<<count<<endl;
                it = adj[currentnode].begin();
                for (int p=0; p<adj[currentnode].size(); ++p)
                {
                    cout<<"p is "<<p<<endl;
                    if (*it == parentnode)
                    {
                        // cout<< "at position "<<p<< " of list "<<currentnode<< " we have the element "<<*it<<endl;
                        //cout<<"count is "<<count<<endl;
                        count+=1;
                        //cout<<"count has been incremented, new count is "<<count<<endl;
                    }

                    advance(it,1);
                    cout<<"count is "<<count<<endl;
                    if (count==2)
                    {
                        cout << "aha! Trouble at node" << *i <<endl;
                        return true;
                    }

                }
            }

        }
    }
    recStack[currentnode] = false;  // remove the vertex from recursion stack
    nodelist.pop_back();
    cout<<currentnode<<" has been removed from nodelist"<<endl;
    return false;
}


// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in http://www.geeksforgeeks.org/archives/18212
bool QGraph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    // Call the recursive helper function to detect cycle in different
    // DFS trees

    for(int i = 0; i < V; i++) //Examines all the nodes of the graph.
    {
        list<int>::iterator it;
        qDebug()<<"Adjacency list for node "<<i<< " is "<< endl;
        for (it= adj[i].begin(); it != adj[i].end(); ++it)
        {
            qDebug()<< *it <<endl;
        }
    }
    for(int i = 0; i < V; i++) //Examines all the nodes of the graph.
    {
        qDebug()<<i;
        if (detectCycle(i, i, visited, recStack))
        {
        list<int>::iterator p;

        for (p=find(nodelist.begin(),nodelist.end(),keynode);p!=nodelist.end();p++)
        {
        nodesincycle.push_back(*p);
        qDebug()<<*p<<endl;
        }
            return true;
        }
    }

    return false;
}

//int main()
//{
//    // Create a graph given in the above diagram
//    QGraph g(8);
//    g.addEdge(2, 3);
//    g.addEdge(0, 1);
//    g.addEdge(5,6);
//    g.addEdge(0, 2);
//    g.addEdge(2, 5);
//    g.addEdge(4, 6);
//    g.addEdge(2,4);
//    g.addEdge(6,7);
//
//    if(g.isCyclic())
//    {
//        cout << "Cyclic entanglement detected!! Choose one way to collapse!";
//    }
//    else
//    {
//        cout << "No cycles at the moment.";
//    }
//
//    return 0;
//}
