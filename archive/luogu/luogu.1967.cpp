#include <cstdio>
#include <algorithm>

inline int Min(int a, int b) {return a < b? a: b;}

const int N = 11000;
const int M = 51000;
const int INF = 0x3f3f3f3f;

int n, m, q;
bool vis[N];

// edge start
struct edge{
	int to, val, next;
}e[N << 1];
int ehead[N], ecnt;

inline void add_edge(int now, int to, int val){
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

// kru start
int k_ecnt;
struct k_edge{
	int now, to, val;
	bool operator< (const k_edge &b)const { return this -> val > b.val; }
}k_e[M << 1];

struct _set{
	int fa[N];
	inline void init(int now){
		for(int i = 1; i <= now; i++)
			fa[i] = i;
	}
	int get_fa(int now){
		if( fa[now] == now )
			return now;
		return fa[now] = get_fa( fa[now] );
	}
	int& operator[] (int now) { return fa[now]; }
}set;

void kru(){
	set.init(n);
	std::sort(k_e + 1, k_e + k_ecnt + 1);
	for(int i = 1; i <= k_ecnt; i++){
		int tmp_now = set.get_fa( k_e[i].now ), tmp_to = set.get_fa( k_e[i].to );
		if( tmp_now != tmp_to ){
			add_edge(k_e[i].now, k_e[i].to, k_e[i].val);
			add_edge(k_e[i].to, k_e[i].now, k_e[i].val);
			set[ tmp_to ] = tmp_now;
		}
	}
}
// kru end

// st start
int dep[N], fa[N][21], Min_node[N][21];
void get_st(int now, int la){
	vis[now] = true;
	dep[now] = dep[la] + 1;
	fa[now][0] = la;

	for(int k = 1; k <= 20; k++){
		fa[now][k] = fa[ fa[now][ k - 1 ] ][ k - 1 ];
		Min_node[now][k] = Min(Min_node[now][ k - 1 ], Min_node[ fa[now][k - 1] ][ k - 1 ]);
	}

	for(int i = ehead[now]; i; i = e[i].next){
		if( e[i].to == la )
			continue;
		Min_node[ e[i].to ][0] = e[i].val;
		get_st(e[i].to, now);
	}
}
// st end

int query(int from, int to){
	int min = INF;

	if( dep[from] < dep[to] ) { int tmp = to; to = from; from = tmp; }
	for(int k = 20; k >= 0; k --){
		if(dep[ fa[from][k] ] >= dep[to]){
			min = Min(min, Min_node[from][k]);
			from = fa[from][k];
		}
	}
	if( from == to )
		return min; 
	for(int k = 20; k >= 0; k --){
		if(fa[from][k] != fa[to][k]){
			min = Min(min, Min(Min_node[from][k], Min_node[to][k]));
			from = fa[from][k];
			to = fa[to][k];
		}
	}
	min = Min(min, Min( Min_node[from][0], Min_node[to][0] ));
	return min;
}

int main(){
#ifdef woshiluo
	freopen("luogu.1967.in", "r", stdin);
	freopen("luogu.1967.out", "w" ,stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w; i <= m; i++){
		scanf("%d%d%d", &u, &v, &w);
		k_e[ ++ k_ecnt ] = (k_edge){u, v, w};
		k_e[ ++ k_ecnt ] = (k_edge){v, u, w};
	}
	kru();

	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			get_st(i, 0);
//			fa[i][0] = i; Min_node[i][0] = INF;
		}
	}

	scanf("%d", &q);

	int u, v;
	while( q -- ) {
		scanf("%d%d", &u, &v);
		if( set.get_fa(u) != set.get_fa(v) ){
			printf("-1\n");
			continue;
		}
		printf("%d\n", query(u, v));
	}
}
