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

const unsigned int N = 110;

unsigned int n, m, q;
bool con[N][N];

namespace sub1{ 
	struct _ask {
		unsigned int cur, id;
		bool operator< ( _ask b ) { return cur < b.cur; }
	} ask[N];

	unsigned int f[N][2], ans[N];

	void calc(){
		for( unsigned int i = 1; i <= n; i ++ ) {
			scanf( "%u", &f[i][0] );
		}
		while( m -- ) {
			unsigned int x, y;
			scanf( "%u%u", &x, &y );
			con[x][y] = true;
		}
		for( unsigned int i = 1; i <= q; i ++ ) {
			scanf( "%u", &ask[i].cur );
			ask[i].id = i;
		}

		std::sort( ask + 1, ask + 1 + q );
		unsigned int end = ask[q].cur;
		unsigned int cur = 1, la = 0, p1 = 1;
		for( unsigned int o = 1; o <= end; o ++, la ^= 1, cur ^= 1 ) {
			for( unsigned int i = 1; i <= n; i ++ ) {
				f[i][cur] = 0;
				for( unsigned int j = 1; j <= n; j ++ ) {
					if( con[i][j] )
						f[i][cur] ^= f[j][la];
				}
			}
			while( ask[p1].cur == o && p1 <= q ) {
				ans[ ask[p1].id ] = f[1][cur];
				p1 ++;
			}
		}

		for( unsigned int i = 1; i <= q; i ++ ) {
			printf( "%u\n", ans[i] );
		}
	}
}

namespace sub3 {
	unsigned int f[N];
	void calc() {
		for( unsigned int i = 1; i <= n; i ++ ) {
			scanf( "%u", &f[i] );
		}
		while( m -- ) {
			unsigned int x, y;
			scanf( "%u%u", &x, &y );
		}

		unsigned int ans = f[2];
		for( unsigned int i = 3; i <= n; i ++ ) 
			ans ^= f[i];
		while( q -- ) {
			unsigned int ai;
			scanf( "%u", &ai );
			if( ( n - 1 ) % 2 == 1 ) {
				if( ai % 2 == 1 ) 
					printf( "%u\n", ans );
				else 
					printf( "%u\n", f[1] );
			}
			else 
				printf( "%u\n", ans );
		}
	}
}

int main() {
	freopen( "magic.in", "r", stdin );
	freopen( "magic.out", "w", stdout );

	scanf( "%u%u%u", &n, &m, &q );

	if( m == n * ( n - 1 ) / 2 ) 
		sub3::calc();
	else 
		sub1::calc();

	fclose( stdin );
	fclose( stdout );
	return 0;
}
