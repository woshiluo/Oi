#include <cstdio>

#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 1e5 + 1e4;

int n, k, cnt;
long long ans = 0;
int x[N], mp[N], pool[N];

inline long long dx( int n ) {
	if( n < 1 ) 
		return 0;
	return ( 1LL * ( 1 + n ) * n ) >> 1LL;
}

inline int get_gol_id( long long gol ) {
	int gol_id = std::lower_bound( mp + 1, mp + cnt + 1, gol ) - mp;
	if( gol_id > cnt ) 
		gol_id = cnt;
	while( mp[ gol_id ] > gol && gol_id > 1 )
		gol_id --;
	return gol_id;
}

int main() {
	freopen( "game.in", "r", stdin );
	freopen( "game.out", "w", stdout );

	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &x[i] );
		mp[i] = x[i];
	}
	std::sort( mp + 1, mp + n + 1 );
	cnt = ( std::unique( mp + 1, mp + n + 1 ) - mp ) - 1;

#ifdef woshiluo
	printf( "%d\n", cnt );
	for( int i = 1; i <= cnt; i ++ ) {
		printf( "%d\n", mp[i] );
	}
#endif
	for( int i = 1; i <= n; i ++ ) {
#ifdef woshiluo
		printf( "%d: ", x[i] );
#endif
		x[i] = std::lower_bound( mp + 1, mp + cnt + 1, x[i] ) - mp;
		pool[ x[i] ] ++;
#ifdef woshiluo
		printf( "%d\n", x[i] );
#endif
	}

	for( int i = 1; i <= cnt; i ++ ) {
		int gol_id = get_gol_id( 1LL * mp[i] * k );
#ifdef woshiluo
		printf( "%d gol: %lld gol_id: %d\n", mp[i], 1LL * mp[i] * k, gol_id );
#endif
		ans += 6LL * dx( gol_id - i - 1 );
	}

	for( int i = 1; i <= cnt; i ++ ) {
		if( pool[i] >= 2 ) {
			int cur = mp[i];
			int gol_left = get_gol_id( cur / k );
			while( 1LL * mp[gol_left] * k < cur )
				gol_left ++;
			int gol_rig = get_gol_id( 1LL * cur * k );
			ans += 3LL * Max( gol_rig - gol_left, 0 );
		}
		if( pool[i] >= 3 ) 
			ans ++;
	}

	printf( "%lld\n", ans );
}
