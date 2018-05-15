#include <iostream>
#include <vector>

using namespace std;

const long random_seed = 1;
const int value_range = 10; // from 0 to range - 1

vector<vector<int>> random_initialize(int N)
{
    vector<vector<int>> res;
    for (int i = 0; i < N; ++i)
    {
        vector<int> row;
        for (int j = 0; j < N; ++j)
        {
            int random_value = 1 + rand() / ((RAND_MAX + 1u) / value_range);
            row.push_back(random_value);
        }
        res.push_back(row);
    }
}

vector<vector<int>> partition_matrix(const vector<vector<int>> &A, int begin_i, int begin_j, int length){
    vector<vector<int>> res;
    for(int i = 0; i < length; ++i){
        vector<int> row;
        for(int j = 0; j < length; ++j){
            row.push_back(A[i][j]);
        }
        res.push_back(row);
    }
    return res;
}

vector<vector<int>> recursive_multiply(const vector<vector<int>> &A, const vector<vector<int>> &B){
    int N = A.size();
    vector<vector<int>> C(N);
    if(N == 1){
        C[0][0] = A[0][0] * B[0][0];
    }else{
        int half = N / 2;
        vector<vector<int>> A11 = partition_matrix(A, 0, 0, half);
        vector<vector<int>> A12 = partition_matrix(A, 0, half, half);
        vector<vector<int>> A21 = partition_matrix(A, half, 0, half);
        vector<vector<int>> A22 = partition_matrix(A, half, half, half);

        vector<vector<int>> B11 = partition_matrix(B, 0, 0, half);
        vector<vector<int>> B12 = partition_matrix(B, 0, half, half);
        vector<vector<int>> B21 = partition_matrix(B, half, 0, half);
        vector<vector<int>> B22 = partition_matrix(B, half, half, half);

        vector<vector<int>> C11 = recursive_multiply()
    }
}