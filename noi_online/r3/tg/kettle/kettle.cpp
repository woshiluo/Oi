#include <cstdio>
#include <cstring>

#include <algorithm>

template<class T>
void aabs( T &a ) { return a < 0? -a: a; }
template<class T>
T Min( T a, T b ) { return a < b? a: b; }
template<class T>
T Max( T a, T b ) { return a < b? a: b; }
template<class T>
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T>
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

const int N = 1e6 + 1e5;

int n, k;
int a[N];

int main() {
	freopen( "kettle.in", "r", stdin );
	freopen( "kettle.out", "w", stdout );

	scanf( "%d%d", &n, &k );
	k ++;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}

	int cur = 0, ans = 0;
	for( int i = 1; i <= k; i ++ ) 
		cur += a[i];
	ans = cur;

	for( int left = 2, rig = k + 1; rig <= n; left ++, rig ++ ) {
		cur = cur - a[ left - 1 ] + a[rig];	
		chk_Max( ans, cur );
	}
	printf( "%d\n", ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
