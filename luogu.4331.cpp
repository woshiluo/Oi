#include <cstdio>

#include <queue>

const int N = 1e6 + 1e5;

typedef long long ll;

int n;
int a[N], b[N];
std::priority_queue<int> q;

ll aabs( ll cur ) { return cur < 0? -cur: cur; }

int main() {
#ifdef woshiluo
	freopen( "luogu.4331.in", "r", stdin );
	freopen( "luogu.4331.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &b[i] );
		b[i] -= i;
	}
	for( int i = 1; i <= n; i ++ ) {
		q.push( b[i] );
		if( q.top() > b[i] ) {
			q.pop();
			q.push( b[i] );
		}
		a[i] = q.top();
	}

	for( int i = n - 1; i >= 1; i -- ) {
		a[i] = std::min( a[ i + 1 ], a[i] );
	}

	ll ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		ans += aabs( b[i] - a[i] );
	}

	printf( "%lld\n", ans );

	for( int i = 1; i <= n; i ++ ) 
		printf( "%d ", a[i] + i );

}
