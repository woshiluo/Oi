#include <cstdio>
#include <algorithm>

const int N = 11000;
const int M = 51000;

int n, m, q;
int val[N << 2];

// Edge Start
struct edge {
	int to, next;
}e[N << 2];
int ehead[N << 1], ecnt;

inline void add_edge(int now, int to){
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

// Kru_tree Start
struct k_edge {
	int now, to, val;
	bool operator< (k_edge b) {
		return this -> val > b.val;
	}
}k_e[M];

struct _set{
	int fa[N << 1];
	void init(int now) {
		now <<= 1;
		for(int i = 1; i <= now; i++)
			fa[i] = i;
	}
	int get_fa(int now) {
		if( fa[now] == now )
			return now;
		return fa[now] = get_fa( fa[now] );
	}
	int& operator[] (int now) { return fa[now]; }
}set;

void kru_tree() {
	set.init(n);
	std::sort( k_e + 1, k_e + m + 1 );
	for(int i = 1; i <= m; i ++ ) {
		int tmp_now = set.get_fa( k_e[i].now ), tmp_to = set.get_fa( k_e[i].to );
		if( tmp_now != tmp_to ) {
			n ++;
			val[n] = k_e[i].val;
			add_edge(n, tmp_to);
			add_edge(tmp_to, n);
			add_edge(n, tmp_now);
			add_edge(tmp_now, n);
			set[tmp_to] = n;
			set[tmp_now] = n;
		}
	}
}
// Kru_tree End

int fa[N << 1][21], dep[N << 1];
bool vis[N << 1];
void get_st(int now, int la) {
	vis[now] = true;
	dep[now] = dep[la] + 1;
	fa[now][0] = la;

	for(int k = 1; k <= 20; k ++) 
		fa[now][k] = fa[ fa[now][ k - 1 ] ][ k - 1 ];

	for(int i = ehead[now]; i; i = e[i].next) {
		if( e[i].to == la )
			continue;
		get_st(e[i].to, now);
	}
}

int query(int from, int to){
	if( set.get_fa(from) != set.get_fa(to) )
		return -1;
	if( dep[from] < dep[to] ) {
		int tmp = to; to = from; from = tmp;
	}
	
	for(int k = 20; k >= 0; k --) {
		if( dep[ fa[from][k] ] >= dep[to] )
			from = fa[from][k];
	}
	
	if(from == to) 
		return val[from];

	for(int k = 20; k >= 0; k --) {
		if( fa[from][k] != fa[to][k] ) {
			from = fa[from][k];
			to = fa[to][k];
		}
	}
	return val[ fa[from][0] ];
}

int main() {
#ifdef woshiluo
	freopen("luogu.1967.retree.in", "r", stdin);
	freopen("luogu.1967.retree.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w; i <= m; i ++) {
		scanf("%d%d%d", &u, &v, &w);	
		k_e[i] = (k_edge){u, v, w};
	}
	kru_tree();
	
	for(int i = n; i >= 1; i --) {
		if( vis[i] == false ) 
			get_st(i, i);
	}

	scanf("%d", &q);

	int u, v;
	while( q -- ) {
		scanf("%d%d", &u, &v);
		printf("%d\n", query(u, v));
	}
}
