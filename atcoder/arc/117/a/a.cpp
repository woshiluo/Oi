#include <cstdio>

#include <algorithm>

const int N = 2100;

int a, b;

void first_a() {
	int res[N], cnt = 0;
	for( int i = 1; i <= a; i ++ ) {
		res[i] = i;
		cnt += i;
	}
	for( int i = 1; i < b; i ++ ) {
		res[ a + i ] = -i;
		cnt -= i;
	}
	if( cnt <= 0 ) 
		return ;
	res[ a + b ] = -cnt;
	for( int i = 1; i <= a + b; i ++ ) {
		printf( "%d ", res[i] );
	}
	printf( "\n" );
	exit(0);
}

void first_b() {
	int res[N], cnt = 0;
	for( int i = 1; i <= b; i ++ ) {
		res[i] = -i;
		cnt -= i;
	}
	for( int i = 1; i < a; i ++ ) {
		res[ b + i ] = i;
		cnt += i;
	}
	if( cnt >= 0 ) 
		return ;
	res[ a + b ] = -cnt;
	for( int i = 1; i <= a + b; i ++ ) {
		printf( "%d ", res[i] );
	}
	printf( "\n" );
	exit(0);
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d%d", &a, &b );
	first_a();
	first_b();
}
