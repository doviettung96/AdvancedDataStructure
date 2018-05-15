#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

const float INFINITY = numeric_limits<float>::max();

vector<vector<float>> apsp_floyd(vector<vector<float>> W){
	vector<vector<float>> D = W;
	int n = W.size();

	for(int k = 0; k < n; ++k){
		vector<vector<float>> next_D = D;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				next_D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
			}
		}
		D = next_D;
	}
	return D;	
}

void displayGraph(vector<vector<float>> G){
	int n = G.size();
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j)
			cout << G[i][j] << " ";
		cout << endl;
	}
}

int main(){
	vector<vector<float>> W;
	int n;
	cin >> n;
	for(int i = 0; i < n; ++i){
		vector<float> row;
		for(int j = 0; j < n; ++j){
			string cell_str;
			cin >> cell_str;
			float cell_value;
			if(cell_str == "INF") cell_value = INFINITY;
			else {
				stringstream cell_ss;
				cell_ss << cell_str;
				cell_ss >> cell_value;
			}

			row.push_back(cell_value);
		}
		W.push_back(row);
	}

	vector<vector<float>> D = apsp_floyd(W);
	cout << "All pairs shortest path: " << endl;
	displayGraph(D);
}