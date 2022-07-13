#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>
#include <ctime>
#include <ratio>
#include <chrono>

typedef long long int ll;

using namespace std;

class Vertex
{
    public:
        int value;
        int key;
        int rank;
        int prims_parent;
        int kruskals_parent;
        Vertex(int value, int key, int rank, int prims_parent, int kruskals_parent)
        {
            this->value = value;
            this->key = key;
            this->rank = rank;
            this->prims_parent = prims_parent;
            this->kruskals_parent = kruskals_parent;
        }
};

class Edge
{
    public:
        int start;
        int end;
        int weight;
};

class Graph
{
        int V, E;
    public:
        vector<vector<int>> adjacencyMatrix;
        vector<Vertex> vertices;
        vector<Edge> edgeList;
        Graph(int V, int E)
        {

            this->V = V;
            this->E = E;
            vertices.clear();
            edgeList.clear();

            adjacencyMatrix.resize(V, vector<int>(V, -1));
            for (int i = 0; i < V; i++)
            {

                adjacencyMatrix[i][i] = 0;
                Vertex v(i, INT_MAX, 0, -1, i);
                vertices.push_back(v);
            }

        }
        void addEdge(int u, int v, int w);

        void kruskalsMST();
        int kruskals_findSet(int);

        void kruskals_merge(int, int);
        void kruskals_link(int, int);

        void primsMST();
};

void Graph ::addEdge(int u, int v, int w)
{
    // adding edge to graph
    edgeList.push_back({u, v, w});
    adjacencyMatrix[v][u] = w;
    adjacencyMatrix[u][v] = w;
}


bool compareEdgeOnWeight(Edge x, Edge y)
{   
    // comparing edges on edge weight used for sorting edgeList
    return x.weight <= y.weight;
}

void Graph ::kruskalsMST()
{
    // sorting edges on their weights
    sort(edgeList.begin(), edgeList.end(), compareEdgeOnWeight);

    for (auto iter : edgeList)
    {
        int u = iter.start;
        int v = iter.end;
        int w = iter.weight;

        int set_u = kruskals_findSet(u);
        int set_v = kruskals_findSet(v);

        if (set_u != set_v)
        {
            kruskals_merge(set_u, set_v);
        }
    }
}

int Graph ::kruskals_findSet(int u)
{   
    // finds the representative of the set
    if (vertices[u].value != vertices[u].kruskals_parent)
        return kruskals_findSet(vertices[u].kruskals_parent);
    return vertices[u].kruskals_parent;
};

void Graph ::kruskals_merge(int u, int v)
{
    kruskals_link(u, v);
}

void Graph ::kruskals_link(int x, int y)
{
    // linking two sets with representative of set x and y
    if (vertices[x].rank > vertices[y].rank)
    {
        vertices[y].kruskals_parent = x;
    }
    else
    {
        // if rank[x] <= rank[y]
        vertices[x].kruskals_parent = y;
        if (vertices[x].rank == vertices[y].rank)
            vertices[y].rank++;
    }
}


class compareVertexKey
{
    public:
        // comparing keys of two vertices
        bool operator()(Vertex &v, Vertex &u)
        {
            return v.key > u.key;
        }
};

void Graph ::primsMST()
{
    // visited vertices
    vector<bool> mstSet(V, false);

    // 0 is considered as Source Vertex
    vertices[0].key = 0;
    vertices[0].prims_parent = -1;

    // minheap
    priority_queue<Vertex, vector<Vertex>, compareVertexKey> queue;

    queue.push(vertices[0]);

    while (!queue.empty())
    {

        // Extracting the vertex having minimum key value
        auto vertex = queue.top();
        queue.pop();

        int u = vertex.value;
        mstSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (adjacencyMatrix[u][v] > 0 && mstSet[v] == false && adjacencyMatrix[u][v] < vertices[v].key)
            {
                vertices[v].prims_parent = u;
                vertices[v].key = adjacencyMatrix[u][v];
                queue.push(vertices[v]);
            }
        }
    }
}
