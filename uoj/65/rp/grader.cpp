#include <iostream>
#include <algorithm>
#include <random>
#include <cstdio>

#include "rp.h"
using namespace std;

const int A[9] = {7, 9, 11, 16, 100, 2020, 2021, 114514, 1919810};

random_device rd;
default_random_engine rng(rd());
uniform_int_distribution<> int_dis(0, 8);

int main(){
    int res = (A[int_dis(rng)] == guess());
    cout << res << endl;
}