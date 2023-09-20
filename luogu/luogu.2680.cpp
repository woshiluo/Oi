#include <cstdio>

const int N = 310000;

int n, m;
int son[N], mson[N], fa[N], dep[N], top[N], id[N], idcnt;

// Edge Start
struct edge{
	int to, next, val;
}e[N << 1];
int ehead[N], ecnt;
inline void add_edge(int now, int to, int val){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

// Segment Tree Start
struct node{
	int base, sum, lazy;
}tree[N << 1];
// Segment Tree End

// Heavy-Light Depostion Start
void dfs1(int now = 1, int la = 0, int depth = 1){
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

void line_add(int from, int to){
	while(top[from] != top[to]){
		if(dep[ top[from] ] < dep[ top[to] ]){ int tmp = to; to = from; from = tmp; }
		query_add(id[ top[from] ], top[from]); 
		from = fa[ top[from] ];
	}
	if(id[from] > id[to])
		query_add(id[from], id[to]);
}
// Heavy-Light Depostion End

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w; i < n; i++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	for(int i = 1, u, v; i <= m; i++){
		scanf("%d%d", &u, &v);
		line_add(u, v);
	}
}
