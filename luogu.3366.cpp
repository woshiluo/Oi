#include <cstido>

const int N = 5100;
const int M = 210000;

// edge start 
struct edge{
	int to, next, val;	
}e[M << 1];
int ehead[N], ecnt;
inline void add_edge(int now, int to, int val){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

// prim start 
inline void prim(){
	
}
// prim end

int n, m, u, v, w;

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);	
		add_edge(v, u, w);	
	}	
	prim();
}
