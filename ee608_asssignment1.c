// ECE_608_Assignment_1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Vertex {
        public:
                Vertex(int v) : val(v), label(-1) {}
                int get_val();
                void set_label(int c_l);
                int get_label();
                vector<Vertex *> get_neighbors();
                vector<Vertex *> get_parents();
                void add_to_neighbors(Vertex *v);
                void add_to_parents(Vertex *v);

        private:
                int val; //value
                int label; //level of BFS traversal 
                vector<Vertex *> neighbors; //adjacent vertices
                vector<Vertex *> parents; //parents during BFS traversal
};
        
int Vertex::get_val() {
        return val;
}

void Vertex::set_label(int c_l) {
        label = c_l;
}

int Vertex::get_label() {
        return label;
}

vector<Vertex *> Vertex::get_neighbors() {
        return neighbors;
}

vector<Vertex *> Vertex::get_parents() {
        return parents;
}

void Vertex::add_to_neighbors(Vertex *v) {
        neighbors.push_back(v);
}

void Vertex::add_to_parents(Vertex *v) {
        parents.push_back(v);
}

struct Edge {
        public:
                Edge(Vertex *vto, Vertex *vtt) : vertex_one(vto), vertex_two(vtt) {}

        private:
                Vertex *vertex_one; //a linked vertex at one side
                Vertex *vertex_two; //another vertex at another side
};

class Graph {
    public:
                Graph(int n); //constructor
                void add_edge(int start_idx, int end_idx);
        vector<Vertex *> get_vertices();
        vector<Edge *> get_edges();
                
    private:
        vector<Vertex *> vertices; //an array of vertices
        vector<Edge *> edges; //an array of edges
                int num_vertices; //number of vertices
};

Graph::Graph(int n) {
        for(int i = 0; i < n; i++) {
                vertices.push_back(new Vertex));
        }
}

void Graph::add_edge(int start_idx, int end_idx) {
        Edge *c_e = new Edge(vertices[start_idx], vertices[end_idx]);
        edges.push_back(c_e);
        
        vertices[start_idx]->add_to_neighbors(vertices[end_idx]);
        vertices[end_idx]->add_to_neighbors(vertices[start_idx]);
}

vector<Vertex *> Graph::get_vertices() {
        return vertices;
}

vector<Edge *> Graph::get_edges() {
        return edges;
}

void find_all_shortest_paths(Vertex *s, Vertex *v, int c_rem_len, vector<vector<int>> &paths, vector<int> &path) {
        if(c_rem_len < 0) return;
        
        if(c_rem_len == 0 && v == s) {
                paths.push_back(path);
                reverse(paths.back().begin() + 1, paths.back().end());

                return;
        }

        path.push_back(v->get_val());

        for(int i = 0; i < v->get_parents().size(); i++) {
                find_all_shortest_paths(s, v->get_parents()[i], c_rem_len - 1, paths, path);
        }

        path.pop_back();
}

//return number of shortest paths from start vertex, s and end vertex, v
int bfs(Graph *g, int start_idx, int end_idx) {
        if(!g) throw invalid_argument("ERROR: Invalid Graph Input");         

        int ans = 0;
        vector<Vertex *> vertices = g->get_vertices();
        
        //exception handling for invalid start index and/or end index
        if(start_idx < 0 || start_idx >= vertices.size() || end_idx < 0 || end_idx >= vertices.size()) {
                throw invalid_argument("ERROR: Invalid Start Index and/or End Index Input(s)");        
        }
        
        queue<Vertex *> q; //queue for BFS traversal

        //first, identify s and v
        Vertex *s = g->get_vertices()[start_idx], *v = g->get_vertices()[end_idx];

        //if the start vertex is the end vertex, return 0
        if(s == v) {
                cout << "Start vertex is the same as end vertex" << endl;
                return 0;
        }

        s->set_label(0);
        q.push(s);

        while(!q.empty()) {
                Vertex *c_v = q.front();
                q.pop();
                
                //stop traversing when the end vertex has been found
                if(c_v == v) break;

                for(Vertex *c_neigh : c_v->get_neighbors()) {
                        if(c_neigh->get_label() == -1) { //the vertex has not been visited yet
                                c_neigh->set_label(c_v->get_label() + 1);
                                q.push(c_neigh);
                        }

                        c_neigh->add_to_parents(c_v);

                        if(c_neigh == v) {
                                ans += c_v->get_parents().size();
                        }

                }
        }

        //end vertex's label indicates shortest path length to reach it from start vertex
        cout << "Shortest path length: " << v->get_label() << endl;
        
        /*
        //find all the shortest paths
        vector<vector<int>> paths; //all the shortest paths
        vector<int> path; //current path

        path.push_back(s->get_val());

        find_all_shortest_paths(s, v, v->get_label(), paths, path);

        for(int i = 0; i < paths.size(); i++) {
                cout << "Path " << (i + 1) << ": ";
                
                for(int j = 0; j < paths[i].size(); j++) {
                        cout << paths[i][j];
                        
                        if(j != paths[i].size() - 1) cout << " -> ";
                }

                cout << endl;
        }
        */

        return ans;
}

int main()
{
    //create a new graph
    Graph *g = new Graph(8);
    
        g->add_edge(0, 1);
    g->add_edge(0, 2);
    g->add_edge(0, 3);
    g->add_edge(0, 4);
        g->add_edge(1, 4);
        g->add_edge(1, 5);
        g->add_edge(2, 4);
        g->add_edge(2, 6);
        g->add_edge(3, 6);
        g->add_edge(4, 6);
        g->add_edge(5, 7);
        g->add_edge(6, 7);

        //test case #1
        int start_idx = 2, end_idx = 5;
        cout << "There are " << bfs(g, start_idx, end_idx) << " path(s) in the graph from vertex " << start_idx << " to vertex " << end_idx;

        getchar();

        return 0;
}





int _tmain(int argc, _TCHAR* argv[])
{
        return 0;
}
