// Woshiluo<woshiluo@woshiluo.site>
// 2021/06/05 00:03:56 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

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
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

const int N = 3e5 + 1e4;
const int K = 20;

int price[N], ton[N];
int fa[N][K], ston[N][K];
ll sum[N][K];
struct Edge {
	int to, next;
} e[N];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
inline void add_node( int from, int cur ) {
	fa[cur][0] = from;
	for( int k = 1; k < K; k ++ ) {
		int fa_k = fa[cur][ k - 1 ];
		fa[cur][k] = fa[fa_k][ k - 1 ];
	}
}

int get_highest( int cur ) {
	for( int k = K - 1; k >= 0; k -- ) {
		if( fa[cur][k] && ton[ fa[cur][k] ] ) 
			cur = fa[cur][k];
	}
	return cur;
}

struct Node {
	int ton;
	long long price;
};
Node find( int cur, int limit ) {
	Node res = (Node) { 0, 0 };
	while( limit ) {
		int tmp = get_highest(cur);
		if( ton[tmp] == 0 )
			break;
		int cur_ton = std::min( limit, ton[tmp]  );
		res.ton += cur_ton; res.price += 1LL * cur_ton * price[tmp];
		limit -= cur_ton; ton[tmp] -= cur_ton;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int node_cnt = 0, q;
	scanf( "%d", &q );
	{
		int a, c;
		scanf( "%d%d", &a, &c );
		node_cnt ++;
		ton[node_cnt] = a; price[node_cnt] = c;
		add_node( 0, 1 );
	}
	for( int i = 1; i <= q; i ++ ) {
		node_cnt ++;
		int op;
		scanf( "%d", &op );
		if( op == 1 ) {
			int p;
			scanf( "%d", &p );
			p ++;
			{
				int a, c;
				scanf( "%d%d", &a, &c );
				ton[node_cnt] = a; price[node_cnt] = c;
				add_node( p, node_cnt );
			}
		}
		else {
			int v, w;
			scanf( "%d%d", &v, &w );
			v ++;
			Node ans = find( v, w );
			printf( "%d %lld\n", ans.ton, ans.price );
			fflush( stdout );
		}
	}
}
