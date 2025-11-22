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
        cout << "Adjacency List Representation of Graph:\n";
        for(int i = 0; i < V; i++) {
            cout << i << " : ";  // Print vertex number
            if(l[i].empty()) {
                cout << "(no connections)"; // Handle isolated nodes
            }
            for(int neigh : l[i]) {  // Iterate over all neighbors of vertex i
                cout << neigh << " "; // Print each neighbor
            }
            cout << endl;
        }
    }

    /*
    DEPTH-FIRST SEARCH (DFS) — Recursive approach

    - DFS is a graph traversal algorithm that explores as far as possible
      along each branch before backtracking.
    - It uses recursion or an explicit stack to go deep into the graph.
    - It’s similar to preorder traversal in trees.

    Characteristics:
    - Traverses deeper before moving to next sibling node.
    - Time Complexity: O(V + E)
    - Space Complexity: O(V) for recursion stack
    - Works for both connected and disconnected graphs.
    - Commonly used in:
        - Detecting cycles
        - Topological sorting
        - Finding connected components
        - Solving path and maze problems
    */

    // Helper function for DFS traversal from a given source
    void dfsHelper(int src, vector<bool>& vis) {
        vis[src] = true;              // Mark the current node as visited
        cout << src << " ";           // Print the current node

        // Visit all unvisited neighbors recursively
        for(int neigh : l[src]) {
            if(!vis[neigh]) {
                dfsHelper(neigh, vis);
            }
        }
    }

    // DFS function that handles disconnected components automatically
    void dfs() {
        vector<bool> vis(V, false);   // Track visited nodes
        cout << "\nDFS Traversal (handling disconnected components): ";

        for(int i = 0; i < V; i++) {
            if(!vis[i]) {
                // If the node is not visited, start DFS from that node
                dfsHelper(i, vis);
            }
        }

        cout << endl;
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
    Graph g(7); // Create a graph with 7 vertices (0 to 6)

    // Adding edges for first connected component (main graph)
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    // Second connected component: 4 linked with 5
    g.addEdge(4, 5);

    // Third component: vertex 6 is completely isolated (no edges)

    /*
    Diagram of the graph:

          0
          |
          1
         / \
        2---3         4---5        6

    Adjacency List Representation:
    0 : 1
    1 : 0 2 3
    2 : 1 3
    3 : 1 2
    4 : 5
    5 : 4
    6 : (no connections)

    Explanation:
    - Vertices 0–3 form the first connected component
    - Vertices 4–5 form the second connected component
    - Vertex 6 is an isolated node (third component)
    - DFS will automatically traverse all components because we loop over all vertices
      and start DFS on any vertex not yet visited.
    */

    g.printAdjList(); // Print adjacency list of the graph

    // Perform DFS traversal — it will automatically detect multiple sources
    g.dfs();

    /*
    OUTPUT:

    Adjacency List Representation of Graph:
    0 : 1
    1 : 0 2 3
    2 : 1 3
    3 : 1 2
    4 : 5
    5 : 4
    6 : (no connections)

    DFS Traversal (handling disconnected components): 0 1 2 3 4 5 6

    Explanation of DFS Traversal:
    - Starts from 0 → goes deep into 1 → 2 → 3 → then backtracks
    - Moves to 4 (since it’s unvisited) → visits 5 → backtracks
    - Moves to 6 (isolated) → visits it
    - This ensures all nodes are covered even if graph is disconnected.
    */

    return 0;
}
