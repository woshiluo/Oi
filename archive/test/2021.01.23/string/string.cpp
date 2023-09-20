#include <cstdio>
#include <cstring>

const int N = 2100;
const int mod = 1e9 + 7;

struct ModInt {
	int cur;
	ModInt( int _cur = 0 ) {
		cur = ( ( _cur % mod ) + mod ) % mod;
	}
	ModInt operator +( const ModInt &b ) const {
		return ( cur + b.cur ) % mod;
	}
	void operator +=( const ModInt &b ) {
		cur += b.cur;
		if( cur >= mod ) 
			cur -= mod;
	}
	ModInt operator *( const ModInt &b ) const {
		return ( 1LL * cur * b.cur ) % mod;
	}
	void output( char ed = '\n' ) const {
		printf( "%u%c", cur, ed );
	}
};

int n, k;
int a[N];
ModInt up[N], down[N];
ModInt f[N][N];
// 0 <= 
// 1 >

int main() {
	freopen( "string.in", "r", stdin );
	freopen( "string.out", "w", stdout );

	char str[N];
	scanf( "%d%d", &n, &k );
	scanf( "%s", str );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = str[ i - 1 ] - 'a' + 1;
	}

	f[0][0] = 1;
	for( int i = 0; i < n; i ++ ) {
		int less = a[ i + 1 ] - 1, more = 26 - a[ i + 1 ], ad = n - ( i + 1 ) + 1;
		for( int j = 0; j <= k; j ++ ) {
			int nxt = j + ad;
			down[j] += f[i][j];
			f[ i + 1 ][j] += down[j] * less;
			if( nxt > k ) 
				continue;
			up[nxt] += f[i][j];
			f[ i + 1 ][nxt] += up[nxt] * more;
		}
	}

	( f[n][k] + down[k] ).output();
}
