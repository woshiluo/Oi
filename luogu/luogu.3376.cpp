#include <cstdio>
#include <cstring>

#include <queue>

template <class T>/*{{{*/
T Min( T a, T b ) { return a < b? a: b; }
template <class T>
T Max( T a, T b ) { return a > b? a: b; }
template <class T>
T chk_Min( T &a, T b ) { if( a > b ) a = b; }
template <class T>
T chk_Max( T &a, T b ) { if( a < b ) a = b; }

inline bool is_digit( const char cur ) { return cur >= '0' && cur <= '9'; }
template <class T>
T read() {
	T res = 0, k = 1; char x = getchar();
	for( ; !is_digit(x); x = getchar() ) 
		if( x == '-' ) 
			k = -1;
	for( ; is_digit(x); x = getchar() ) 
		res = res * 10 + ( x - '0' );
	return res * k;
}/*}}}*/

typedef long long ll;
typedef unsigned long long ull;

const int N = 210;
const int M = 5100;
const ll LLM = 0x3f3f3f3f3f3f3f3f;

int n, m, s, t;

struct Edge {/*{{{*/
	int to, next, flow;
} e[ M << 1 ];
int ehead[N], ecnt = 1;
int thead[N];
inline void add_edge( int cur, int to, int flow ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	e[ecnt].flow = flow;
	ehead[cur] = ecnt;
}/*}}}*/

namespace Dinic {
	int st, ed;
	int dep[N];
	bool bfs() {
		memset( dep, -1, sizeof(dep) );
		dep[st] = 0;
		std::queue<int> q;
		q.push(st);
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = ehead[cur]; i; i = e[i].next ) {
				if( e[i].flow == 0 ) 
					continue;
				int to = e[i].to;
				if( dep[to] != -1 ) 
					continue;
				dep[to] = dep[cur] + 1;
				q.push(to);
			}
		}
		return dep[ed] != -1;
	}
	ll dfs( int cur, ll flow ) {
		if( cur == ed ) 
			return flow;
		ll res = 0;
		for( int &i = thead[cur]; i; i = e[i].next ) {
			if( !flow ) 
				break;
			if( e[i].flow && dep[ e[i].to ] == dep[cur] + 1 ) {
				ll cur_flow = dfs( e[i].to, Min( flow, (ll)e[i].flow ) );
				res += cur_flow;
				e[i].flow -= cur_flow;
				e[ i ^ 1 ].flow += cur_flow;
				flow -= cur_flow;
			}
		}
		return res;
	}
	ll dinic( int _st, int _ed ) {
		st = _st; ed = _ed;
		ll res = 0;
		while( bfs() ) {
			// TODO: CHECK
			memcpy( thead, ehead, sizeof(ehead) );
			ll tmp = dfs( st, LLM );
			res += tmp;
		}
		return res;
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.3376.in", "r", stdin );
	freopen( "luogu.3376.out", "w", stdout );
#endif
	n = read<int>(); m = read<int>(); s = read<int>(); t = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int u, v, w;
		u = read<int>(); v = read<int>(); w = read<int>();
		add_edge( u, v, w );
		add_edge( v, u, 0 );
	}
	printf( "%lld", Dinic::dinic( s, t ) );
}
