#include <iostream>
#include <vector>
#include <list>
#include <queue> // Required for BFS
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
    }

    // Print the adjacency list of the graph
    void printAdjList() {
        cout << "Adjacency List Representation of Graph:\n";
        for(int i = 0; i < V; i++) {
            cout << i << " : ";
            if(l[i].empty()) {
                cout << "(no connections)"; // Handle isolated nodes
            }
            for(int neigh : l[i]) {
                cout << neigh << " ";
            }
            cout << endl;
        }
    }

    /*
    BREADTH-FIRST SEARCH (BFS)

    - BFS is a graph traversal algorithm that explores vertices level by level.
      It visits all neighbors of a node before moving to the next level neighbors.
    - BFS uses a queue to maintain the order of traversal.
    - Characteristics:
        - Explores neighbors first, then neighbors of neighbors.
        - Time Complexity: O(V + E)
        - Space Complexity: O(V) for visited array + O(V) for queue in worst case
        - Works for both connected and disconnected graphs.
        - Commonly used in:
            - Finding shortest path in unweighted graphs
            - Checking connectivity
            - Level-order traversal in trees
            - Detecting bipartiteness
    */

    // BFS from a given source vertex
    void bfsHelper(int src, vector<bool>& vis) {
        queue<int> q;         // Queue for BFS
        q.push(src);          // Start BFS from source
        vis[src] = true;      // Mark source as visited

        cout << src << " ";   // Print the starting node

        while(!q.empty()) {
            int node = q.front(); // Get the front node
            q.pop();              // Remove it from queue

            // Visit all unvisited neighbors
            for(int neigh : l[node]) {
                if(!vis[neigh]) {
                    q.push(neigh);   // Add neighbor to queue
                    vis[neigh] = true; // Mark neighbor as visited
                    cout << neigh << " "; // Print neighbor immediately when visited
                }
            }
        }
    }

    // BFS that handles disconnected components automatically
    void bfs() {
        vector<bool> vis(V, false);  // Track visited nodes
        cout << "\nBFS Traversal (handling disconnected components): ";

        for(int i = 0; i < V; i++) {
            if(!vis[i]) {
                // If node is not visited, start BFS from this node
                bfsHelper(i, vis);
            }
        }

        cout << endl;
    }
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
    */

    g.printAdjList(); // Print adjacency list of the graph

    // Perform BFS traversal — will automatically detect multiple sources
    g.bfs();

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

    BFS Traversal (handling disconnected components): 0 1 2 3 4 5 6

    Explanation of BFS Traversal:
    - Start from 0 → visit neighbors 1 → visit neighbors of 1 → 2 and 3
    - All vertices of first component are visited (0,1,2,3)
    - Move to 4 (unvisited) → visit 5
    - Move to 6 (isolated) → visit it
    - BFS ensures all nodes are visited even if graph is disconnected.
    - The traversal visits nodes in levels:
        Level 0: 0
        Level 1: 1
        Level 2: 2, 3
        Level 3: 4, 5
        Level 4: 6 (isolated)
    */

    return 0;
}
