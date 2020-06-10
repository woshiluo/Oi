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

const int N = 110;

int n, m, q;
bool con[N][N];

namespace sub1{ 
	struct _ask {
		int cur, id;
		bool operator< ( _ask b ) { return cur < b.cur; }
	} ask[N];

	int f[N][2], ans[N];

	void calc(){
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &f[i][0] );
		}
		while( m -- ) {
			int x, y;
			scanf( "%d%d", &x, &y );
			con[x][y] = true;
		}
		for( int i = 1; i <= q; i ++ ) {
			scanf( "%d", &ask[i].cur );
			ask[i].id = i;
		}

		std::sort( ask + 1, ask + 1 + q );
		int end = ask[q].cur;
		int cur = 1, la = 0, p1 = 1;
		for( int o = 1; o <= end; o ++, la ^= 1, cur ^= 1 ) {
			for( int i = 1; i <= n; i ++ ) {
				f[i][cur] = 0;
				for( int j = 1; j <= n; j ++ ) {
					if( con[i][j] )
						f[i][cur] ^= f[j][la];
				}
			}
			while( ask[p1].cur == o && p1 <= q ) {
				ans[ ask[p1].id ] = f[1][cur];
				p1 ++;
			}
		}

		for( int i = 1; i <= q; i ++ ) {
			printf( "%d\n", ans[i] );
		}
	}
}

namespace sub3 {
	int f[N];
	void calc() {
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &f[i] );
		}
		while( m -- ) {
			int x, y;
			scanf( "%d%d", &x, &y );
		}

		int ans = f[2];
		for( int i = 3; i <= n; i ++ ) 
			ans ^= f[i];
		while( q -- ) {
			int ai;
			scanf( "%d", &ai );
			if( ( n - 1 ) % 2 == 1 ) {
				if( ai % 2 == 1 ) 
					printf( "%d\n", ans );
				else 
					printf( "%d\n", f[1] );
			}
			else 
				printf( "%d\n", ans );
		}
	}
}

int main() {
//	freopen( "magic.in", "r", stdin );
//	freopen( "magic.out", "w", stdout );

	scanf( "%d%d%d", &n, &m, &q );

	if( m == n * ( n - 1 ) / 2 ) 
		sub3::calc();
	else 
		sub1::calc();

	fclose( stdin );
	fclose( stdout );
	return 0;
}
