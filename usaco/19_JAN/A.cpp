#include <cstdio>

inline int Max(int a,int b){return a>b?a:b;}

const int N=1e5+1e4;

// edge start 
struct edge{
	int next, to;
}e[N << 1];
int ehead[N], ecnt;

inline void add_edge(int now, int to){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

int n, ans, max, u ,v;
int size[N];

int main(){
	freopen("planting.in","r",stdin);
	freopen("planting.out","w",stdout);
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		scanf("%d%d", &u, &v);
		size[u]++,size[v]++;
		max=Max(size[u],max);
		max=Max(size[v],max);

		add_edge(u ,v);
		add_edge(v ,u);
	}
	printf("%d",max+1);
}
