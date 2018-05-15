#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main(){
	long long day = 86400000;
	long long n = day * 30;
	cout << n * n << " " << n << " " << sqrt(n) << " " <<  pow(n, 1.0 / 3) << " " << log2(n) << endl;
	return 0;
}