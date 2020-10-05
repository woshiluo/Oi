#include <cstdio>

#include <map>
#include <algorithm>

inline void chk_Min( long long &a, long long b ) { a = std::min( a, b ); }
inline void chk_Max( long long &a, long long b ) { a = std::max( a, b ); }

const int N = 5e5 + 1e4;

struct node { long long wei, val; };
bool cmp( node _a, node _b ) { 
	return _a.wei < _b.wei; 
}

int n;
long long sum[N];
node a[N];
std::map<long long, long long> mp;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		long long wei, val;
		scanf( "%lld%lld", &wei, &val );
		mp[wei] += val;
	}
	int n = 0;
	for( auto cur: mp ) {
		n ++;
//		node tmp = (node){ cur.second, cur.first };
		node tmp = (node){ cur.first, cur.second };
		a[n] = tmp;
	}
	std::sort( a + 1, a + n + 1, cmp );

	for( int i = 1; i <= n; i ++ ) {
		sum[i] = sum[ i - 1 ] + a[i].val;
	}

	long long ans = a[1].val, max = a[1].wei;
	for( int i = 2; i <= n; i ++ ) {
		chk_Max( max, - sum[ i - 1 ] + a[i].wei );
		chk_Max( ans, sum[i] - a[i].wei + max );
	}

	printf( "%lld\n", ans );
}
