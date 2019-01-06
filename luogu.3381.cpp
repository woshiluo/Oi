#include <cstdio>
#include <cstring>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 5100;
const int M = 51000;
const int INF = 0x3f3f3f3f;

int n, m, s, t, u, v, w, f, now, Maxflow, Mincost;

// edge start 
struct edge{
	int next, to, flow, val;
}e[M << 1];
int ehead[N], ecnt;
inline void add_edge(int now, int to, int flow, int val){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].flow=flow;
	e[ecnt].val=val;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end
// spfa start 
int head, tail;
int q[N * 30], dis[N], pre[N], cur[N], flow[N];
bool vis[N];
inline bool spfa(){
	memset(vis, 0, sizeof(INF));
	memset(flow, INF, sizeof(INF));
	memset(dis, INF, sizeof(INF));
	head = tail = 0;
	q[head] = s;vis[s] = true;

	while(head <= tail){
		for(int i = ehead[ q[head] ]; i; i = e[i].next){
			if(e[i].val > 0 && dis[now] + e[i].val < dis[ e[i].to ]){
				dis[ e[i].to ] = dis[now] + e[i].val;
				cur[now] = i;
				pre[ e[i].to ] = now;
				flow[ e[i].to ] = Min(flow[now], e[i].val);
				if(!vis[ e[i].to ]){
					vis[ e[i].to ] = true;
					q[++tail] = e[i].to;
				}
			}
		}
		head++;
	}
	return pre[t] != 0;
}
// spfa end
inline void MCMF(){
	while( spfa() ){
		Maxflow += flow[t];
		Mincost += flow[t] * dis[t];
		now = t;
		while(now != s){
			e[ cur[now] ].flow -= flow[t];
			e[ cur[now] + ( cur[now] & 1? -1: 1) ].flow += flow[t];
			now = pre[now];
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("luogu.3381.in", "r", stdin);
	freopen("luogu.3381.out", "w", stdout);
#endif
	scanf("%d%d%d%d",&n, &m, &s, &t);
	for(int i = 1;i <= m; i++){
		scanf("%d%d%d%d", &u, &v, &w, &f);        
		add_edge(u, v, w, f);
		add_edge(u, v, 0, -f);
	} 
	MCMF();
	printf("%d %d", Maxflow, Mincost);
}
