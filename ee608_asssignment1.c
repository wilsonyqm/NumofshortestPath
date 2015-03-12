#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <stdexcept>
#include <algorithm>

using namespace std;

struct Vertex {
        public:
                Vertex(int v) : val(v), label(-1), sp(0) {}
                int get_val();
                void set_label(int c_l);
                int get_label();
                void set_sp(int c_sp);
                int get_sp();
                void clear_parents();
		vector<Vertex *> get_neighbors();
                vector<Vertex *> get_parents();
                void add_to_neighbors(Vertex *v);
                void add_to_parents(Vertex *v);
        private:
                int val; //value
                int label; //level of BFS traversal
                int sp; //number of shortest path
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

void Vertex::set_sp(int c_sp) {
	sp = c_sp;
}

int Vertex::get_sp() {
	return sp;	
}

vector<Vertex *> Vertex::get_neighbors() {
        return neighbors;
}

vector<Vertex *> Vertex::get_parents() {
        return parents;
}

void Vertex::clear_parents() {
	parents.clear();
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
	void clear_graph(int s);
                
    private:
        vector<Vertex *> vertices; //an array of vertices
        vector<Edge *> edges; //an array of edges
                int num_vertices; //number of vertices
};

Graph::Graph(int n) {
        for(int i = 0; i < n; i++) {
                vertices.push_back(new Vertex(i));
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

void find_all_shortest_paths(Vertex *s, Vertex *v, vector<vector<int> > &paths, vector<int> &path) {
        if(v == s) {
                
		paths.push_back(path);
                reverse(paths.back().begin() + 1, paths.back().end());

                return;
        }

        path.push_back(v->get_val());

        for(int i = 0; i < v->get_parents().size(); i++) {
		cout<<"I am: " <<v->get_val()<<"Parents: "<<v->get_parents()[i]->get_val()<<'\n';
	           find_all_shortest_paths(s, v->get_parents()[i], paths, path);
        }
	
        path.pop_back();
}

void print_paths(Vertex *s, Vertex *v) {
	//find all the shortest paths
        vector<vector<int> > paths; //all the shortest paths
        vector<int> path; //current path

        path.push_back(s->get_val());

        find_all_shortest_paths(s, v, paths, path);

        for(int i = 0; i < paths.size(); i++) {
                cout << "Path " << (i + 1) << ": ";
                
                for(int j = 0; j < paths[i].size(); j++) {
                        cout << paths[i][j];
                        
                        if(j != paths[i].size() - 1) cout << " -> ";
                }

                cout << endl;
        }
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
        s->set_sp(1);
        q.push(s);
        while(!q.empty()) {
                Vertex *c_v = q.front();
                q.pop();
                
                //stop traversing when the end vertex has been found
                if(c_v == v) {
                	//end vertex's label indicates shortest path length to reach it from start vertex
        			cout << "Shortest path length: " << v->get_label() << endl;
        
        			print_paths(s, v);
        
                	return c_v->get_sp();
                }

                for(Vertex *c_neigh : c_v->get_neighbors()) {
                        if(c_neigh->get_label() == -1) { //the vertex has not been visited yet
                                c_neigh->set_label(c_v->get_label() + 1);
                                q.push(c_neigh);
                        }
                        
                        if(c_neigh->get_label() == c_v->get_label() + 1) {
                        	c_neigh->set_sp(c_neigh->get_sp() + c_v->get_sp());
                        	c_neigh->add_to_parents(c_v);
                        }
                }
        }
       
        

        return ans;
}

void Graph::clear_graph(int s) {
	for(int i = 0; i < vertices.size(); i++) {
		vertices[i]->set_label(-1);
		vertices[i]->set_sp(0);
		vertices[i]->clear_parents();	
	}

	vertices[s]->set_sp(1);
}

int main(int argc, const char * argv[])
{
    int i,j,nv,c=0;
    int k=0;
    double a;
    time_t t;
    srand ((unsigned) time(&t)  );
    nv=rand()%5+5;
    Graph *g = new Graph(nv);
    if(nv!=0){
    for(i=0;i<nv-1;i++){
        for(j=i+1;j<nv-1;j++){
            a=rand()/(double)RAND_MAX;
            //printf("%f\n", a);
            if(a>0.2 && i!=j){
        	g->add_edge(i, j);
		printf("Edge is from:%d to: %d\n", i, j);
                k=k+1;
            }
        }
    }
    }
    else {
        printf("Empty Graph!");
    }
    
    printf("%d\n", nv);
    printf("Total number of Vertex is: %d",k);

	    //create a new graph
           //test case #1

	for(int i = 0; i < 10; i++) {
        	int start_idx = (int)(rand() % nv), end_idx = (int)(rand() % nv);
		g->clear_graph(start_idx);
        	cout << "There are " << " path(s) in the graph from vertex " << start_idx << " to vertex " << end_idx;
        	cout << "There are " << bfs(g, start_idx, end_idx) << " path(s) in the graph from vertex " << start_idx << " to vertex " << end_idx;
		cout<<'\n';
		cout<<'\n';
	}

        return 0;
}
