// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/25 19:41:53 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

using std::make_pair;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const long long N = 5e5 + 1e4;

long long n;
long long a[N], b[N], cnt[N], sum[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	for( long long i = 1; i <= 6; i ++ ) {
		scanf( "%lld", &a[i] );
	}
	std::sort( a + 1, a + 6 + 1 );
	scanf( "%lld", &n );
	if( n == 1 ) {
		printf( "0\n" );
		return 0;
	}
	std::vector< std::pair<long long, long long> > pos;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lld", &b[i] );
		for( int j = 1; j <= 6; j ++ ) {
			if( b[i] - a[j] > 0 )
				pos.push_back( make_pair( b[i] - a[j], i ) );
		}
	}
	std::sort( pos.begin(), pos.end() );

	int cnt = 0;
	long long ans = ( 1LL << 61LL );
	int p1 = 0, p2 = 0;
	int size = pos.size();
	while( p1 < size ) {
		while( p2 < size && cnt != n ) {
			int cur = pos[p2].second;
			if( sum[cur] == 0 ) 
				cnt ++;
			sum[cur] ++;
			p2 ++;
		}
		if( cnt == n )
			ans = std::min( ans, pos[p2 - 1].first - pos[p1].first );
		int cur = pos[p1].second;
		if( sum[cur] == 1 ) 
			cnt --;
		sum[cur] --;
		p1 ++;
		if( p2 < p1 ) 
			p2 = p1;
	}

	printf( "%lld\n", ans );
}
