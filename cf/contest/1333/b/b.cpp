// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020-04-08 22:41
// Blog: https://blog.woshiluo.com
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

const int N = 1e5 + 1e4;

inline int hash( int a ) {
	return a + 1;
}

int T;
int n;
int a[N], b[N];
bool vis[N][3];
// 0 -1 
// 1 0 
// 2 1

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		bool flag = true;
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			int tmp_hash = hash( a[i] );
			vis[i][tmp_hash] = true;
			if( tmp_hash != 0 ) 
				vis[i][0] = vis[ i - 1 ][0];
			if( tmp_hash != 1 ) 
				vis[i][1] = vis[ i - 1 ][1];
			if( tmp_hash != 2 ) 
				vis[i][2] = vis[ i - 1 ][2];
		}
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &b[i] );
		}
		for( int i = n; i >= 1; i -- ) {
			if( a[i] == b[i] ) 
				continue;
			if( b[i] > a[i] ) {
				if( vis[ i - 1 ][2] == false ) {
					flag = false;
					break;
				}
			}
			if( b[i] < a[i] ) {
				if( vis[ i - 1 ][0] == false ) {
					flag = false;
					break;
				}
			}
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}

