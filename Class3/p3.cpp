/*
- Author: Do Viet Tung
- Id: s1232004
- Compile/ Run instructions:
g++ -std=c++11 -o test p3.cpp
./test
- Test case: (vertex starts from 0)
6
2 1 3
1 4
2 4 5
1 1
1 3
1 5

*/

#include <iostream>
#include <vector>

using namespace std;

struct vertex_t {
	int discover_time;
	int finish_time;
	vertex_t() : discover_time(0), finish_time(0) {}
};

class Graph {
private:
	vector<vertex_t> vertex_list;
	vector<vector<int>> adjacent_list;
	int time;
public:
	Graph(vector<vector<int>> adjacent_list) {
		vertex_list = vector<vertex_t> (adjacent_list.size());
		for (int i = 0; i < adjacent_list.size(); ++i) {
			this->adjacent_list.push_back(adjacent_list[i]);
		}
	}
	void dfs() {
		time = 0;
		bool visited[vertex_list.size()];
		for (int i = 0; i < vertex_list.size(); ++i) visited[i] = false;
		for (int i = 0; i < vertex_list.size(); ++i) {
			if (!visited[i])
				visit(visited, i);
		}
		cout << endl;
	}

	void visit(bool visited[], int source) {
		vertex_list[source].discover_time = ++time;
		visited[source] = true;
		cout << source << " ";
		for (auto adjacent_vertex : adjacent_list[source]) {
			if (!visited[adjacent_vertex]) {
				visit(visited, adjacent_vertex);
			}
		}
		vertex_list[source].finish_time = ++time;
	}

	void display_vertex_list() {
		cout << "Display vertex list infomation" << endl;
		for (int i = 0; i < vertex_list.size(); ++i) {
			cout << i << ": " << vertex_list[i].discover_time << " " << vertex_list[i].finish_time << endl;
		}
	}

	void display_adjacent_list(){
		cout << "Display adjacent_list infomation" << endl;
		for (int i = 0; i < adjacent_list.size(); ++i) {
			cout << i + 1 << ": ";
			for(auto j : adjacent_list[i]){
				cout << j + 1 << " ";
			}
			cout << endl;
		}
	}
};

int main() {
	vector<vector<int>> adjacent_list;
	int number_of_vertices;
	cin >> number_of_vertices;
	for (int i = 0; i < number_of_vertices; ++i) {
		int number_of_edges;
		cin >> number_of_edges;
		vector<int> adjacent_vertices;
		for (int j = 0; j < number_of_edges; ++j) {
			int incident_vertex;
			cin >> incident_vertex;
			adjacent_vertices.push_back(incident_vertex);
		}
		adjacent_list.push_back(adjacent_vertices);
	}

	Graph g(adjacent_list);
	// g.display_adjacent_list();
	g.dfs();
	g.display_vertex_list();
}
