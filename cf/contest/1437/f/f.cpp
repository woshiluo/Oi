// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/28 23:19:32 
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

const int N = 5e3 + 1e2;
const int mod = 998244353;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline void add_eq( int &a, int b ) { a = add( a, b ); }

inline bool chk( int left, int rig, int pos ) { return left <= pos && pos <= rig; }

int n;
int a[N], left[N], rig[N];
int f[N][N];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	std::sort( a + 1, a + n + 1 );
}
