#include <cstdio>

typedef __int128 lll;

const int N = 1e5 + 1e4;

// ax + by = gcd( a, b )
lll exgcd( lll a, lll b, lll &x, lll &y ) {
	if( b == 0 ) {
		x = 1; y = 0;
		return a;
	}

	lll k = exgcd( b, a % b, x, y );

	lll tmp_x = x, tmp_y = y;
	x = tmp_y;
	y = tmp_x - ( a / b ) * tmp_y;

	return k;
}

struct Node {
	// x = a (mod b)
	lll a, b;
} node[N];

Node merge( Node a, Node b ) {
	lll k1, k2;
	lll k = exgcd( a.b, b.b, k1, k2 );
	exgcd( a.b / k, b.b / k, k1, k2 );

	lll lcm = a.b / k * b.b;

	// (Node) { a + k * b, lcm( a, b ) }
	return (Node) { 
		( ( ( a.a + ( ( b.a - a.a ) / k ) * k1 * a.b ) % lcm ) + lcm ) % lcm, 
		lcm };
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4777.in", "r", stdin );
	freopen( "luogu.4777.out", "w", stdout );
#endif
	int n;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		long long a, b;
		scanf( "%lld%lld", &b, &a );
		node[i].a = a; node[i].b = b;
	}

	Node tmp = node[1];
	for( int i = 2; i <= n; i ++ ) {
		tmp = merge( tmp, node[i] );
	}

	printf( "%lld\n", (long long)tmp.a );
}
