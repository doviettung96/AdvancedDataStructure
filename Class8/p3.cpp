#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

const int value_range = 10; // from 0 to range - 1
const long random_seed = 1;

class SquareMatrix{
private:
    int **elements;
    int N;
public:
    explicit SquareMatrix(int N) : N(N) {
        elements = new int* [N];
        for(int i = 0; i < N; ++i) elements[i] = new int [N];
    }
    SquareMatrix(const SquareMatrix &other): N(other.N) {
        elements = new int* [N];
        for(int i = 0; i < N; ++i){
            elements[i] = new int [N];
            for(int j = 0; j < N; ++j){
                elements[i][j] = other.elements[i][j];
            }
        }
    }
    ~SquareMatrix(){
        for(int i = 0; i < N; ++i) delete elements[i];
        delete[] elements;
    }
    void random_initialize()
    {
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                int random_value = 1 + rand() / ((RAND_MAX + 1u) / value_range);
                elements[i][j] = random_value;
            }
        }
    }

    void display() const{
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                cout << elements[i][j] << " ";
            }
            cout << endl;
        }
    }

    int* &operator[] (const int &index){
        return elements[index];
    }
    
    friend const SquareMatrix recursively_multiply( SquareMatrix &A,  SquareMatrix &B, int N);
    friend const SquareMatrix strassen( SquareMatrix &A,  SquareMatrix &B, int N);
};

const SquareMatrix recursively_multiply( SquareMatrix &A, SquareMatrix &B, int N){
    SquareMatrix C(N);
    if(N == 1){
        C[0][0] = A[0][0] * B[0][0];
    }else{
        int half = N / 2;
        SquareMatrix A11(half), A12(half), A21(half), A22(half);
        SquareMatrix B11(half), B12(half), B21(half), B22(half);

        for(int i = 0; i < half; ++i){
            for(int j = 0; j < half; ++j){
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + half];
                A21[i][j] = A[i + half][j];
                A22[i][j] = A[i + half][j + half];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + half];
                B21[i][j] = B[i + half][j];
                B22[i][j] = B[i + half][j + half];
            }
        }

        SquareMatrix C1 = recursively_multiply(A11, B11, half), 
                     C2 = recursively_multiply(A12, B21, half);
        SquareMatrix C3 = recursively_multiply(A11, B12, half), 
                     C4 = recursively_multiply(A12, B22, half);
        SquareMatrix C5 = recursively_multiply(A21, B11, half), 
                     C6 = recursively_multiply(A22, B21, half);
        SquareMatrix C7 = recursively_multiply(A21, B12, half), 
                     C8 = recursively_multiply(A22, B22, half);

        for(int i = 0; i < half; ++i){
            for(int j = 0; j < half; ++j){
                C[i][j] = C1[i][j] + C2[i][j];
                C[i][j + half] = C3[i][j] + C4[i][j];
                C[i + half][j] = C5[i][j] + C6[i][j];
                C[i + half][j + half] = C7[i][j] + C8[i][j];
            }
        }
    }
    return C;
}

const SquareMatrix strassen( SquareMatrix &A, SquareMatrix &B, int N){
    SquareMatrix C(N);
    if (N == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
    }
    else
    {
        int half = N / 2;
        SquareMatrix A11(half), A12(half), A21(half), A22(half);
        SquareMatrix B11(half), B12(half), B21(half), B22(half);

        for (int i = 0; i < half; ++i)
        {
            for (int j = 0; j < half; ++j)
            {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + half];
                A21[i][j] = A[i + half][j];
                A22[i][j] = A[i + half][j + half];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + half];
                B21[i][j] = B[i + half][j];
                B22[i][j] = B[i + half][j + half];
            }
        }
        SquareMatrix S1(half), S2(half), S3(half), S4(half), S5(half), S6(half), S7(half), S8(half), S9(half), S10(half);

        for(int i = 0; i < half; ++i){
            for(int j = 0; j < half; ++j){
                S1[i][j] = B12[i][j] - B22[i][j];
                S2[i][j] = A11[i][j] + A12[i][j];
                S3[i][j] = A21[i][j] + A22[i][j];
                S4[i][j] = B21[i][j] - B11[i][j];
                S5[i][j] = A11[i][j] + A22[i][j];
                S6[i][j] = B11[i][j] + B22[i][j];
                S7[i][j] = A12[i][j] - A22[i][j];
                S8[i][j] = B21[i][j] + B22[i][j];
                S9[i][j] = A11[i][j] - A21[i][j];
                S10[i][j] = B11[i][j] + B12[i][j];
            }
        }

        SquareMatrix P1 = strassen(A11, S1, half);
        SquareMatrix P2 = strassen(S2, B22, half);
        SquareMatrix P3 = strassen(S3, B11, half);
        SquareMatrix P4 = strassen(A22, S4, half);
        SquareMatrix P5 = strassen(S5, S6, half);
        SquareMatrix P6 = strassen(S7, S8, half);
        SquareMatrix P7 = strassen(S9, S10, half);

        for(int i = 0; i < half; ++i){
            for(int j = 0; j < half; ++j){
                C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
                C[i][j + half] = P1[i][j] + P2[i][j];
                C[i + half][j] = P3[i][j] + P4[i][j];
                C[i + half][j + half] = P1[i][j] + P5[i][j] - P3[i][j] - P7[i][j];
            }
        }
    }
    return C;
}

int main(){
    srand(random_seed);
    vector<int> test_cases = {32, 64, 128, 256, 512, 1024};
    
    for(auto N: test_cases){
        SquareMatrix A(N), B(N);
        A.random_initialize();
        B.random_initialize();
        
        cout << "N = " << N << endl;

        chrono::steady_clock::time_point begin, end;
        begin = chrono::steady_clock::now();
        SquareMatrix C = recursively_multiply(A, B, N);
        end = chrono::steady_clock::now();
        cout << "A.B recursive: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
   
        begin = chrono::steady_clock::now();
        SquareMatrix D = strassen(A, B, N);
        end = chrono::steady_clock::now();
        cout << "A.B strassen: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;

    }
}