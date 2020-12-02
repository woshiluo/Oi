// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/30 13:50:34 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

bool cmp( int _a, int _b ) { return _a > _b; }

int main() {
	int n, k;
	std::priority_queue<long long> q;
	scanf( "%d%d", &n, &k );
	int a[ n + 10 ];
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}

	std::sort( a + 1, a + n + 1, cmp );
	for( int i = 1; i <= k + 1; i ++ ) {
		q.push(0);
	}
	
	long long res = 0;
	for( int i = 1; i <= n; i ++ ) {
		long long cur = q.top(); q.pop();

		res += cur;
		cur += a[i];
		q.push(cur);
	}

	printf( "%lld\n", res );
}
