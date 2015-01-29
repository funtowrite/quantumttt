// A C++ Program to detect cycle in an undirected graph
#include <iostream>
#include <list>
#include <limits.h>
#include <algorithm>

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
    void resetgraph(int V);
};

QGraph::QGraph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void QGraph::addEdge(int v, int w) //v is the node number. Each node has a list of adjacent nodes
{
    adj[v].push_back(w); // Add w to vs list.
    adj[w].push_back(v); // Add v to ws list.
}

void QGraph::resetgraph(int V)
{
    adj = new list<int>[V];
    int keynode=0;
    nodelist.clear();
    nodesincycle.clear();
}

bool QGraph::detectCycle(int currentnode, int parentnode, bool visited[], bool *recStack) //recursive function returns true if there is a cycle. Depth first search starting from node v.
{
    if(visited[currentnode] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visited[currentnode] = true;
        recStack[currentnode] = true;
        nodelist.push_back(currentnode);
        cout<<currentnode<<" has been added to nodelist"<<endl;

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
       if (!nodelist.empty()){
            nodelist.pop_back();
    }
    cout<<currentnode<<" has been removed from nodelist"<<endl;
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

    // Call the recursive helper function to detect cycle in different
    // DFS trees

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

        for (p=find(nodelist.begin(),nodelist.end(),keynode);p!=nodelist.end();p++)
        {
        nodesincycle.push_back(*p);
        cout<<*p<<endl;
        }
            return true;
        }
    }
    return false;
}

//int main()
//{
//    // Create a graph
//    QGraph g(3);
//    g.addEdge(0, 1);
//   // g.addEdge(1, 2);
//    //g.addEdge(2, 0);

//    if(g.isCyclic())
//    {
//        cout << "Cyclic entanglement detected!! Choose one way to collapse!";
//    }
//    else
//    {
//        cout << "No cycles at the moment.";
//    }

//    return 0;
//}
