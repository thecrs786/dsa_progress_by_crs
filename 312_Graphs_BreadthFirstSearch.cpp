#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;

/*

BFS -> Breadth-First Search:
- BFS is a graph traversal algorithm.
- It explores vertices in the order of their distance from the starting node (level by level).
- Immediate neighbors of a node are visited before moving to the next level neighbors.
- BFS is widely used in:
    - Finding shortest paths in unweighted graphs
    - Checking connectivity
    - Level-order traversal in trees
    - Finding connected components
    - Solving puzzles (e.g., shortest moves in a maze)

Characteristics of BFS:
- Uses a queue to maintain order of nodes to visit.
- Uses a visited array/vector to avoid revisiting nodes.
- Explores all nodes at distance d before nodes at distance d+1.
- Can be adapted for both directed and undirected graphs.

Time Complexity (TC):
- O(V + E) for adjacency list
- V = number of vertices, E = number of edges
- Each vertex is enqueued and dequeued at most once, and each edge is explored once.

Memory Complexity (MC):
- O(V) for visited array
- O(V) for queue in worst case (all vertices in queue)
- So overall O(V + E) for adjacency list storage

Relation to Trees:
- BFS on a graph is equivalent to **level-order traversal in trees**
- In trees, BFS visits nodes level by level using a queue
- Graph BFS handles cycles and disconnected graphs with visited array

*/

class Graph {
    int V;              // Number of vertices
    list<int>* l;       // Dynamic array of adjacency lists

public:

    // Constructor
    Graph(int V) {
        this->V = V;
        l = new list<int>[V]; // Create V lists for adjacency
    }

    // Add an undirected edge between u and v
    void addEdge(int u, int v) {
        l[u].push_back(v); // Add v to u's adjacency list
        l[v].push_back(u); // Add u to v's adjacency list (undirected)
    }

    // BFS Traversal from vertex 0
    void BFS() {
        queue<int> q;               // Queue to process nodes level by level
        vector<bool> vis(V, false); // Visited array to avoid revisiting nodes

        q.push(0);      // Start BFS from vertex 0
        vis[0] = true;  // Mark starting node as visited

        while (!q.empty()) {         // Process until all reachable nodes are visited
            int u = q.front();       // Get the front node from queue
            q.pop();                 // Remove it from queue
            cout << u << " ";        // Process node (here, printing)

            // Visit all neighbors of u
            for (int v : l[u]) {     
                if (!vis[v]) {      // If neighbor not visited
                    vis[v] = true;  // Mark neighbor as visited
                    q.push(v);      // Enqueue neighbor for later processing
                }
            }
        }
    }

    /*
    How BFS works on example graph:

    Graph:
          0
          |
          1
         / \
        2---3
        |
        4

    Step by step BFS traversal starting from 0:
    - Start at 0: visit 0
        Queue: [0] -> pop 0 -> visit neighbors [1]
        Queue: [1]
    - Visit 1: visit 1
        Queue: [1] -> pop 1 -> visit neighbors [0,2,3], 0 already visited
        Queue: [2,3]
    - Visit 2: visit 2
        Queue: [2,3] -> pop 2 -> visit neighbors [1,3,4], 1 and 3 already visited
        Queue: [3,4]
    - Visit 3: visit 3
        Queue: [3,4] -> pop 3 -> neighbors [1,2] already visited
        Queue: [4]
    - Visit 4: visit 4
        Queue: [4] -> pop 4 -> neighbors [2] already visited
        Queue: []
    Final BFS order: 0 1 2 3 4

    Note: BFS guarantees **shortest path in unweighted graphs** from source.
    */

    // BFS traversal from any given source
    void BFS_from(int src) {
        queue<int> q;
        vector<bool> vis(V, false);

        q.push(src);      // Start from given source
        vis[src] = true;

        while (!q.empty()) {
            int u = q.front(); 
            q.pop();
            cout << u << " ";

            for (int v : l[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
};
/*
        WARNING:

        
NOTE ON VISITED ARRAY WHILE PRINTING ADJACENCY LIST:

1. When we print an adjacency list, we are NOT traversing the graph.
   - We are just iterating over each vertex's neighbors.
   - No recursion or queue is used, so cycles cannot cause infinite loops.
   - Therefore, marking nodes as visited while printing is unnecessary.

2. What can go wrong if we mark nodes as visited while printing:
   - If we later perform BFS or DFS on the same graph using the same visited array,
     some nodes may already appear as visited.
   - This will cause the traversal to skip those nodes.
   - Result: BFS/DFS traversal may become incomplete.

Example:

Graph g(3);
g.addEdge(0, 1);
g.addEdge(1, 2);

vector<bool> vis(3, false);

for (int i = 0; i < 3; i++) {
    for (int neigh : g.l[i]) {
        vis[neigh] = true; // WRONG: marking visited while printing
        cout << neigh << " ";
    }
}

// Later, BFS starting from vertex 0
g.BFS(); 
// Node 1 is already marked visited from printing
// BFS will skip it
// Output will be incomplete, not visiting all nodes

3. Key takeaway:
- Printing adjacency lists: NO visited array required.
- BFS/DFS traversals: visited array is REQUIRED to avoid infinite loops due to cycles.
- Mixing the two can silently break traversal algorithms.

*/
int main() {
    // Example 1: Original graph
    Graph g1(5);

    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(2, 4);

    cout << "BFS traversal starting from vertex 0 (Example 1): ";
    g1.BFS();
    cout << endl;

    // Example 2: Slightly disconnected graph
    Graph g2(6);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(3, 4);
    g2.addEdge(4, 5);

    cout << "BFS traversal starting from vertex 0 (Example 2): ";
    g2.BFS_from(0); // BFS only covers connected component containing 0
    cout << endl;

    cout << "BFS traversal starting from vertex 3 (Example 2): ";
    g2.BFS_from(3); // BFS for disconnected component
    cout << endl;

    return 0;
}

/*
Key Notes:
- BFS uses queue to maintain **level order**.
- Visited array prevents cycles from infinite loops.
- BFS on graphs is the **generalization of level-order traversal in trees**.
- Examples show BFS in connected and disconnected graphs.
- Time Complexity: O(V + E)
- Memory Complexity: O(V + E) (adjacency list + queue + visited array)
*/
