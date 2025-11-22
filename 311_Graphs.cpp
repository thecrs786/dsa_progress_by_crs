#include <iostream>
#include <vector>
#include <list> // Using doubly linked list for adjacency list representation
using namespace std;

/*
GRAPH BASICS:

A graph G = (V, E) consists of:
- V: Set of vertices (nodes)
- E: Set of edges (connections between nodes)

Types of graphs:
1. Directed Graph (Digraph): edges have direction u -> v
2. Undirected Graph: edges have no direction u - v
3. Weighted Graph: edges carry a weight (distance, cost, etc.)
4. Unweighted Graph: edges have no weight
5. Cyclic / Acyclic: cycles exist or not
6. Sparse / Dense: few edges or many edges relative to nodes

Representation of Graphs:
1. Adjacency Matrix: 2D array VxV
   - Easy to check if edge exists
   - Takes O(V^2) space
   - Best for dense graphs
2. Adjacency List: Array/List of lists
   - Each vertex stores list of neighbors
   - Takes O(V + E) space
   - Best for sparse graphs
   - Can use vector<list<int>> or list<int>* dynamically
*/

class Graph {
    int V;              // Number of vertices
    list<int>* l;       // Dynamic array of doubly linked lists to store adjacency lists
                        // Why list? Doubly linked list allows efficient insertion/deletion
                        // Why dynamic array? V can be decided at runtime, not compile time

public:

    // Constructor
    Graph(int V) {
        this->V = V;
        /*
        Allocate memory dynamically:
        l = new list<int>[V] creates an array of V lists (adjacency lists)
        Each vertex has its own list of neighbors
        */
        l = new list<int>[V];
    }

    // Add an edge between vertex u and vertex v
    void addEdge(int u, int v) {
        l[u].push_back(v); // Add v to u's adjacency list
        l[v].push_back(u); // Add u to v's adjacency list (because undirected graph)
        /*
        For weighted graph: use pair<int,int> (neighbor, weight)
        Example: list<pair<int,int>> *l; l[u].push_back({v, weight});
        */
    }

    // Print the adjacency list of the graph
    void printAdjList() {
        for(int i = 0; i < V; i++) {
            cout << i << " : ";  // Print vertex number
            for(int neigh : l[i]) {  // Iterate over all neighbors of vertex i
                cout << neigh << " "; // Print each neighbor
            }
            cout << endl;
        }
    }

    /*
    Additional Methods we can implement using adjacency list:

    1. BFS (Breadth-First Search)
    2. DFS (Depth-First Search)
    3. Detect cycles
    4. Find shortest path (Dijkstra for weighted, BFS for unweighted)
    5. Check connectivity (connected components)
    6. Minimum Spanning Tree (Prim's or Kruskal's)
    */
};

int main() {
    Graph g(5); // Create a graph with 5 vertices (0 to 4)

    // Adding edges
    g.addEdge(0, 1); // Connect vertex 0 with vertex 1
    g.addEdge(1, 2); // Connect vertex 1 with vertex 2
    g.addEdge(1, 3); // Connect vertex 1 with vertex 3
    g.addEdge(2, 3); // Connect vertex 2 with vertex 3
    g.addEdge(2, 4); // Connect vertex 2 with vertex 4

    /*
    Diagram of the graph:

          0
          |
          1
         / \
        2---3
        |
        4

    Adjacency List Representation:
    0 : 1
    1 : 0 2 3
    2 : 1 3 4
    3 : 1 2
    4 : 2

    Explanation:
    - Vertex 0 connected to 1
    - Vertex 1 connected to 0, 2, 3
    - Vertex 2 connected to 1, 3, 4
    - Vertex 3 connected to 1, 2
    - Vertex 4 connected to 2

    Key Points:
    - Undirected graph: edges go both ways
    - Unweighted graph: no weights are stored
    - Efficient storage using adjacency list (O(V + E) space)
    - Using list allows fast insertions
    - Using dynamic array allows runtime flexibility for V
    */

    g.printAdjList(); // Print adjacency list of the graph

    return 0;
}
