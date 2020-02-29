#include <cstdio>

const int N = 1e5 + 1e4;

inline int Max( int a, int b ) { return a > b? a: b; }

int n, ans = -1, ans_id;
int bit[60], a[N];

void bit_sqilt( int cur ) {
	int cnt = 1;
	while( cur ) { 
		bit[cnt] += ( cur & 1 );
		cur >>= 1;
		cnt ++;
	}
}

int main() {
#ifdef woshiluo
	freopen( "C.in", "r", stdin );
	freopen( "C.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		bit_sqilt( a[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		int tmp = a[i], pow_2 = 1, cnt = 1, res = 0;
		while( pow_2 <= tmp ) {
			if( ( a[i] & pow_2 ) && bit[cnt] == 1 ) 
				res = res | ( pow_2 );
			pow_2 <<= 1;
			cnt ++;
		}
		if( res > ans ) {
			ans = res;
			ans_id = i;
		}
	}
	printf( "%d ", a[ans_id] );
	for( int i = 1; i <= n; i ++ ) {
		if( i == ans_id ) 
			continue;
		printf( "%d ", a[i] );
	}
}
