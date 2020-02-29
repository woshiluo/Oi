#include <cstdio>

const int N = 110000;

int n;

// Edge Start
struct edge{
	int next, to;
}e[N << 1];
int ehead[N], ecnt;

inline void add_edge(int now, int to){
	ecnt ++; 
	e[ecnt].to = to;
	e[ecnt].next = ehead[now]; 
	ehead[now] = ecnt;
}
// Edge End

// Segment Start

struct node{
	long long k, d, t;
}tree[N << 2];

inline void poshdown(int now){
	if( tree[now].t || tree[now].k || tree[now].d ){
		tree[now << 1].t += (tree[now].t + tree[now].d * tree[now << 1].k); 
		tree[now << 1].k += tree[now].k; 
		tree[now << 1].d += tree[now].d;
		tree[now << 1 | 1].t += (tree[now].t + tree[now].d * tree[now << 1 | 1].k); 
		tree[now << 1 | 1].k += tree[now].k; 
		tree[now << 1 | 1].d += tree[now].d;
		tree[now] = (node){0, 0, 0};
	}
}

void query_add(int from, int to, long long val, int now = 1, int left = 1, int rig = idcnt){
	if(from <= left && rig <= to){
		tree[now].k += val;
		return ;
	}
	pushdown(now);
	int mid = (left + rig) >> 1;
	if(from <= mid) query_add(from, to, val, now << 1, left, mid);
	if(to > mid) query_add(from, to, val, now << 1 | 1, mid + 1, rig);
	return ;
}

void query_mul(int from, int to, long long val, int now = 1, int left = 1, int rig = idcnt){
	if(from <= left && rig <= to){
		tree[now].d += val;
		tree[now].t += val * tree[now].k;
		return ;
	}
	pushdown(now);
	int mid = (left + rig) >> 1;
	if(from <= mid) query_mul(from, to, val, now << 1, left, mid);
	if(to > mid) query_mul(from, to, val, now << 1 | 1, mid + 1, rig);
	return ;
}

void query_sum(int from, int to, int now = 1, int left = 1, int rig = idcnt){
}
// Segment End

// Heavy - Light Decopostion Start
int idcnt, id[N], dep[N], fa[N], son[N], top[N], mson[N];
void dfs1(int now, int la, int depth){
	fa[now] = la; dep[now] = depth;
	son[now] = 1;
	for(int i = ehead[now]; i; i = e[i].next){
		if( e[i].to == la ) 
			continue;
		dfs1(e[i].to, now, depth + 1);
		son[now] += son[ e[i].to ];
		if( son[ e[i].to ] > son[ mson[now] ] )
			mson[now] = e[i].to;
	}
}

void dfs2(int now, int la){
	id[now] = ++ idcnt;
	if(top[now] == 0)
		top[now] = now;
	if(mson[now] == 0)
		return ;
	top[ mson[now] ] = top[now];
	dfs2(mson[now], now);
	for(int i = ehead[now]; i; i = e[i].next){
		if( e[i].to == la || e[i].to == mson[now] )
			continue;
		dfs2(e[i].to, now);
	}
}
// Heavy - Light Decopostion End

int main(){
	scanf("%d", &n);
	for(int i = 1, u, v; i < n; i++){
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	int m, op, x, y;
	scanf("%d", &m);
	while( m -- ){
		scanf("%d", &op);	
		if( op == 1 ){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		else if( op == 2 ){
			scanf("%d%d", &x, &y);
			mul(x, y);
		}
		else if( op == 3 ){
			scanf("%d", &x);
			printf("%d\n", query(x));
		}
	}
}
