#include "graph.cpp"
#include <fstream>
using namespace std::chrono;

#define V_LOW 1000
#define V_HIGH 15000

int main()
{
    int t = 5;

    ofstream file;
    file.open("result.csv", ios::app);
    srand(time(NULL));
    for (int i = 0; i < t; i++)
    {

        int d = V_HIGH - V_LOW;
        int n = rand() % d + V_LOW;
        int e = rand() % (9 * n) + n;

        cout << "Vertices: " << n << " "
             << "Edges: " << e << "\n";
        Graph g = Graph(n, e);

        file << n << ", " << e << ", ";
        int j = 0;
        e = min(n * (n - 1) / 2, e);
        while (j < e)
        {
            // taking two random vertices
            int u = rand() % n;
            int v = rand() % n;

            if (v == u)
                continue;

            if (g.adjacencyMatrix[u][v] == -1)
            {
                int w = rand() % (2 * n) + 1;
                g.addEdge(u, v, w);
                j++;
            }
        }

        // Get starting timepoint
        auto start = high_resolution_clock::now();

        // Call the function
        g.kruskalsMST();

        // Get ending timepoint
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Kruskal's = "
             << duration.count() << ", ";

        file << duration.count() << ", ";

        // Get starting timepoint
        start = high_resolution_clock::now();

        // Call the function
        g.primsMST();

        // Get ending timepoint
        stop = high_resolution_clock::now();

        duration = duration_cast<microseconds>(stop - start);

        file << duration.count() << "\n";

        cout << "Prim's = "
             << duration.count() << endl;

        cout << "\n";
    }
    file.close();

    return 0;
}