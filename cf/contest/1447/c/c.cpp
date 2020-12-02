// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/15 23:45:40 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
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

struct node { long long id, val; };
node a[N];

bool cmp( node _a, node _b ) { return _a.val < _b.val; }

void solve() {
	long long n, W;
	scanf( "%lld%lld", &n, &W );
	long long f1 = ( W / 2 ) + ( W & 1 );
	for( long long i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i].val );
		a[i].id = i;
	}
	bool flag = false; long long id = 0;
	for( long long i = 1; i <= n; i ++ ) {
		if( f1 <= a[i].val && a[i].val <= W ) {
			printf( "1\n%lld\n", a[i].id );
			return ;
		}
	}
	std::sort( a + 1, a + n + 1, cmp );
	{
		std::pair<long long, long long> sum[N];
		std::vector<long long> ans[N];
		long long cur = 1;
		sum[1].first = 0; sum[1].second = 1;
		for( long long i = 1; i <= n; i ++ ) {
			if( a[i].val <= f1 ) {
				sum[cur].first += a[i].val;
				ans[cur].push_back( a[i].id );
				if( sum[cur].first >= ( f1 / 2 ) ) {
					cur ++;
					sum[cur].first = 0; sum[cur].second = cur;
				}
			}
		}
		std::sort( sum + 1, sum + cur + 1 );
		long long tot = 0, tot_ed = 0;
		for( long long i = cur; i >= 1; i -- ) {
			tot += sum[i].first;
			if( tot >= f1 ) {
				tot_ed = i;
				break;
			}
		}
		if( tot >= f1 ) {
			long long cnt = 0;
			for( long long i = cur; i >= tot_ed; i -- ) 
				cnt += ans[ sum[i].second ].size();
			printf( "%lld\n", cnt );
			for( long long i = cur; i >= tot_ed; i -- ) 
				for( auto x: ans[ sum[i].second ] )
					printf( "%lld ", x );
			printf( "\n" );
			return ;
		}
	}
	printf( "-1\n" );
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	long long T;
	scanf( "%lld", &T );
	while( T -- ) {
		solve();
	}
}
