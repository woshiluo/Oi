// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/07 22:45:52 
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

const long long N = 1e5 + 1e4;

long long A, B, n;

struct node {
	long long a, b;
} a[N];

bool cmp( node _a, node _b ) { return _a.a < _b.a; }

bool work() {
	for( long long i = 1; i <= n; i ++ )  {
		if( B <= 0 ) 
			return false;
		long long killed_times = ( a[i].b / A ) + ( a[i].b % A != 0LL );
		long long live_times = ( B / a[i].a ) + ( B % a[i].a != 0LL );
		if( live_times < killed_times )
			return false;
		B -= killed_times * a[i].a;
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	long long T;
	scanf( "%lld", &T );
	while( T -- ) {
		scanf( "%lld%lld%lld", &A, &B, &n );
		for( long long i = 1; i <= n; i ++ ) {
			scanf( "%lld", &a[i].a );
		}
		for( long long i = 1; i <= n; i ++ ) {
			scanf( "%lld", &a[i].b );
		}
		std::sort( a + 1, a + n + 1, cmp );
		printf( "%s\n", work()? "YES": "NO" );
	}
}
