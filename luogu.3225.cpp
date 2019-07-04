#include <cstdio>
#include <cstring>

inline int Min(int a, int b) { return a < b? a: b; }
inline int Max(int a, int b) { return a > b? a: b; }

const int N = 510;

int n, cnt, cut_cnt, _case;

// Edge Start 
struct edge {
	int to, next;
} e[N << 1];
int ehead[N], ecnt;

inline void add_edge(int now, int to) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now]; 
	ehead[now] = ecnt;
}

void edge_init() {
	ecnt = 0;
	memset(ehead, 0, sizeof(ehead));
}
// Edge End

// Tarjan Start
int dfn[N], low[N] , time_index;
bool cut[N];
void tarjan(int now, int fa) {
	dfn[now] = low[now] = ++ time_index;
	bool flag = false;
	for(int i = ehead[now]; i; i = e[i].next) {
		if( e[i].to == fa )
			continue;
		if( dfn[ e[i].to ] == 0 ) {
			tarjan(e[i].to, now);
			low[now] = Min(low[now], low[ e[i].to ]);
			if( low[ e[i].to ] >= dfn[now] ) {
				if( now != fa || flag ) 
					cut[now] = true;
				flag = true;
			}
		}
		else 
			low[now] = Min(low[now], dfn[ e[i].to ]);
	}
}

void _tarjan(int QAQ) {
	for(int i = 1; i <= QAQ; i++) {
		if( dfn[i] == 0 ) 
			tarjan(i, i);
	}
}
// Tarjan End

int col[N], col_cnt;

void dfs(int now)  {
	col[now] = col_cnt;
	if( cut[now] )
		return ;
	cnt ++;
	for(int i = ehead[now]; i; i = e[i].next) {
		if( cut[ e[i].to ] && col[ e[i].to ] != col_cnt ) {
			cut_cnt ++;
			col[ e[i].to ] = col_cnt;
		}
		if( col[ e[i].to ] == 0 )
			dfs( e[i].to );
	}
}	

void init() {
	edge_init();
	// Tarjan_init
	time_index = col_cnt = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(col, 0, sizeof(col));
	memset(cut, 0, sizeof(cut));
}

int main(){
#ifdef woshiluo
	freopen("luogu.3225.in", "r", stdin);
	freopen("luogu.3225.out", "w", stdout);
#endif
	while( scanf("%d", &n) != EOF ) {
		if( n == 0 ) 
			break;
		init();
		int tmp = 0, ans = 0; 
		long long base = 1;

		for(int i = 1, u, v; i <= n; i++) {
			scanf("%d%d", &u, &v);
			tmp = Max(tmp, Max(u, v));
			add_edge(u, v);
			add_edge(v, u);
		}

		_tarjan(tmp);

		for(int i = 1; i <= tmp; i++) {
			if( col[i] || cut[i] )
				continue;
			col_cnt ++;
			cnt = cut_cnt = 0;
			dfs(i);
			if( cut_cnt == 0 )
				ans += 2, base *= 1LL * cnt * (cnt - 1) / 2LL;
			else if( cut_cnt == 1)
				ans ++, base *= 1LL * cnt;
		}
		printf("Case %d: %d %lld\n", ++ _case, ans, base);
	}
}
