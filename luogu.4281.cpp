#include <cstdio>

inline int Max(int a, int b) {return a > b? a: b;}

const int N = 510000;

int n, m;

// edge start 
struct edge{
	int to, next;
}e[N << 1];
int ehead[N], ecnt;
inline void add_edge(int now, int to){
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

// Heavy-Light Decompostion start
int son[N], mson[N], dis[N], dep[N], fa[N], id[N], top[N], idcnt;
void dfs1(int now = 1, int la = 0, int depth = 1){
	dis[now] = depth;
	son[now] = 1; 
	fa[now] = la; dep[now] = depth;
	for(int i = ehead[now]; i; i = e[i].next){
		if(e[i].to == la)
			continue;
		dfs1(e[i].to, now, depth + 1);
		son[now] += son[ e[i].to ];
		if(son[ e[i].to ] > son[ mson[now] ])
			mson[now] = e[i].to;
	}
}

void dfs2(int now = 1, int la = 0){
	id[now] = ++idcnt;
	if(top[now] == 0)
		top[now] = now;
	if(mson[now] == 0)
		return ;
	top[ mson[now] ] = top[now];
	dfs2(mson[now], now);
	for(int i = ehead[now]; i; i = e[i].next){
		if(e[i].to == la || e[i].to == mson[now])
			continue;
		dfs2(e[i].to, now);
	}
}

int lca(int from, int to){
	while(top[from] != top[to]){
		if(dep[ top[from] ] < dep[ top[to] ]){ int tmp = from; from = to; to = tmp; }
		from = fa[ top[from] ];
	}
	return dep[from] < dep[to]? from: to;
}
// Heavy-Light Decompostion end

int main(){
#ifdef woshiluo
	freopen("luogu.4281.in", "r", stdin);
	freopen("luogu.4281.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v; i < n; i++){
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}

	dfs1();
	dfs2();

	while( m-- ){
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		int lca1 = lca(x, y), lca2 = lca(y, z), lca3 = lca(x, z);
		int ans = dep[lca1] > dep[lca2]? lca1: lca2;
		ans = dep[lca3] > dep[ans]? lca3: ans;
		printf("%d %d\n", ans, dis[x] + dis[y] + dis[z] - (dis[ lca(lca1, lca(lca2, lca3)) ] << 1) - dis[ans]);
	}
}
