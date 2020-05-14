// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/27 00:04:43 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
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

const int N = 2e5 + 1e4;

int n, k, st, la;
int c[N], m[N];
std::stack<int> pool[N];
std::vector<int> ans[N];

struct edge { int lst, cur, nxt; } e[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &m[i] );
	}
	for( int i = 1; i <= k; i ++ ) {
		scanf( "%d", &c[i] );
	}
	std::sort( m + 1, m + n + 1 );
	int p1 = 1;
	for( int i = k; i >= 1; i -- ) {
		while( m[p1] <= c[i] && p1 <= n ) {
			pool[i].push( m[p1] );
			p1 ++;
		}
	}
	for( int i = 1; i <= k; i ++ ) {
		if( !pool[i].empty() ) {
			if( st == 0 ) {
				st = la = i;
				e[i] = (edge){ 0, i, 0 };
			}
			else {
				e[la].nxt = i;
				e[i] = (edge){ la, i, 0 };
				la = i;
			}
		}
	}
	int cnt = n, ans_len = 1;
	while( cnt > 0 ) {
		int cur = st;
		for( int i = 1; i <= k; i ++ ) {
			if( cur == 0 )
				break;
			ans[ans_len].push_back( pool[ e[cur].cur ].top() );
			pool[ e[cur].cur ].pop();
			cnt --;
			if( pool[ e[cur].cur ].empty() ) {
				if( cur == st ) {
					st = e[cur].nxt;
					e[st].lst = 0;
				}
				else if( e[cur].nxt == 0 ) {
					e[ e[cur].lst ].nxt = 0;
				}
				else {
					int lst = e[cur].lst;
					int nxt = e[cur].nxt;
					e[nxt].lst = lst;
					e[lst].nxt = nxt;
				}
				cur = e[cur].nxt;
			}
			if( cur == i ) {
				cur = e[cur].nxt;
			}
		}
		ans_len ++;
	}

	printf( "%d\n", ans_len - 1 );
	for( int i = 1; i < ans_len; i ++ ) {
		int size = ans[i].size();
		printf( "%d ", size );
		for( int j = 0; j < size; j ++ ) {
			printf( "%d ", ans[i][j] );
		}
		printf( "\n" );
	}
}
