#include <cstdio>
#include <cstring>

#include <set>
#include <stack>
#include <vector>

const int N = 1e5 + 1e4;

int T;
int n;
int g[N];
// struct/class 
struct edge { int next, to; };

// Edge Start 
edge e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

int low[N], dfn[N];
bool vis[N];
std::stack<int> st;
void tarjan( int cur ) {/*{{{*/
	st.push(cur);
	vis[cur] = true;
	dfn[cur] = low[cur] = ++ time_index;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( dfn[ e[i].to ] == 0 ) 
			tarjan( e[i].to );
		if( vis[ e[i].to ] ) 
			low[cur] = Min( low[cur], low[ e[i].to ] );
	}
	if( dfn[cur] == low[cur] ) {/*{{{*/
		std::vector<int> a;
		int cur_col = ++ col_cnt;
		while( !st.empty() ) {
			int tmp = st.top();
			if( low[tmp] == low[cur] ) 
				a.push_back(tmp);
			else 
				break;
			vis[tmp] = false;
			col[tmp] = cur_col;
			cir_val[ cur_col ] += g[tmp];
		}
		int cnt = a.size();
		for( int i = 0; i < cnt; i ++ ) {
			bool flag = true;
			for( int o = ehead[ a[i] ]; o; o = e[o].next ) {
				if( col[ e[o].to ] != cur_col )
					flag = false;
			}
			if( flag ) {
				bond[ cur_col ] = true;
				break;
			}
		}
	}/*}}}*/
}/*}}}*/

void tarjan_run() {
	for( int i = 1; i <= n; i ++ ) {
		if( dfn[i] == 0 ) 
			tarjan(i);
	}
}

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		init();
		readin();
		tarjan_run();
	}
}
