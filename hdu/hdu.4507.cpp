#include <cstdio>

const int mod = 1e9 + 7;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline int power( int a ) { return mul( a, a ); }

int T, max_len;
long long left, rig;
int _count[110][2][10][10][10], _sum[110][2][10][10][10], _pow[110][2][10][10][10];
int max_count[110][2][10][10][10], max_sum[110][2][10][10][10], max_pow[110][2][10][10][10];
bool _vis[110][2][10][10][10];
int a[110];

inline int length( int cur, int len ) {
	int res = cur;
	while( len > 0 ) {
		res = mul( 10, res );
		len --;
	}
	return res;
}

struct node {
	int len, cur, seven, rem, base_rem;
	bool max;
	int& count() {
		if( max ) 
			return max_count[len][seven][rem][cur][base_rem];
		return _count[len][seven][rem][cur][base_rem];
	}
	int& sum() {
		if( max )
			return max_sum[len][seven][rem][cur][base_rem];
		return _sum[len][seven][rem][cur][base_rem];
	}
	int& pow() {
		if( max ) 
			return max_pow[len][seven][rem][cur][base_rem];
		return _pow[len][seven][rem][cur][base_rem];
	}
	bool& vis() {
		return _vis[len][seven][rem][cur][base_rem];
	}
	void print() {
//		printf( "%d %d %d %d %d %d\n", len, cur, seven, rem, base_rem, max );
//		printf( "%d %d %d\n", count(), sum(), pow() );
	}
};

int dfs( node cur ) {
	if( ( ! cur.max ) && cur.vis() )
		return cur.pow();
	if( cur.len == 0 ) {
		if( cur.seven || cur.rem == 0 || cur.base_rem == 0 ) {
			cur.count() = cur.sum() = cur.pow() = 0;
			return cur.pow();
		}
		cur.count() = 1; cur.sum() = cur.cur; cur.pow() = power( cur.cur );
		return cur.pow();
	}
	int &cur_count = cur.count();
	int &cur_sum = cur.sum();
	int &cur_pow = cur.pow();
	if( cur.max ) 
		cur_count = cur_sum = cur_pow = 0;
	for( int i = 0; i <= ( cur.max? a[cur.len]: 9 ); i ++ ) {
		node nxt = cur;
		nxt.len -= 1; nxt.seven = ( cur.seven || ( i == 7 ) ); nxt.cur = i; nxt.max = ( cur.max && i == a[cur.len] );
		nxt.rem = ( cur.rem * 10 + i ) % 7; nxt.base_rem = ( cur.base_rem + i ) % 7;
		dfs( nxt );
		cur_count = add( cur_count, nxt.count() );
		cur_sum = add( cur_sum, add( mul( length( cur.cur, cur.len ), nxt.count() ), nxt.sum() ) );
		cur_pow = add( cur_pow, add( nxt.pow(), add( mul( nxt.count(), power( length( cur.cur, cur.len ) ) ), 
						mul( mul( 2, length( cur.cur, cur.len ) ), nxt.sum() ) ) ) );
	}
	if( cur.max == false )
		cur.vis() = true;
	cur.print();
	return cur_pow;
}

int sum( long long _a ) {
	if( _a == 0 ) 
		return 0;
	if( _a < 0 )
		return 0;
	max_len = 0;
	while( _a ) { 
		a[ ++ max_len ] = _a % 10;
		_a /= 10;
	}
//	printf( "ans: %d\n", dfs( (node){ max_len, 0, 0, 0, 0, true } ) );
	return dfs( (node){ max_len, 0, 0, 0, 0, true } );
}

int main() {
#ifdef woshiluo
	freopen( "hdu.4507.in", "r", stdin );
	freopen( "hdu.4507.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%lld%lld", &left, &rig );
		if( left == 0 ) 
			printf( "%d\n", ( sum(rig) + mod ) % mod );
		else 
			printf( "%d\n", ( add( sum(rig), - sum( left - 1 ) ) + mod ) % mod );
	}
}
