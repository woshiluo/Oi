#include <cstdio>
#include <cstring>

inline int Min(int a,int b){return a<b?a:b;}

const int N = 5100;
const int M = 51000;
const int INF = 0x7f7f7f7f;

int n, m, s, t, u, v, w, f;

// edge start 
struct edgE{
	int to,next,flow,val;
}e[M<<1];
int ehead[N],ecnt;
inline void add_edge(int now, int to, int flow, int val){
	ecnt++;
	e[ ecnt ].to = to;
	e[ ecnt ].val = val;
	e[ ecnt ].flow = flow;
	e[ ecnt ].next = ehead[now];
	ehead[ now ] = ecnt;
}
// edge end
// MCMF start
int Maxflow, Mincost, head, tail, head_dep, tail_dep;
int flow[N], dis[N], cur[N], pre[N], q[N];
bool vis[N];
inline bool spfa(){
	memset(vis, false, sizeof(vis));
	memset(dis, 0x7f, sizeof(dis));
	head = tail = head_dep = tail_dep = 0;
	q[head] = s;vis[s] = true;dis[s] = 0;pre[t] = 0;flow[s] = INF;

	while(head <= tail || head_dep < tail_dep){
		for(int i = ehead[ q[head] ]; i; i = e[i].next){
			if(e[i].flow > 0 && dis[ q[head] ] + e[i].val < dis[ e[i].to ]){
				dis[ e[i].to ] = dis[ q[head] ] + e[i].val;
				cur[ e[i].to ] = i;
				pre[ e[i].to ] = q[head];
				flow[ e[i].to ] = Min(flow[ q[head] ], e[i].flow);
				if(!vis[ e[i].to ]){
					vis[ e[i].to ] = true;
					tail++;
					if(tail > n) tail=1, tail_dep++;
					q[ tail ] = e[i].to;
				
				}
			}
		}		
		vis[ q[head] ]= false;
		head++;
		if(head > n) head = 1, head_dep++;
	}
	return pre[t] != 0;	
}

inline void MCMF(){
	while( spfa() ){
		Maxflow += flow[t];
		Mincost += flow[t] * dis[t];
		int now = t;
		while(now != s){
			e[ cur[now] ].flow -= flow[t];
			e[ cur[now] + ( ( cur[now] & 1 )? 1: -1) ].flow += flow[t];
			now = pre[now];
		}
	}	
}
// MCMF end

int main(){	
#ifndef ONLINE_JUDGE 
	freopen("luogu.3381.in", "r", stdin);
	freopen("luogu.3381.out", "w", stdout);
#endif
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d%d", &u, &v, &w, &f);	
		add_edge(u, v, w, f);
		add_edge(v, u, 0, -f);
	}
	MCMF();
	printf("%d %d", Maxflow, Mincost);
}
