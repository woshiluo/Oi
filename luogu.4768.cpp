#include <cstdio>
#include <algorithm>

const int N = 2e5 + 1e4;
const int M = 4e5 + 1e4;

int T, n, m;

// Edge Start
struct edge {
	int to, next, val;
}e[M << 1];
int ehead[N << 1], ecnt;

inline void add_edge(int now, int to, int val = 0) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

void edge_init(){
	ecnt = 0;
	memset(ehead, 0, sizeof(ehead));
}
// Edge End

// Kru Tree Start
struct k_edge {
	int now, to, val, hei;
	bool operator(k_edge b) { return this -> hei > b.hei; }
}k_e[M];

struct _set {
	int fa[N << 1];
	void init(int now) {
		now <<= 1;
		for(int i = 1; i <= now; i ++)
			fa[i] = i;
	}
	int get_fa(int now) {
		if( fa[now] == now )
			return now;
		return fa[now] = get_fa(fa[now]);
	}
	int& operator[] (int now) { return fa[now]; }
}set;

void kru_tree() {
	edge_init();
	set.init(n);
	std::sort(k_e + 1, k_e + m + 1);
	for(int i = 1; i <= m; i++) {
		int tmp_now = set.get_fa( k_e[i].now ), tmp_to = set.get_fa( k_e[i].to );
		if( tmp_now != tmp_to ) {
			n ++;
			add_edge(n, k_e[i].now);
			add_edge(n, k_e[i].to);
		}
	}
}
// Kru Tree End

// Dijkstra Start
struct node {
	int now, dis;
	bool operator< (node b) { return this -> val < b.val; }
};
priority_queue<node> q;

int dis[N << 1];
bool vis[N << 1:

void get_dis(){
	dis[1] = 0; vis[1] = true;
	q.push(1, 0);
	while( ! q.empty() ) {
		node top = q.top(); q.pop();
		for(int i = ehead[ top.now ]; i; i = e[i].next) {
			if( dis[now] + e[i].val < dis[ e[i].to ] ){
				dis[ e[i].to ] = dis[now] + e[i].val;
				if( vis[ e[i].to ] == false ) {
					vis[ e[i].to ] = true;
					q.push( (node){e[i].to, dis[ e[i].to ]} );
				}
			}
		}
	}
}
// Dijkstra End
void init() {
	edge_init();
}

void readin() {
	scanf("%d%d", &n, &m);
	for(int i = 1, v; i <= m; i++) {
		scanf("%d%d%d%d", &k_e[i].now, &k_e[i].to, &v, &k_e[i].hei);
		add_edge(k_e[i].now, k_e[i].to, v);
	}
}

int main() {
	scanf("%d", &T);
	while( T -- ) {
		init();
		readin();
		get_dis();
		kru_tree();

		get_st();
		work();
	}
}
