#include <cstdio>
#include <algorithm>

inline int Min(int a, int b) { return a < b ? a : b;}

const int N = 3e5;
const int INF = 0x3f3f3f3f;

int n, m;
int is[N], min[N];

// Edge Start 
struct edge {
	int to, next, val;
} e[N << 1], ne[N << 1];
int ehead[N], ecnt, nehead[N], necnt;

inline void add_edge(int now, int to, int val, int ehead[], int& ecnt, edge e[]) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now]; 
	ehead[now] = ecnt;
}
// Edge End

// Heavy-Light Decopostion Start 
int dep[N], fa[N], son[N], mson[N], id[N], top[N], idcnt;
void pre_son(int now = 1, int la = 0, int depth = 1) {
	dep[now] = depth; fa[now] = la;
	son[now] = 1;
	for(int i = ehead[now]; i; i = e[i].next) {
		if( e[i].to == la )
			continue;
		min[ e[i].to ] = Min(min[now], e[i].val);
		pre_son(e[i].to, now, depth + 1);
		son[now] += son[ e[i].to ];
		if( son[ e[i].to ] > son[ mson[now] ] )
			mson[now] = e[i].to;
	}
}

void get_top(int now = 1, int la = 0) {
	id[now] = ++idcnt;
	if( top[now] == 0 )
		top[now] = now;
	if( mson[now] == 0 )
		return ;
	top[ mson[now] ] = top[now];
	get_top(mson[now], now);
	for(int i = ehead[now]; i; i = e[i].next) {
		if( e[i].to == la || e[i].to == mson[now] )
			continue;
		get_top(e[i].to, now);
	}
}

int lca(int from, int to) {
	while( top[from] != top[to] ) {
		if(dep[from] < dep[to] ) 
			{ int tmp = to; to = from; from = tmp; }
		from = fa[ top[from] ];
	}
	return dep[from] > dep[to]? to: from;
}
// Heavy-Light Decopostion End

bool cmp(int a, int b) { return id[a] < id[b]; }

int st[N], stcnt;

void push(int now){
	if( stcnt == 1 ) {
		st[ ++ stcnt ] = now;
		return ;
	}
	int l = lca(now, st[stcnt]);
	if(l == st[stcnt]) 
		return ;
	while( stcnt > 1 && id[ st[ stcnt - 1 ] ] >= id[l] )
		add_edge(st[ stcnt - 1 ], 0, st[stcnt], nehead, necnt, ne), stcnt --;
	if( st[stcnt] != l ) {
		add_edge(l, st[stcnt], 0, nehead, necnt, ne);
		st[stcnt] = l;
	}
	st[ ++ stcnt ] = now;
}

int dfs(int now) {
	if( nehead[now] == 0 )
		return min[now];
	int temp = 0;
	for(int i = nehead[now]; i; i = ne[i].next) {
		temp += dfs( ne[i].to );
	}
	nehead[now] = 0;
	return Min(min[now], temp);
}

int main() {
#ifdef woshiluo
	freopen("luogu.2495.in", "r", stdin);
	freopen("luogu.2495.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1, u, v, w; i < n; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w, ehead, ecnt, e);
		add_edge(v, u, w, ehead, ecnt, e);
	}
	min[1] = INF;
	pre_son();
	get_top();
	scanf("%d", &m);
	while( m -- ) {
		int tmp;
		scanf("%d", &tmp);
		for(int i = 1; i <= tmp; i++) 
			scanf("%d", &is[i]);
		std::sort(is + 1, is + tmp + 1, cmp);
		st[ stcnt = 1 ] = 1;
		for(int i = 1; i <= tmp; i++) 
			push( is[i] );
		while( stcnt > 0 ) 
			add_edge(st[stcnt - 1], st[stcnt], 0, nehead, necnt, ne), stcnt --;
		printf("%d\n", dfs(1));
	}
}
