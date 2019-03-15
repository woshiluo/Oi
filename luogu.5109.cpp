#include <cstdio>
#include <queue>
#include <cstring>

const int N = 2e5 + 1e4;
const int M = 4e5 + 1e4;

int T;
int n, m, u, v, l, a;

class kruskal_tree{
	public:
		int ecnt;
		struct edge_normal{
			int now, to, val, hei;	
			bool operator<(edge_normal b){
				return this -> hei > b.hei;
			}
		}e[M << 1];
		class Graph{
			public:
				int n;
				struct node{
					int dep, val;
					int fa[20];
				}nodes[N << 1];
				struct edge{
					int next, to, val;
				}e[M << 1];
				int ehead[N << 1], ecnt;
				inline void add_edge(int now, int to, int val = 0);
				inline void init();	
				void get_st();
		}G;
		inline void add_edge(int now, int to, int val, int hei);
		inline void get_pre(int n);
		inline void init();
		inline int build_tree(int n);
}Tree;

inline void kruskal_tree::Graph::init(){
	ecnt = 0;
	memset(ehead, 0, sizeof(ehead));
}

inline void kruskal_tree::init(){
	ecnt = 0;
	G.init();
}

inline void kruskal_tree::Graph::add_edge(int now, int to, int val){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	e[ecnt].val = val;
	ehead[now] = ecnt;
}

inline void kruskal_tree::add_edge(int now, int to, int val, int hei){
	e[++ecnt] = (edge_normal){now, to, val, hei};
}

inline void build_tree(int n){
	G.init();
	G.n = n;
	std::sort(	
}

inline void kruskal_tree::get_pre(int n){
	build_tree();	
}

inline void init(){
	Tree.init();	
}

void build_tree(){
	G.init();
}

void readin(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d%d", &u, &v, &l ,&a);	
		Tree.add_edge(u, v, l, a);
		Tree.G.add_edge(u, v, l);
	}
}

inline void dijrstra(){
	q.clear();
	memset(dis, 0x3f, sizeof(dis));	
	dis[1] = 0;q.push(
}

int main(){
#ifdef woshiluo
	freopen("luogu.5109.in", "r", stdin);
	freopen("luogu.5109.out", "w", stdout);
#endif
#ifndef woshiluo
	freopen("return.in", "r" , stdin);
	freopen("return.out", "w", stdout);
#endif	
	scanf("%d", &T);
	while(T--){
		init();		
		readin();
		dijrstra();
		Tree.get_pre(n);
	}
}
