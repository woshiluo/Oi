// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/22 16:24:37 
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

int T;
int n, x, y;
int a[N];
int pool[N], ans[N];

struct node { 
	int val, cnt; 
	bool operator< ( const node &b ) const {
		return cnt < b.cnt;
	}
};

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d", &n, &x, &y );
		std::vector<int> pos[N];
		memset( pool, 0, sizeof(pool) );
		memset( ans, 0, sizeof(ans) );
		int fill = n + 1;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			pool[ a[i] ] ++;
			pos[ a[i] ].push_back(i);
		}
		std::priority_queue<node> q;
		for( int i = 1; i <= n + 1; i ++ ) {
			if( pool[i] != 0 ) 
				q.push( (node){ i, pool[i] } );
			else 
				fill = i;
		}
		for( int i = 1; i <= x; i ++ )  {
			node top = q.top(); q.pop();
			ans[ pos[top.val].back() ] = top.val;
			pos[top.val].pop_back();
			top.cnt --;
			if( top.cnt != 0 ) 
				q.push(top);
		}
		y -= x;
		while( q.size() >= 2 && y > 0 ) {
			if( y == 3 && q.size() == 3 ) {
				node top1 = q.top(); q.pop();
				node top2 = q.top(); q.pop();
				node top3 = q.top(); q.pop();
				ans[ pos[top1.val].back() ] = top2.val;
				ans[ pos[top2.val].back() ] = top3.val;
				ans[ pos[top3.val].back() ] = top1.val;
				y -= 3;
				continue;
			}
			node top1 = q.top(); q.pop();
			node top2 = q.top(); q.pop();
			ans[ pos[top1.val].back() ] = top2.val;
			ans[ pos[top2.val].back() ] = ( ( y != 1 )? top1.val: fill );
			pos[top1.val].pop_back(); pos[top2.val].pop_back();
			top1.cnt --, top2.cnt --;
			if( top1.cnt != 0 ) 
				q.push(top1);
			if( top2.cnt != 0 ) 
				q.push(top2);
			y -= 2;
		}
		if( y > 0 ) 
			printf( "NO\n" );
		else {
			printf( "YES\n" );
			for( int i = 1; i <= n; i ++ ) {
				printf( "%d ", ( ans[i] == 0 )? fill: ans[i] );
			}
			printf( "\n" );
		}
	}
}
