// 
// Graph Definition:
//   A graph G is defined as a collection of a set V, of vectics (or nodes),
//   and a set E, of edges, then for a finite n, G = {V, E}, where
//   V = {V1, V2,...,Vn};  E = { Eij = (Vi, Vj), 1 <= i, j <= n }
//   - undirected edge: a connection between a apir of nodes (A, B).
//   - directed edge: from initial vertex A to terminal vertex B, <A, B>.
//   - digraph or network: a set of vertics and a set of directed edges.
//   - degree of a vertex (A) in undirected graph: 
//       deg(A) = the number of edges incident with the vertex A.
//   - in-degree of a vertex in directed graph:
//       deg(A) = the number of edges terminating at the vextex A.
//   - out-degree of a vertex in directed graph:
//       deg+(A) = the number of edges with A as their inital vertex.
//   - weighted graph: numeric values associate with each edge.
//   - connected graph: there is a path between any two vertices.
//   - path from the vertex A to the vertex B: 
//     p(A, B) is a sequence of one or more edges from A to B.
//   - a path of length m: A = V0, V1, ... , Vm = B
//
// Graph Structure:
//   a node or vectex in the graph structure may contain multiple 
//   predecessor as well as multiple successor nodes.
//
// Graph Representations:
//   - adjacency matrics
//   - adjacency lists
//   - adjacency multilists     // TBD
//
// Graph Traversals:
//   - Depth First Traversal
//   - Breadth First Traversal
//
// Topological Sort (Ordering)
//   - it is a linear ordering of vertices such that for every edge u->v
//     in a directed graph, the vertex u always comes before vertex v.
//   - Topo Sort only works for a directed acyclic graph (DAG),
//     acyclic graph has no cycle.
//   - DAG has at least one vertex with indegree  as 0.
//     DAG has at least one vertex with outdegree as 0. 
//
// Shortest Path
//   - single pair: from one node to another
//   - single source: from one node to all other nodes
//   - signle destination: from all nodes to one node
//   - all pairs: between every pairs
//
// Minimum Spanning Tree (MST)
//   a spinning tree of a graph is a subgraph that has all the vertices (n)
//   and some (n - 1) edges sufficient to build a tree.
//   + the minimum spanning tree has the minimum weight than all other
//     spanning trees of the same graph.
//   + a connected graph always has one or more spinning trees. 
//     a graph havin a spinning tree is connected.
//   + algorithms to find the minimum spinning tree of a graph:
//     - Prim Algorithm
//     - Kruskal Algorithm
//
// Detect Cycle in Undirected Graph
//   Methods:
//     - DFS
//     - BFS
//     - Disjoint Set
//     - Topological Sort
//     - Bellman Ford (Negative Cycle)
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <list>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

/* using an integer to present a vertex
 */
typedef  unsigned int   Vertex;
typedef  int            Weight;

/* a structure to represent a weighted edge in graph
 * + does not define the direction in this structure
 */
struct Edge { 
    Vertex  src;        // the source vertex of an edge in directed graph
    Vertex  dst;        // the destination vertext of an edge in directed graph
    Weight  weight;     // the cost from the source vertex to the destination vertext
    string  name;       // TBD

    Edge(Vertex s, Vertex d) : src(s), dst(d), weight(1), name("") { }
    Edge(Vertex s, Vertex d, Weight w) : src(s), dst(d), weight(w), name("") { }
    Edge(Vertex s, Vertex d, Weight w, string id) : src(s), dst(d), weight(w), name(id) { };

    bool equal_directed(Edge e) { return this->src == e.src && this->dst == e.dst; }
 
    bool equal_undirected(Edge e) { return (this->src == e.src && this->dst == e.dst) ||
                                           (this->src == e.dst && this->dst == e.src); }
    
    // void print_edge() { cout << "[" << src << ", " << dst << ", " << weight << ", " << name <<"]"; }
    void print_edge() { 
        cout << "[" << char(src) << ", " << char(dst) << ", " << weight <<"]"; }
};
/* a structure to represent a connected, directed and 
 * weighted graph.
 */
class Graph {
    bool  directed;             // directed graph, false by default
    bool  weighted;             // edges have weights (costs)
    vector<Vertex>  vertices;   // sorted dynamic list (vector)
    // vector<Edge>  edges;        // unsorted dynamic list (vector)

    bool  check_edges();
public:
    vector<list<Edge>> edge_lists;    // adjacent_list, unsorted, represents the graph

    // constructors
    Graph() : directed(false), weighted(false)  { edge_lists.clear(); }
    Graph(bool dt, bool wt) : directed(dt), weighted(wt)  { edge_lists.clear(); }

    bool  is_directed() { return directed; }
    bool  is_weighted() { return weighted; }
    int   number_vertices() { return vertices.size(); }
    int   number_edges();

    Vertex get_vertex(int index);
    int    get_index(Vertex v);
    int    add_vertex(Vertex v);
    void   del_vertex(int index);
    void   del_vertex(Vertex v) { del_vertex(get_index(v)); }
    bool   find_vertex(Vertex v) { return get_index(v) >= 0; }
    void   print_vertices();

    void  add_edge(Vertex s, Vertex d, Weight w);
    void  add_edge(Vertex s, Vertex d) { add_edge(s, d, 1); }
    void  add_edge(Edge e)  { add_edge(e.src, e.dst, e.weight); };
    void  del_edge(Vertex s, Vertex d);
    void  del_edge(Edge e);
    bool  equal_edge(Edge e1, Edge e2);

    void  print_graph();
    // void  create_directed_graph(list<Edge>& edges);
    // void  create_undirected_graph(list<Edge>& edges);

    int   algorithm_shortest_path(Vertex s, Vertex d, vector<Vertex>& path);
    void  algorithm_bellman_ford(Vertex start, int *distances);
    void  algorithm_mst_prim(Vertex v0, vector<Edge>& mst);
    void  topological_sort(vector<Vertex>& topo_sort);
    bool  detect_cycle_dfs(int vi, int pi, vector<int>& visited);
};

#define COST_MAX   (UINT_MAX >> 1)  // avoid overflow
#define NOT_VERTEX  '*'             // invalid vertex

/**********************************************************************
 * Graph::Vertex
 * + vertex is unique, the value is comparable, the same as an integer.
 */
int Graph::get_index(Vertex v)
{
    int nv = number_vertices();
    for (int i = 0; i < nv; ++i) {
        if (vertices[i] == v) {
            return i;
        }
    }
    return -1;
}
/* add_vertext()
 * add the vertex into the sorted list (vector).
 * add nothing if the vertex exists already.
 * return the index of the vertex.
 */
int Graph::add_vertex(Vertex v)
{
    vertices.push_back(v);
    return vertices.size() - 1;
}

void Graph::del_vertex(int index)
{
    if (index >= 0 && index < vertices.size()) {
        vertices.erase(vertices.begin() + index);
    }
}

Vertex Graph::get_vertex(int index)
{
    if (index >= 0 && index < vertices.size()) {
        return vertices[index];
    }
    return UINT_MAX;
}

void Graph::print_vertices()
{
    cout << "Vertices: ";
    int  nv = vertices.size();
    const int ww = log10(nv) + 2;
    for(int i = 0; i < nv; ++i) { 
        // if (i % 20 == 0) { cout << endl; } 
        cout.width(ww); cout << char(vertices[i]) << ", ";  
    } 
    cout << endl;
}

int Graph::number_edges()
{
    int num = 0;
    for (auto elist : edge_lists) {
        num += elist.size();
    }
    return is_directed() ? num : num >> 1;
}

bool Graph::equal_edge(Edge e1, Edge e2)
{
    return is_directed() ? e1.equal_directed(e2) : e1.equal_undirected(e2);
}
//
bool Graph::check_edges()
{
    int nv = number_vertices();

    for (int i = 0; i < nv; ++i) {
        Vertex v = vertices[i];
        for (Edge e : edge_lists[i]) {
            if (e.src != v) {

            }
        }
    }
}
//
void Graph::add_edge(Vertex s, Vertex d, Weight w)
{
    // if (!edge_lists.empty()) {
    //     for (auto elist : edge_lists) {
    //         for (auto e : elist) {
    //             cout << "[" << e.src << ", " << e.dst << "], ";
    //         }
    //         cout << endl;
    //     }
    // }
    if (find_vertex(s)) {
        int src_index = get_index(s); 
        // Edge *e = new Edge(s, d);
        // elist.push_back(*e);
        edge_lists[src_index].emplace_back(s, d, w);
    }
    else {
        int src_index = add_vertex(s);

        list<Edge> elist;
        elist.emplace_back(s,d, w);
        // edge_lists.emplace(edge_lists.begin() + src_index, s, d);
        edge_lists.insert(edge_lists.begin() + src_index, elist);
    }
    
    if ( !find_vertex(d) ) {
        int dst_index = add_vertex(d);
        list<Edge> elist;
        if ( !is_directed() ) {
            elist.emplace_back(d, s, w);
        }
        edge_lists.insert(edge_lists.begin() + dst_index, elist);
    }
    else if ( !is_directed() ) {
        int dst_index = get_index(d); 
        edge_lists[dst_index].emplace_back(d, s, w);
    }
    cout << "vertices: "; print_vertices(); 
    cout << char(s) << ": "; for (auto e : edge_lists[get_index(s)]) { e.print_edge(); }  cout << endl;
    cout << char(d) << ": "; for (auto e : edge_lists[get_index(d)]) { e.print_edge(); }  cout << endl;
    cout << "list size: " << edge_lists.size() << endl;
    print_graph();
}

void Graph::print_graph()
{
    int nv = edge_lists.size();
    int ne = number_edges();
    cout << "Edge (Adjacent) Lists: size = " << nv << " Edge [src, dst, weight <, name>]" << endl;
    for (int i = 0; i < nv; ++i) {
        cout.width(6); cout << i << ": ";
        for (Edge e: edge_lists[i]) {
            e.print_edge(); if ( !e.equal_directed(edge_lists[i].back()) ) { cout << ", "; }
        }
        cout << endl;
    }
}
/**********************************************************************
 * algorithm_shortest_path
 * + single source algorithm,
 *  
 * + the algorithm can be enhanced to check cyl
 * + time complexity: best O(E), worst O(VE)
 *   V = number of vertices; E = number of edges
 *   spce complexity: 
 */
int Graph::algorithm_shortest_path(Vertex s, Vertex d, vector<Vertex>& path)
{
    int  nv = number_vertices();

    vector<int>  distances(nv, COST_MAX);
    int si = get_index(s);
    distances[si] = 0;

    vector<Vertex> previous(nv, NOT_VERTEX);
    
    queue<int> Q;
    Q.push(si);

    vector<bool> visited(nv, false);
    visited[si] = true;

    int count[nv] = { 0 };

    // BFT
    while (!Q.empty()) {
        int vi = Q.front();
         Q.pop();
        // visited[vi] = false;

        for (Edge e : edge_lists[vi]) {
            int di = get_index(e.dst);
            if (distances[vi] + e.weight < distances[di]) {
                distances[di] = distances[vi] + e.weight;
                previous[di] = e.src;
                if (!visited[di]) {
                    Q.push(di);
                    visited[di] = true;
                    count[di]++;
                    // if (count[di] > nv) {
                        // return false;  // negative cycle
                        // return -1;
                    // }
                    // cout << "visit: " << char(e.dst) << endl;
                }
            }
            if (e.dst == d) {
                break;
            }
        }
        // cout << "dist " << vi << ": "; for (int i = 0; i < nv; ++i) { cout << distances[i] << ", "; } cout << endl;
        // cout << "prev " << vi << ": "; for (int i = 0; i < nv; ++i) { cout << char(previous[i]) << ", "; } cout << endl;
    }

    // obtain the shortest path (made up of vertices)
    int di = get_index(d);
    int vi = di;
    if (distances[vi] < COST_MAX) {
        Vertex v = get_vertex(vi);
        while (v != NOT_VERTEX) {
            path.push_back(v);
            // cout << vi << ": " << char(v) << ", ";
            if (v == s) {
                break;
            }
            v = previous[vi];
            if (v != NOT_VERTEX) {
                vi = get_index(v);
            }
        }
        reverse(path.begin(), path.end());
        // for (auto v : path) { cout << char(v) << ", "; }  cout << endl;
    }
    return  distances[di];
}
/**********************************************************************
 * Algorithm Bellman Ford: 
 * + sortest path for single source, dynamic programming
 * + works for the negtive weights, can be used to check the cycles.
 * 
 * - initialize distance
 * - go to the next vertex, not the neighbor vertex
 * - cannot break out when there is noing changed for every vertex.
 * 
 * + time complexity:  best O(E), average O(VE), worst O(VE)
 *   space complexity: O(V)
 *   V = number of vertices; E = number of edges
 * 
 * input:
 *   (Vertex)start - the start (source) vertex
 * return:
 *   (int*)distances - the shortest distances to other vertices.
 *                     the caller must allocate the memory of ditances[]
 */
void Graph::algorithm_bellman_ford(Vertex start, int *distances)
{
    int nv = number_vertices();
    // vector<Vertex> path(nv, -1);
  
    for (int i = 0; i < nv; i++) {
        distances[i] = COST_MAX;
    }
    int s = get_index(start);
    distances[s] = 0;
    
    // relax all vertices
    for (int i = 0; i < nv; ++i) {
        int vi = (i + s) % nv;
        for (Edge e : edge_lists[vi]) {
            int si = get_index(e.src);      // vi == si
            int di = get_index(e.dst);
            if (distances[si] != COST_MAX && distances[si] + e.weight < distances[di]) {
                distances[di] = distances[si] + e.weight;
                // path[di] = e.src; 
            }
        }
        cout << "dist " << vi << ": "; for (int i = 0; i < nv; ++i) { cout << distances[i] << ", "; } cout << endl;
        // cout << "path " << i << ": "; for (int i = 0; i < 7; ++i) { cout << path[i] << ", "; } cout << endl;
    }
  
    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there 
    // is a cycle. 
    for (int i = 0; i < nv; i++) { 
        for (Edge e : edge_lists[i]) { 
            int si = get_index(e.src); 
            int di = get_index(e.dst);
            int weight = e.weight;
            if (distances[si] != COST_MAX && distances[si] + weight < distances[di]) { 
                printf("Graph contains negative weight cycle");
                return; // If negative cycle is detected, simply return
            }
        } 
    }
}
/**********************************************************************
 * Kahn's Topological Sorting
 *   it is impossible if the grapg is not a directed acyclic graph (DAG)
 * algorithm:
 *   + compute indegree for every vertex
 *   + put all the vertices (indexes) with indegree as 0 in a queue
 *   + pop a vertex from the queue until queue is empty
 *     - decrease the indegree by 1 for the neighbor vertices
 *     - put the vertex into the queue if its indegree become 0
 *   + repeat the last step until the queue is empty
 *   *
 */
void Graph::topological_sort(vector<Vertex>& topo_sort)
{
    int nv = number_vertices();

    // calculate the indegrees for every vertex
    vector<int> indegrees(nv, 0);
    for (int i = 0; i < nv; i++) { 
        for (Edge e : edge_lists[i]) { 
            int di = get_index(e.dst);
            indegrees[di]++;
        }
    }
    cout << "indegrees: "; for (auto e : indegrees) { cout << e << ", "; }  cout << endl;
    
    // find vertices tht have no incoming edges
    queue<int> no_incoming;
    for (int i = 0; i < nv; i++) {
        if (indegrees[i] == 0) {
            no_incoming.push(i);
        }
    }

    while ( !no_incoming.empty() ) {
        int i = no_incoming.front();
        no_incoming.pop();
        Vertex v = get_vertex(i);
        topo_sort.push_back(v);
        for (auto e : edge_lists[i]) {
            int di = get_index(e.dst);
            indegrees[di]--;
            if (indegrees[di] == 0) {
                no_incoming.push(di);
            }
        }
    }
}
/**********************************************************************
 * Prim's Minimum Spanning Tree (Greedy Algorithm)
 * Algorithm:
 *   1. remove the self-loops and parallel edges
 *   2. choose a node as the root node
 *   3. select the outgoing edge with less weight
 *   4. 
 */
void Graph::algorithm_mst_prim(Vertex v0, vector<Edge>& mst)
{
    int nv = number_vertices();
    bool selected[nv] = { false };

/*
    // find the vertex having the minimum weight, should be done by min-heap
    int min_vertex_si, min_vertex_di;
    int min_weight = INT_MAX;
    for (int vi = 0; vi < nv; ++vi) {
        for (Edge e : edge_lists[vi]) {
            if (e.weight < min_weight) {
                min_weight = e.weight;
                min_vertex_si = vi;
                min_vertex_di = get_index(e.dst);
            }
        }
    }
    Vertex v0 = get_vertex(min_vertex_si);
    mst.push_back(v0);
    visited[min_vertex_si] = true;
    cout << "Min Vertex: " << char(v0) << " (" << min_vertex_si << ", " << min_vertex_di << ")" << endl;
*/
    int vi = get_index(v0);
    selected[vi] = true;
    vector<int> vertices; 
    vertices.push_back(vi);
    
    for (int edge_count = 0; edge_count < nv - 1; ++edge_count) {
        Edge min_edge(v0, NOT_VERTEX, INT_MAX);
        for (int vi : vertices) {
            for(Edge e : edge_lists[vi]) {
                int di = get_index(e.dst);
                if ( !selected[di] && e.weight < min_edge.weight) {
                    min_edge = e;
                }
            }
        }
        mst.push_back(min_edge);
        vi = get_index(min_edge.dst);
        vertices.push_back(vi);
        selected[vi] = true;
    }   
}
/**********************************************************************
 * Detect Cycle using DFS (or DFT)
 * 
 */
bool Graph::detect_cycle_dfs(int vi, int pi, vector<int>& visited)
{
    visited[vi] = true;
    cout << vi << "(" << char(get_vertex(vi)) << "), ";
    for (Edge e : edge_lists[vi]) {
        int di = get_index(e.dst);
        if (!visited[di]) {
            return detect_cycle_dfs(di, vi, visited);
        }
        else if (di != pi) {
            cout << di << "(" << char(get_vertex(di)) << ") = cycle ";
            return true;
        }
    }
    return false;
}
/**********************************************************************
 * Depth First Traversal (Search) - DFT/DFS
 * traverses the nodes in a depthward motion, then move backward to 
 * get the next node for traversal. it visits every node exactly once.
 * 
 * Backtracking means that when you are moving forward and there are 
 * no more nodes along the current path, you move backwards on the same 
 * path to find nodes to traverse.
 * 
 * the DFT assume every edge has the same cost (weight).
 * the DFT may not work when there is an undirected cycle.
 */
vector<vector<int>> adjacent_table
{
//   0  1  2  3  4  5  6        //
    {0, 0, 1, 1, 0, 0, 0},      //   0---2---1
    {0, 0, 1, 0, 0, 1, 0},      //   |  /|   |
    {1, 1, 0, 1, 1, 0, 0},      //   | / |   |
    {1, 0, 1, 0, 0, 0, 1},      //   3   4---5
    {0, 0, 1, 0, 0, 1, 0},      //    \     /
    {0, 1, 0, 0, 1, 0, 1},      //     \   /
    {0, 0, 0, 1, 0, 1, 0}       //       6
};
/* the DFS recursive implementation uses the idea of backtracking.
 * it is smilar to the preorder traversal of a binary tree.
 * it exhausts all the nodes by going ahead in the current path,
 * then move backward when no more unvisited nodes on the path.
 */
void graph_DFT_recursive(int v, vector<bool>& vertex_visited)
{
    if (vertex_visited[v]) {
        return;
    }
    vertex_visited[v] = true;
    cout << v << " ";
    for (int i = adjacent_table[v].size() - 1; i >= 0; --i) {
        if (adjacent_table[v][i]) {
            graph_DFT_recursive(i, vertex_visited);
        }
    }
}
/* the DFT iterative implemention uses a stack to backtrack the nodes.
 * + it goes forward (visit every node) along one path, 
 * + save (push into a stack) all the adjacent nodes of the nodes on 
 *   the path for backtracking.
 */
void graph_DFT_iterative(int v)
{
    vector<bool> vertices_visited(adjacent_table.size(), false);

    vertices_visited[v] = false; 
    stack<int> S;
    S.push(v);

    while (!S.empty()) 
    { 
        v = S.top(); 
        S.pop(); 
  
        if (!vertices_visited[v])
        { 
            cout << v << " "; 
            vertices_visited[v] = true; 
        } 
  
        for (int i = 0; i < adjacent_table[v].size(); ++i) {
            if (adjacent_table[v][i] && !vertices_visited[i]) {
                S.push(i);
            }
        }
    }
}
/**********************************************************************
 * Breadth First Traversal (Search)
 * explores the vertices in order of the distance from the source vertex,
 * where the distance is the minimum length (number of vertices) of the path
 * from the source vertex.
 * 
 * BFT works best when there is a concept of layers or levels in the graph.
 * BFT assume every edge has the same cost (weight).
 */
void graph_BFT_iterative(int v)
{
    vector<bool> vertices_visited(adjacent_table.size(), false);
  
    queue<int> Q;

    vertices_visited[v] = true; 
    Q.push(v);
  
    while (!Q.empty())
    { 
        v = Q.front(); 
        cout << v << " "; 
        Q.pop(); 
  
        for (int i = 0; i < adjacent_table[v].size(); ++i) 
        { 
            if ( adjacent_table[v][i] && !vertices_visited[i])
            { 
                vertices_visited[i] = true; 
                Q.push(i); 
            } 
        }
    } 
}
void graph_BFT_recursive(int v)
{

}
/**********************************************************************
 * Dijkstra Algorithm (single source shortest Path)
 *   find the sortest path (respect to the cost) from the start node 
 *   to every node in the graph.
 *   + greedy programming
 * Algorithm: 
 *   cost[][] is the same as G[][] except changing the 0 to COST_MAX.
 *   distance[] will include the results of all the nodes.
 *     initialize to COST_MAX except the starting node [0].
 *   pred[] remembers the previous node that leads to the shortest distance.
 *   the outside while loop make sure every node is visited.
 *   the first for loop finds the shortest path in unvisited nodes
 *   the second for loop does the relaxation, 
 *   Relaxation:
 * Note: writen in C.
 */
// #define COST_MAX   (UINT_MAX >> 1)  // avoid overflow

void graph_dijkstra_algorithm(vector<vector<unsigned int>>& g, 
                              unsigned int start,
                              vector<unsigned int>& distance)
{
    int sz = g.size();
    int i, j, next;
    unsigned int cost[sz][sz];
    // unsigned int pred[sz] = {start};
    bool visited[sz] = {false};

    // replace the 0 in g[][] with COST_MAX
    for (i = 0; i < sz; i++) {
        for (j = 0; j < sz; j++) {
            cost[i][j] = g[i][j] == 0 ? COST_MAX : g[i][j];
        }
    }

    for (i = 0; i < sz; i++) {
        distance[i] = cost[start][i];
    }
    // for (i = 0; i < sz; i++) { cout << distance[i] << " "; } cout << endl;

    distance[start] = 0;
    visited[start] = true;
    int count = 1;

    while (count < sz - 1) {
        unsigned long minDistance = COST_MAX;
        for (i = 0; i < sz; ++i) {
            if (distance[i] < minDistance && !visited[i]) {
                minDistance = distance[i];
                next = i;
            }
        }
        visited[next] = true;
        // cout << "next = " << next << ": ";
        // for (i = 0; i < sz; i++) { cout << distance[i] << " "; } cout << endl;
        for (i = 0; i < sz; ++i) {
            if (!visited[i]) {
                // cout << "min= " << minDistance << ", next= " << next << ", i= " << i << ", cost= " << cost[next][i] << ", ";
                if (minDistance + cost[next][i] < distance[i]) {
                    distance[i] = minDistance + cost[next][i];
                    // cout << "distance= " << distance[i];
                    // pred[i] = next;
                }
                // cout << endl;
            }
        }
        // cout << "count= " << count << ": ";
        // for (i = 0; i < sz; i++) { cout << distance[i] << " "; } cout << endl;
        // for (i = 0; i < sz; i++) { cout << pred[i] << " "; } cout << endl;
        ++count;
    }
    cout << "visited: ";  for (auto v : visited) { cout << v << ", "; }  cout << endl;
    cout << "distance from " << start << " to: ";
    for (i = 0; i < sz; ++i) {
        cout << distance[i] << ", ";
    }
    cout << endl;
}
/**********************************************************************
 * Kruskal's Spanning Tree Algorithm
 * algorithm:
 *   1. remove self circle and parallel edges.
 *   2. build and sort the edges according to their weights.
 *   3. treat each edge as a single node tree, 
 *      when the edge e.dst on a different tree (has a different tid),
 *      merge the trees by assign it with the same tree id (tid).
 *   4. go through the ordered edges from the begin to the end.
 * note:
 *   this impelemtation can be improved by using Disjoint Set Data Structure.
 */
void graph_kruskal_algorithm(vector<vector<unsigned int>>& g, 
                             vector<Edge>& mst)
{
    int sz = g.size();
    vector<Edge> edges;
    for (int u = 0; u < sz; u++) {
        for (int v = u; v < sz; v++) {
            if ( g[u][v] ) {
                Edge e(u, v, g[u][v]);
                if ( edges.empty() || edges.back().weight <= e.weight ) {
                    edges.push_back(e);
                }
                else { 
                    vector<Edge>::iterator it;
                    for (it = edges.begin(); it < edges.end(); it++) {
                        if ((*it).weight > e.weight) {
                            edges.insert(it, e);
                            break;
                        }
                    }
                }
            }
        }
    }
    // for (auto e : edges) {
    //     cout << e.src << "-" << e.dst << "." << e.weight << ", ";
    // }
    // cout << endl;

    vector<int> tid(sz);
    for (int i = 0; i < sz; ++i) {
        tid[i] = i;
    }

    for (Edge e : edges) {
        if (tid[e.src] != tid[e.dst]) {
            mst.push_back(e);
            int ts = tid[e.src], td = tid[e.dst];
            for (int i = 0; i < sz; ++i) {
                if (tid[i] == ts) {
                    tid[i] = td;
                }
            }
        }
    }
}

/* testing driver code
 */
//   A---C---B
//   |  /|   |
//   | / |   |
//   D   E---F
//    \     /
//     \   /
//       G
//
vector<vector<unsigned int>> G1 = { // adajenct matrix
//   0  1  2  3  4  5  6        //
    {0, 0, 1, 2, 0, 0, 0},      //   0---2---1
    {0, 0, 2, 0, 0, 3, 0},      //   |  /|   |
    {1, 2, 0, 1, 3, 0, 0},      //   | / |   |
    {2, 0, 1, 0, 0, 0, 1},      //   3   4---5
    {0, 0, 3, 0, 0, 2, 0},      //    \     /
    {0, 3, 0, 0, 2, 0, 1},      //     \   /
    {0, 0, 0, 1, 0, 1, 0}       //       6 
};
vector<vector<unsigned int>> G2 = {
//    0, 1, 2, 3, 4, 5, 6, 7, 8
    { 0, 4, 0, 0, 0, 0, 0, 8, 0  }, 
    { 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
    { 0, 8, 0, 7, 0, 4, 0, 0, 2  }, 
    { 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 
    { 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 
    { 0, 0, 4, 14, 10, 0, 2, 0, 0 }, 
    { 0, 0, 0, 0, 0, 2, 0, 1, 6  }, 
    { 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
    { 0, 0, 2, 0, 0, 0, 6, 7, 0  } 
};
//
Graph* graph_create_G1()
{
    Graph *g = new Graph();
    g->add_edge('A', 'C', 1);   //   A---C---B
    g->add_edge('A', 'D', 2);   //   |  /|   |
    g->add_edge('B', 'C', 2);   //   | / |   | 
    g->add_edge('B', 'F', 3);   //   D   E---F
    g->add_edge('C', 'D', 1);   //    \     /
    g->add_edge('C', 'E', 3);   //     \   /
    g->add_edge('D', 'G', 1);   //       G
    g->add_edge('E', 'F', 2);
    g->add_edge('F', 'G', 1);
    return g;
}
//
Graph* graph_create_G3()
{
    Graph *g = new Graph(true, false);
    g->add_edge('B', 'A');      // B-->A    //  B---->A
    g->add_edge('B', 'C');      // B-->C    //  |   / |
    g->add_edge('A', 'C');      // A-->C    //  v  /  v
    g->add_edge('A', 'D');      // A-->D    //  C<----D
    g->add_edge('D', 'C');      // D-->C    //   \    /
    g->add_edge('C', 'E');      // C-->E    //    \  /
    g->add_edge('D', 'E');      // D-->E    //     E
    // g->add_edge('E', 'D');      // E-->D    //     E
    return g;
}
//
void graph_display_distance(Graph *g, int *distances)
{
    int nv = g->number_vertices();
    int s;
    for (int i = 0; i < nv; ++i) { 
        if (distances[i] == 0) {
            s = i;
            break;
        }
    }
    Vertex start = g->get_vertex(s);

    cout << "distances from vertex ";
    cout << char(start) << "(" << s << "): ";
    for (int i = 0; i < nv; ++i) {
        distances[i] == COST_MAX ? cout << "-" : cout << distances[i];
        if (i < nv - 1) cout << ", ";
    }
    cout << endl;
}
//
void graph_display_path(Graph *g, vector<Vertex>& path)
{
    int n = path.size();
    if (n == 0) {
        return;
    }
    Vertex s = path[0];
    Vertex d = path[n - 1];

    cout << "path from vertex ";
    cout << char(s) << "(" << g->get_index(s) << ") to ";
    cout << char(d) << "(" << g->get_index(d) << "): ";
    for (Vertex v : path) {
        cout << char(v);
        if (v == d) break; else cout << "->";
    }
    cout << endl;
}
//
int main()
{
/*
    cout << "Depth First Traversal (recursive): " << endl;
    vector<bool> vertex_visited(adjacent_table.size(), false);
    for (int i = 0; i < adjacent_table.size(); ++i) {
        for (int i = 0; i < adjacent_table.size(); ++i) { vertex_visited[i] = false; }
        cout << i << ": ";  graph_DFT_recursive(i, vertex_visited);  cout << endl;
    }

    cout << "Depth First Traversal (iterative): " << endl;
    for (int i = 0; i < adjacent_table.size(); ++i) {
        cout << i << ": ";  graph_DFT_iterative(i);  cout << endl;
    }

    cout << "Breadth First Traversal (recursive): " << endl;
    for (int i = 0; i < adjacent_table.size(); ++i) {
        // cout << i << ": "; graph_BFT_recursive(i); cout << endl;
    }

    cout << "Breadth First Traversal (iterative): " << endl;
    for (int i = 0; i < adjacent_table.size(); ++i) {
        cout << i << ": "; graph_BFT_iterative(i); cout << endl;
    }

    cout << "Dijkstra Shortest Path G1: " << endl;
    vector<unsigned int> distances1(G1.size(), COST_MAX);
    graph_dijkstra_algorithm(G1, 0, distances1);

    cout << "Dijkstra Shortest Path G2: " << endl;
    vector<unsigned int> distances2(G2.size(), COST_MAX);
    graph_dijkstra_algorithm(G2, 0, distances2);

    cout << "Dijkstra Shortest Path from 0 to 6: " << endl;
    // vector<vector<unsigned int>> path;
    // graph_dijkstra_algorithm(G2, 0, 6, path);
*/
    Graph g;
    int n = 10;
    int w = log10(n) + 2;
    int B[n];
    for(int i = 0; i < n; ++i) { B[i] = rand() % (n * 10); }
    // cout << "B[" << k - min(8, n) << "] = ";
    for(int i = 0; i < n; ++i) { cout.width(w); cout << B[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Add Vertices: ";
    for (int i = 0; i < n; ++i) { g.add_vertex(B[i]); }
    // for (int i = 0; i < n; ++i) { cout << "[" << i << "]=" << g.vertices[i] << ", ";  }  cout << endl;
    g.print_vertices();

    cout << "find Vertex: ";
    n = g.number_vertices();
    for (int i = 0; i < n; ++i) {
        Vertex v = g.get_vertex(i);
        cout << g.find_vertex(v) << ", ";
    }
    cout << endl;

    Vertex v = B[n/2];
    cout << "Delete Vertex: " << v << ", index = " << g.find_vertex(v);
    n = g.number_vertices();
    for (int i = n - 1; i >= 0; --i) {
        v = g.get_vertex(i);
        g.del_vertex(v);
    }
    g.print_vertices();

    // Graph Class
    cout << "Create Undirected Graph: " << endl;
    Graph *g1 = graph_create_G1();
    // g1->print_vertices();
    g1->print_graph();

    int nv = g1->number_vertices();
    int distances[nv];
    vector<Vertex> path;
    
    cout << "Bellman Ford: " << endl;
    Vertex start = 'A';
    g1->algorithm_bellman_ford(start, distances);
    graph_display_distance(g1, distances);

    cout << "Shortest Path: " << endl;
    start = 'A';
    Vertex destination = 'G';
    int dist = g1->algorithm_shortest_path(start, destination, path);
    graph_display_path(g1, path);

    cout << "Create Directed Graph: " << endl;
    Graph *g3 = graph_create_G3();
    g3->print_graph();

    cout << "Topological Sort: " << endl;
    vector<Vertex> topo_sort;
    g3->topological_sort(topo_sort);
    if (topo_sort.size() != g3->number_vertices()) {
        cout << "Error: this graph has a cycle!" << endl;
    }
    else {
        for (auto e : topo_sort) { cout << char(e) << ", "; }  cout << endl;
    }

    cout << "Prim's Min Spinning Tree: " << endl;
    vector<Edge> mst;
    // g1->print_vertices();
    // g1->print_graph();
    for (int i = 0; i < g1->number_vertices(); ++i) {
        Vertex v0 = g1->get_vertex(i);
        cout << "Start from Vertex " << char(v0) << "(" << i << "): ";
        g1->algorithm_mst_prim(v0, mst);
        int cost = 0;
        for (auto e : mst) {
            cout << char(e.src) << "-" << char(e.dst) << "." << e.weight << ", ";
            cost += e.weight;
        }
        cout << "total_cost = " << cost << endl;
        mst.clear();
    }

    cout << "Kruskal's Min Spinning Tree: " << endl;
    graph_kruskal_algorithm(G1, mst);
    int cost = 0;
    for (auto e : mst) {
        cout << e.src << "-" << e.dst << "." << e.weight << ", ";
        cost += e.weight;
    }
    cout << "total_cost = " << cost << endl;

    cout << "Detect Cycle using DFS: " << endl;
    // g1->print_vertices();
    // g1->print_graph();
    int vn = g1->number_vertices();
    vector<int> visited(nv, false );
    if (g1->detect_cycle_dfs(0, -1, visited)) {
        cout << "Found cycle in the graph!" << endl;
    }
    else {
        cout << "No cycle in the graph." << endl;
    }

    delete g1;
    delete g3;
    return 0;
}
