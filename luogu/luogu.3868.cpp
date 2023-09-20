#include <cstdio>

int n;
int a[N];

int exgcd( int a, int b, int &x, int &y ) {
	if( b == 0 ) {
		x = 1, y = 0;
		return a;
	}
	exgcd( b, a % b, y, x );
	y -= a / b * x;
}

inline int get_inv( int a, int mod ) {
	return ksm( a, mod - 2, mod );
}

int get_crt( int n_list[], int a_list[], int cnt ) {/*{{{*/
	int m[cnt], c[cnt];
	int count_n = 1;
	for( int i = 0; i < cnt; i ++ ) {
		count_n *= n_list[i];
	}
	for( int i = 0; i < cnt; i ++ ) {
		m[i] = count_n / n_list[i];
		c[i] = m[i] * get_inv( m[i], n_list[i] );
	}
	int res = 0;
	for( int i = 0; i < cnt; i ++ ) {
		res = ( res + ( ( 1LL * a_list[i] * c[i] ) % count_n ) ) % count_n;
	}
	return res;
}/*}}}*/

int main() {
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &b[i] );
	}

}
