#include <cstdio>
#include <cstring>

int left, rig, max_len;
int a[100], tmp[100];
int f[100][2][2][2];
// i - 6
// j - 2 
// k - 4

int dfs( int len, bool _max, bool six, bool two, bool four ) {
	if( _max == false ) {
		if( f[len][six][two][four] )
			return f[len][six][two][four];
		if( len == 0 )
			return f[len][six][two][four] = 1;
	}
	else 
		if( len == 0 )
			return 1;
	int &res = ( _max? *(new int): f[len][six][two][four] );
	if( _max ) 
		res = 0;
	for( int i = 0; i <= ( _max? a[len]: 9 ); i ++ ) {
		if( six && i == 2 ) 
			continue;
		if( i == 4 ) 
			continue;
		res += dfs( len - 1, _max && ( i == a[len] ), i == 6, i == 2, i == 4 );
	}
	return res;
}

int ask( int _a ) {
	if( _a == 0 ) 
		return 1;
	if( _a < 0 )
		return 0;
//	memset( f, 0, sizeof(f) );
	max_len = 0;
	while( _a ) { 
		a[ ++ max_len ] = _a % 10;
		_a /= 10;
	}
//	for( int i = 1; i <= max_len; i ++ ) 
//		a[i] = tmp[ max_len - i + 1 ];
	return dfs( max_len, 1, 0, 0, 0 );
}

int main() {
#ifdef woshiluo
	freopen( "hdu.2089.in", "r", stdin );
	freopen( "hdu.2089.out", "w", stdout );
#endif
	while( scanf( "%d%d", &left, &rig) != EOF ) {
		if( left == rig && left == 0 ) 
			break;
		printf( "%d\n", ask(rig) - ask( left - 1 ) );
	}
}
