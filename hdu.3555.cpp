#include <cstdio>
#include <cstring>

int T, max_len;
int a[100], tmp[100];
long long f[100][2][2];
// i - 6
// j - 2 
// k - 4

long long dfs( int len, bool _max, bool four, bool nine ) {
	if( _max == false ) {
		if( f[len][four][nine] )
			return f[len][four][nine];
		if( len == 0 )
			return f[len][four][nine] = 1;
	}
	else 
		if( len == 0 )
			return 1;
	long long &res = ( _max? *(new long long): f[len][four][nine] );
	if( _max ) 
		res = 0;
	for( int i = 0; i <= ( _max? a[len]: 9 ); i ++ ) {
		if( four && i == 9 ) 
			continue;
		res += dfs( len - 1, _max && ( i == a[len] ), i == 4, i == 9 );
	}
	return res;
}

long long ask( long long _a ) {
	if( _a == 0 ) 
		return 1;
	if( _a < 0 )
		return 0;
	max_len = 0;
	while( _a ) { 
		a[ ++ max_len ] = _a % 10;
		_a /= 10;
	}
	return dfs( max_len, 1, 0, 0 );
}

int main() {
#ifdef woshiluo
	freopen( "hdu.3555.in", "r", stdin );
	freopen( "hdu.3555.out", "w", stdout );
#endif
	scanf( "%d", &T );
	long long x;
	while( T -- ) {
		scanf( "%lld", &x );
		printf( "%lld\n", x - ask(x) + 1 );
	}
}
