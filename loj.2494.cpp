#include <cstdio>
#include <cstring>

#include <bitset>
#include <algorithm>

const int N = 5100;
const int mod = 1e9 + 7;

inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline int add( int a, int b ) { return ( ( ( a + b ) % mod ) + mod ) % mod; }

struct node {
	int len, id;
	bool val[N];
	node() {
		len = 0;
		memset( val, 0, sizeof(val) );
	}
	void push( bool cur ) {
		len ++;
		val[len] = cur;
	}
	bool& operator[] ( int index ) { return val[index]; }
	bool operator< ( node b ) { 
		for( int i = len; i >= 1; i -- ) {
			if( val[i] == b[i] )
				continue;
			return val[i] < b[i];
		}
		return false;
	}
};

int n, m, q;
int rk[N], pow[N];
node a[N];

int main() {
#ifdef woshiluo
	freopen( "loj.2494.in", "r", stdin );
	freopen( "loj.2494.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &q );
	for( int i = 1; i <= n ; i ++ ){
		for( int j = 1; j <= m; j ++ ) {
			int tmp;
			scanf( "%1d", &tmp );
			a[j].push(tmp);
		}
	}
	

	for( int i = 1; i <= m; i ++ ) {
		a[i].id = i;
	}
	std::sort( a + 1, a + m + 1 );
	for( int i = 1; i <= m; i ++ ) {
		rk[ a[i].id ] = i;
	}
	for( int i = 1; i <= n; i ++ ) {
		a[ m + 1 ].push(1);
	}
	rk[ m + 1 ] = m + 1;

	pow[0] = 1;
	for( int i = 1; i <= n + 1; i ++ ) {
		pow[i] = mul( pow[ i - 1 ], 2 );
	}

	while( q -- ) {
		node cur;
		int min = 0, max = m + 1;
		for( int j = 1; j <= m; j ++ ) {
			int tmp;
			scanf( "%1d", &tmp );
			if( tmp == 1 ) {
				if( max == m + 1 || rk[j] < rk[max] ) 
					max = j;
			}
			else {
				if( min == 0 || rk[j] > rk[min] ) 
					min = j;
			}
		}
		if( rk[min] > rk[max] ) {
			printf( "0\n" );
			continue;
		}

		min = rk[min]; max = rk[max];
		bool los = false; int ans = 0;
		for( int i = 1; i <= n; i ++ ) {
			int res = 0;
			if( a[max][i] < a[min][i] + los ) {
				if( ( ( a[min][i] + los ) % 2 ) == ( ( a[max][i] + 1 ) % 2 ) ) 
					res = 1;
				los = true;
			}
			else {
				if( ( ( a[min][i] + los ) % 2 ) != a[max][i] ) 
					res = 1;
				los = false;
			}
			if( res == 1 ) {
				ans = add( ans, pow[i - 1] );
			}
		}
		printf( "%d\n", ans + ( max == m + 1 ) );
	}
}
