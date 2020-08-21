// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/07 23:17:40 
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

const int N = 1e5 + 1e4;

std::priority_queue<int> q;

int T, n;
int a[N], pool[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		memset( pool, 0, sizeof(pool) );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			pool[ a[i] ] ++;
		}
		for( int i = 1; i <= n; i ++ ) {
			if( pool[i] != 0 ) 
				q.push(pool[i]);
		}

		int cnt = 0;
		int top = q.top();
		while( !q.empty() && q.top() == top ) {
			cnt ++;
			q.pop();
		}
		int cur_min = cnt - 1, max_cap = ( top - 1 ), cur_cap = 0;
		while( !q.empty() ) {
			int top = q.top(); q.pop();
			cur_cap += top;
			if( cur_cap >= max_cap ) {
				cur_min ++;
				cur_cap -= max_cap;
			}
		}
		printf( "%d\n", cur_min );
	}
}
