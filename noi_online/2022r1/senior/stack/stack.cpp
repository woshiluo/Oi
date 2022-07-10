#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

using std::make_pair;

int full_pow( const int k ) { return 1 << k; }

const int N = 5e5 + 1e4;
const int K = 21;
const int INF = 0x3f3f3f3f;

struct SegmentTree {
	int n ;
	int tree[ N << 2 ];
	void push_up( int cur ) { tree[cur] = Min( tree[ cur << 1 ], tree[ cur << 1 | 1 ] ); }

	void set( int pos, int val, int cur, int left, int rig ) {
		if( left == rig && left == pos ) {
			tree[cur] = val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid )
			set( pos, val, cur << 1, left, mid );
		if( pos > mid )
			set( pos, val, cur << 1 | 1, mid + 1, rig );
		
		push_up( cur );
	}
	void set( int pos, int val ) { set( pos, val, 1, 1, n ); }

	int query( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur];
		}
		
		int mid = ( left + rig ) >> 1, res = n;
		if( from <= mid ) 
			chk_Min( res, query( from, to, cur << 1, left, mid ) );
		if( to > mid ) 
			chk_Min( res, query( from, to, cur << 1 | 1, mid + 1, rig ) );

		return res;
	}
	int query( int from, int to ) { return query( from, to, 1, 1, n ); }

	void build( int cur, int left, int rig ) {
		if( left == rig ) {
			tree[cur] = INF;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		
		push_up(cur);
	}
	void init( int _n ) { n = _n; build( 1, 1, n ); }
} sgt;

int a[N], b[N], degree[N];

struct Edge {
	int to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( const int from, const int to ) {
	ecnt ++;
	degree[to] ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int fa[N][K];
void dfs( const int cur ) {
	for( int k = 1; k < K; k ++ ) {
		if( fa[ fa[cur][ k - 1 ] ][ k - 1 ] )
			fa[cur][k] = fa[ fa[cur][ k - 1 ] ][ k - 1 ];
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		const int to = e[i].to;
		fa[to][0] = cur;
		dfs(to);
	}
}

int main() {
//	freopen( "stack.in", "r", stdin );
//	freopen( "stack.out", "w", stdout );

	const int n = read<int>();
	const int q = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		b[i] = read<int>();
	}

	sgt.init( n + 1 );
	std::set<std::pair<int, int>> set;
	std::stack<int> wait;

	set.insert( make_pair( n + 1, n + 1 ) );
	for( int i = n; i >= 1; i -- ) {
		int nxt1, nxt2;
		nxt1 = nxt2 = n + 1;
		auto p1 = set.lower_bound( make_pair( a[i], 0 ) );
		if( p1 -> first == a[i] ) 
			nxt1 = p1 -> second;

		nxt2 = sgt.query( b[i], n + 1 );

		const int nxt = Min( nxt1, nxt2 );
		while( !wait.empty() && wait.top() < nxt ) {
			const int top = wait.top(); wait.pop();
			set.erase( make_pair( a[top], top ) );
		}
		set.insert( make_pair( a[i], i ) );
		wait.push(i); sgt.set( b[i], i );
		add_edge( nxt, i );
	}

	dfs( n + 1 );

	for( int i = 1; i <= q; i ++ ) {
		const int l = read<int>();
		const int r = read<int>();
		int res = 1;
		int cur = l;
		for( int k = K - 1; k >= 0; k -- ) {
			if( fa[cur][k] && fa[cur][k] <= r ) {
				res += full_pow(k);
				cur = fa[cur][k];
			}
		}
		printf( "%d\n", res );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
