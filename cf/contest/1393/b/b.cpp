// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/07 22:51:58 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1e5 + 1e4;

int n, q;
int a[N];
long long pool[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	long long cnt_2 = 0, cnt_4 = 0;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		pool[ a[i] ] ++;
	}
	for( int i = 1; i <= n; i ++ ) {
		cnt_2 += ( pool[i] / 2LL );
		cnt_4 += ( pool[i] / 4LL );
	}
	scanf( "%d", &q );
	while( q -- ) {
		char op[3];
		int x;
		scanf( "%s%d", op, &x );
		if( op[0] == '-' ) {
			if( ( pool[x] % 4 ) == 0 ) 
				cnt_4 --;
			if( ( pool[x] % 2 ) == 0 ) 
				cnt_2 --;
			pool[x] --;
		}
		else {
			if( ( pool[x] % 4 ) == 3 ) 
				cnt_4 ++;
			if( ( pool[x] % 2 ) == 1 ) 
				cnt_2 ++;
			pool[x] ++;
		}

		if( cnt_4 >= 1 && ( ( cnt_2 - 2 ) >= 2 ) ) 
			printf( "YES\n" );
		else 
			printf( "NO\n" );
	}

}
