#include <cstdio>
#include <cstring>

#include <queue>

const int N = 5e6 + 1e5;

struct edge { int next, to; };

struct AC_AM{
	struct node { int nxt[26], fail; };

	int rt = 1, node_cnt = 1;
	node tree[N];

	int insert( char str[] );
	void build();
	void query( char str[] );
};

int n, ecnt;
int ed[N], sum[N], ehead[N];

edge e[N];
AC_AM ac_am;

inline void add_edge( int now, int to );

void dfs( int cur ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		dfs( e[i].to );
		sum[cur] += sum[ e[i].to ];
	}
} 

int main() {
#ifdef woshiluo
	freopen( "luogu.5357.in", "r", stdin );
	freopen( "luogu.5357.out", "w", stdout );
#endif
	char re_str[N];
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++)  {
		scanf( "%s", re_str );
		ed[i] = ac_am.insert( re_str );
	}

	ac_am.build();

	scanf( "%s", re_str );

	ac_am.query( re_str );

	for( int i = 2; i <= ac_am.node_cnt; i ++ ) {
		add_edge( ac_am.tree[i].fail, i );
	}

	dfs(1);

	for( int i = 1; i <= n; i ++ ) {
		printf( "%d\n", sum[ ed[i] ] );
	}
}

inline void add_edge( int now, int to ) {/*{{{*/
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}/*}}}*/

int AC_AM::insert( char str[] ) {
	int cur = rt;
	for( int i = 0; str[i]; i ++ ) {
		int cur_str = str[i] - 'a';
		if( tree[cur].nxt[cur_str] == 0 ) {
			tree[cur].nxt[cur_str] = ++ node_cnt;
			//tree[cur].fail = 1;
			tree[node_cnt].fail = 1;
		}
		cur = tree[cur].nxt[cur_str];
	}
	return cur;
}

void AC_AM::build() {
	std::queue<int> q;
	for( int i = 0; i < 26; i ++ ) {
		if( tree[1].nxt[i] )
			q.push( tree[1].nxt[i] );
		else 
			tree[1].nxt[i] = 1;
	}
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		for( int i = 0; i < 26; i ++ ) {
			if( tree[cur].nxt[i] ) {
				tree[ tree[cur].nxt[i] ].fail = tree[ tree[cur].fail ].nxt[i];
				q.push( tree[cur].nxt[i] );
			}
			else 
				tree[cur].nxt[i] = tree[ tree[cur].fail ].nxt[i];
		}
	}
}

void AC_AM::query( char str[] ) {
	int cur = 1;
	for( int i = 0; str[i]; i ++ ) {
		cur = tree[cur].nxt[ str[i] - 'a' ];
		sum[cur] ++;
	}
}
