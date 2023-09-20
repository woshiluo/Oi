// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/25 17:12
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int mod = 998244353;
const int N = 1100;

inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline int add( int a, int b ) { return ( a + b ) % mod; }

int n, m, x, y;
int f[N][N], sum[N];

