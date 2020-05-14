// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/25 14:33
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

const long long N = 2e5 + 1e4;

struct _ask { long long id, time; };

long long n, L, v, q;
long long a[N], ans[N];
_ask ask[N];

bool cmp( long long _a, long long _b ) { return _a > _b; }
bool cmp_ask( _ask _a, _ask _b ) { return _a.time < _b.time; }

int main() {
	freopen( "endless.in", "r", stdin );
	freopen( "endless.out", "w", stdout );
	scanf( "%lld%lld%lld", &n, &L, &v );
	for( long long i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i] );
	}
	std::sort( a + 1, a + n + 1, cmp );
	scanf( "%lld", &q );
	for( long long i = 1; i <= q; i ++ ) {
		scanf( "%lld", &ask[i].time );
		ask[i].id = i;
	}
	std::sort( ask + 1, ask + q + 1, cmp_ask );
	long long p1 = 1;
	for( long long i = 1; i <= q; i ++ ) {
		while( ( L / v < ask[i].time || ( ( L % v == 0 ) && ( L / v == ask[i].time ) ) ) && p1 <= n ) {
			L += a[p1];
			p1 ++;
		}
		if( L / v < ask[i].time || ( ( L % v == 0 ) && ( L / v == ask[i].time ) ) ) 
			ans[ ask[i].id ] = -1;
		else 
			ans[ ask[i].id ] = p1 - 1;
	}

	for( long long i = 1; i <= q; i ++ ) {
		printf( "%lld\n", ans[i] );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
