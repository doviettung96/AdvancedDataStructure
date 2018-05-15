/*
Author: Do Viet Tung
ID: s1232004
- Run/ Compile:
g++ -std=c++11 -o test p2.cpp
./test
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct subset_t{
	int rank;
	int parent;
};


int find(subset_t subsets[], int i){
	if(subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);
	return subsets[i].parent;
}

void Union(subset_t subsets[], int i, int j){
	int root_of_i = find(subsets, i);
	int root_of_j = find(subsets, j);

	if(subsets[root_of_i].rank < subsets[root_of_j].rank)
		subsets[root_of_i].parent = root_of_j;
	else if(subsets[root_of_i].rank > subsets[root_of_j].rank)
		subsets[root_of_j].parent = root_of_i;
	else{
		subsets[root_of_i].parent = root_of_j;
		subsets[root_of_j].rank++;
	}
}

struct edge_t{
	int src;
	int dest;
	float weight;
	edge_t(int src, int dest, float weight): src(src), dest(dest), weight(weight) {}
	void display(){
		cout << src << " " << dest << " " << weight << endl;
	}
};

struct graph_t{
	int V;
	int E;
	vector<edge_t> edges;
	graph_t(int V, int E): V(V), E(E) {}

	vector<edge_t> kruskal(){
		// create the subset for union-find
		subset_t subsets[V];
		for(int i = 0; i < V; ++i){
			subsets[i] = {0, i};
		}

		// sort a copy of the edges in the non-decreasing order
		vector<edge_t> copy_of_edges(edges);
		sort(copy_of_edges.begin(), copy_of_edges.end(), [](edge_t u, edge_t v) { return u.weight <= v.weight; });

		// add an edge to the minimum spanning tree, if it forms a cycle, then don't
		vector<edge_t> mst;
		for(auto edge: copy_of_edges){
			int root_of_src = find(subsets, edge.src);
			int root_of_dest = find(subsets, edge.dest);
			if(root_of_src != root_of_dest){
				mst.push_back(edge);
				Union(subsets, root_of_src, root_of_dest);
			}
		}

		return mst;
	}		
};


int main(){
	int V, E;
	cin >> V >> E;
	graph_t g(V, E);
	for(int i = 0; i < E; ++i){
		int src, dest;
		float weight;
		cin >> src >> dest >> weight;
		g.edges.push_back({src, dest, weight});
	}

	vector<edge_t> mst = g.kruskal();
	cout << "Minimum spanning tree" << endl;
	for(auto edge: mst){
		edge.display();
	}
}