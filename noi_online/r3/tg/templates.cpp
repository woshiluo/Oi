#include <cstdio>
#include <cstring>

#include <algorithm>

template<class T>
void aabs( T &a ) { return a < 0? -a: a; }
template<class T>
T Min( T a, T b ) { return a < b? a: b; }
template<class T>
T Max( T a, T b ) { return a < b? a: b; }
template<class T>
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T>
void chk_Max( T &a, T b ) { if( a < b ) a = b; }
