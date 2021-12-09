#include <iostream>
#include <algorithm>
#include <random>
#include <cstdio>
using namespace std;

int guess(){
	const int A[9] = {7, 9, 11, 16, 100, 2020, 2021, 114514, 1919810};

	random_device rd;
	default_random_engine rng(rd());
	uniform_int_distribution<> int_dis(0, 8);

	return A[int_dis(rng)];
}
