#include <iostream>
#include <stdexcept>

using namespace std;

#ifndef MAT3x3_H
#define MAT3x3_H

template<class T, int N>
class Mat3x3 {
	T entries[N][N];
public:
	Mat3x3() {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				entries[i][j] = (i == j) ? 1.0 : 0.0;
	}
	Mat3x3(T *coefficients) {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				entries[i][j] = coefficients[i * N + j];
	}

	template<class U, int M>
	Mat3x3<U, M>& operator= (const Mat3x3<U, M>& other) {
		if (this == &other) return *this;

		for (int i = 0; i < M; ++i)
			for (int j = 0; j < M; ++j)
				entries[i][j] = other.entries[i][j];
		return *this;
	}

	const Mat3x3 operator- () const {
		Mat3x3 res;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				res.entries[i][j] = -entries[i][j];
		return res;
	}
	Mat3x3& operator+= (const Mat3x3& other) {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				entries[i][j] += other.entries[i][j];
		return *this;
	}
	Mat3x3& operator-= (const Mat3x3& other) {
		*this += -other;
		return *this;
	}
	Mat3x3& operator*= (const Mat3x3& other) {
		Mat3x3 res;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) {
				res.entries[i][j] = 0.0;
				for (int k = 0; k < N; ++k)
					res.entries[i][j] += entries[i][k] * other.entries[k][j];
			}

		*this = res;
		return *this;
	}

	bool operator== (const Mat3x3& other) {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (entries[i][j] != other.entries[i][j])
					return false;
		return true;
	}
	T& operator() (int i, int j) {
		if (i >= N || i < 0 || j >= N || j < 0) throw invalid_argument("Index out of bound");
		return entries[i][j];
	}
	const T& operator() (int i, int j) const {
		if (i >= N || i < 0 || j >= N || j < 0) throw invalid_argument("Index out of bound");
		return entries[i][j];
	}

	template<class U, int M>
	friend const Mat3x3<U, M> operator+ (const Mat3x3<U, M>& A, const Mat3x3<U, M>& B);
	template<class U, int M>
	friend const Mat3x3<U, M> operator- (const Mat3x3<U, M>& A, const Mat3x3<U, M>& B);
	template<class U, int M>
	friend const Mat3x3<U, M> operator* (const Mat3x3<U, M>& A, const Mat3x3<U, M>& B);
	template<class U, int M>
	friend ostream& operator<< (ostream &os, const Mat3x3<U, M>& A);
};

template<class T, int N>
const Mat3x3<T, N> operator+ (const Mat3x3<T, N>& A, const Mat3x3<T, N>& B) {
	Mat3x3<T, N> res = A;
	res += B;
	return res;
}
template<class T, int N>
const Mat3x3<T, N> operator- (const Mat3x3<T, N>& A, const Mat3x3<T, N>& B) {
	Mat3x3<T, N> res = A;
	res -= B;
	return res;
}
template<class T, int N>
const Mat3x3<T, N> operator* (const Mat3x3<T, N>& A, const Mat3x3<T, N>& B) {
	Mat3x3<T, N> res = A;
	res *= B;
	return res;
}
template<class T, int N>
ostream& operator<< (ostream &os, const Mat3x3<T, N>& A) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			os << A.entries[i][j] << " ";
		os << endl;
	}
	return os;
}

#endif