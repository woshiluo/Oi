#include <cstdio>

const int M = 5e5 + 1e4;
const int N = 3e5 + 1e4;

// edge start 
struct edge{
	int to, next;
}e[M];
int ehead[N], ecnt;
inline void add_edge(int now, int to){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

int n, m, u, v, ans;
int p[N], cnt[N];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d", &p[i]);	
	}
	while(m--){
		scanf("%d%d", &u, &v);
		add_edge(v, u);
	}
	for(int i = n; i >= 1; i--){
		if(cnt[ p[i] ] == n - i - ans && i != n)
			ans++;
		else 
			for(int o = ehead[ p[i] ]; o; o = e[o].next){
				cnt[ e[o].to ]++;
			}
	}
	printf("%d", ans);
}
