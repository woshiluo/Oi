#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int M = 6;
const int N = 2e5 + 1e4;

int a[M][N];

namespace sub_bf {
	void calc( const int m, const int n ) {
		for( int i = 1; i <= m; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				a[i][j] = read<int>();
			}
		}

		ll ans = 0;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				int min = a[1][i] + a[1][j];
				int max = a[1][i] + a[1][j];
				for( int k = 1; k <= m; k ++ ) {
					chk_Min( min, a[k][i] + a[k][j] );
					chk_Max( max, a[k][i] + a[k][j] );
				}
				ans += 1LL * ( min + max );
			}
		}
		
		printf( "%lld\n", ans );
	}
}

namespace sub_2 {
	void calc( const int m, const int n ) {
		for( int i = 1; i <= m; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				a[i][j] = read<int>();
			}
		}

		ll ans = 0;
		for( int i = 1; i <= m; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				ans += 2LL * a[i][j] * n;
			}
		}

		printf( "%lld\n", ans );
	}
}

int main() {
//	freopen( "sort.in", "r", stdin );
//	freopen( "sort.out", "w", stdout );

	const int m = read<int>();
	const int n = read<int>();

//	sub_bf::calc( m, n );
	if( m == 2 ) 
		sub_2::calc( m, n );
	else
		sub_bf::calc( m, n );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
