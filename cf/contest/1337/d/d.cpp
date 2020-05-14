// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/15 23:17:46 
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
template <class T>
T aabs( T a ) { return a < 0? -a: a; }

const int N = 1e5 + 1e4;
const long long INF = 9223372036854775807;

int T;
int n_red, n_green, n_blue;
long long ans = INF;
int red[N], green[N], blue[N];

bool greater( int a, int cur, int nxt ) { return aabs( cur - a ) >= aabs( nxt - a ); }

inline long long pow( int a ) { return 1LL * a * a; }

inline long long get_ans( int a, int b, int c ) {
	if( a <= 0 || b <= 0 || c <= 0 ) 
		return ans;
	if( a > n_red || b > n_green || c > n_blue ) 
		return ans;
	return pow( red[a] - green[b]) + pow( red[a] - blue[c] ) + pow( green[b] - blue[c] );
}

void chk_ans( int a, int b, int c ) {
	for( int i = -20; i <= 20; i ++ ) {
		for( int j = -20; j <= 20; j ++ ) {
			chk_Min( ans, get_ans( a, b + i, c + j ) );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d", &n_red, &n_green, &n_blue );
		for( int i = 1; i <= n_red; i ++ ) {
			scanf( "%d", &red[i] );
		}
		for( int i = 1; i <= n_green; i ++ ) {
			scanf( "%d", &green[i] );
		}
		for( int i = 1; i <= n_blue; i ++ ) {
			scanf( "%d", &blue[i] );
		}
		std::sort( red + 1, red + n_red + 1 );
		std::sort( green + 1, green + n_green + 1 );
		std::sort( blue + 1, blue + n_blue + 1 );

		int p1 = 1, p2 = 1, p3 = 1;
		ans = get_ans( 1, 1, 1 );
		while( p1 <= n_red ) {
			while( p2 < n_green && greater( red[p1], green[p2], green[ p2 + 1 ] ) )
				p2 ++;
			while( p3 < n_blue && greater( red[p1], blue[p3], blue[ p3 + 1 ] ) ) 
				p3 ++;
			chk_ans( p1, p2, p3 );
			p1 ++;
		}
		p1 = 1, p2 = 1, p3 = 1;
		while( p2 <= n_green ) {
			while( p1 < n_red && greater( green[p2], red[p1], red[ p1 + 1 ] ) )
				p1 ++;
			while( p3 < n_blue && greater( green[p2], blue[p3], blue[ p3 + 1 ] ) ) 
				p3 ++;
			chk_ans( p1, p2, p3 );
			p2 ++;
		}
		p1 = 1, p2 = 1, p3 = 1;
		while( p3 <= n_blue ) {
			while( p1 < n_red && greater( blue[p3], red[p1], red[ p1 + 1 ] ) )
				p1 ++;
			while( p2 < n_green && greater( blue[p3], green[p2], green[ p2 + 1 ] ) )
				p2 ++;
			chk_ans( p1, p2, p3 );
			p3 ++;
		}
		printf( "%lld\n", ans );
	}
}
