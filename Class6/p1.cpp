#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void displayGraph(vector<vector<int>> G){
	int n = G.size();
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j)
			cout << G[i][j] << " ";
		cout << endl;
	}
}

vector<vector<int>> warshall(vector<vector<int>> G){
	int n = G.size();
	vector<vector<int>> T = G;

	for(int k = 0; k < n; ++k){
		vector<vector<int>> next_T = T;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j){
				next_T[i][j] = T[i][j] | (T[i][k] & T[k][j]);
			}
		T = next_T;	
	}
	return T;
}

int main(){
	vector<vector<int>> G;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i){
		vector<int> row;
		for(int j = 0; j < n; ++j){
			int cell;
			cin >> cell;
			row.push_back(cell);
		}
		G.push_back(row);
	}
	vector<vector<int>> T = warshall(G);

	cout << "The transitive closure of the above graph is: " << endl;
	displayGraph(T);

}