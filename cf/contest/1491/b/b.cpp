// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/28 21:44:23 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
T aabs( T a ) { return a < 0? -a: a; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T=int>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

const int N = 1100;
const int MAX_RIGHT = 1e6 + 1;

int a[N];
int n, u, v;

bool find_nxt( int cur, int nxt ) {
	if( aabs( cur - nxt ) <= 1 ) 
		return true;
	return false;
}

bool dfs( int cur, int pos ) {
	if( cur == n ) 
		return true;

	if( find_nxt( pos, a[ cur + 1 ] ) )
		return dfs( cur + 1, a[ cur + 1 ] );
	else
		return false;
}

bool in( int cur, int left, int rig ) {
	return left <= cur && cur <= rig;
}

int dx[4] = { +1, -1, 0, 0 };
int dy[4] = { 0, 0, +1, -1 };

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T;
	T = read();
	while( T -- ) {
		n = read(); u = read(); v = read();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read();
		}
		if( dfs( 1, a[1] ) ) {
			int ans = (int)(2e9);
			for( int i = 1; i < n; i ++ ) {
				if( a[i] == a[ i + 1 ] ) {
					chk_Min( ans, v + v );
					chk_Min( ans, u + v );
				}
				if( a[i] == a[ i + 1 ] - 1 || a[i] == a[ i + 1 ] + 1 ) {
					chk_Min( ans, u );
					chk_Min( ans, v );
				}
			}
			for( int i = 1; i <= n; i ++ ) {
				if( i + 1 <= n && a[i] != a[ i + 1 ] )
					chk_Min( ans, u );
				if( i - 1 > 0 && a[i] != a[ i - 1 ] ) 
					chk_Min( ans, u );
			}
			printf( "%d\n", ans );
		}
		else {
			printf( "0\n" );
		}
	}
}
