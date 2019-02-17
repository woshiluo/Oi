#include <cstdio>
#include <cstring>

inline int Max(int a, int b){return a > b? a: b;}
inline int Min(int a, int b){return a < b? a: b;}

const int N = 410;
const int M = 210;
const int INF = 0x3f3f3f3f;

// edge start 
struct edge{
	int to, next, flow, cost;
}e[( (N * M) << 1) + (N << 1) + (M << 1)];
int ecnt, ehead[ N + M + 10];
inline void add_edge(int now, int to, int flow, int cost){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].flow = flow;
	e[ecnt].cost = cost;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

int n, m, tmp, s, t;

int head, tail, head_dep, tail_dep, Maxcost, Maxflow;
int flow[N + M + 10], dis[N + M + 10], la[N + M + 10], cur[N + M + 10],que[N + M + 10];
bool vis[N + M + 10];
inline bool spfa(){
	memset(dis, -INF, sizeof(dis));	
	memset(vis, false, sizeof(vis));
	head = tail = head_dep = tail_dep = 0;
	dis[s] = 0;que[head] = s;flow[s] = INF;vis[s] = true;la[t] = 0; 
	
	while((head <= tail && head_dep == tail_dep) || head_dep < tail_dep){
		for(int i = ehead[ que[head] ]; i; i = e[i].next){
			if(e[i].flow > 0 && dis[ que[head] ] + e[i].cost > dis[ e[i].to ]){
				dis[ e[i].to ] = dis[ que[head] ] + e[i].cost;	
				flow[ e[i].to ] = Min(flow[ que[head] ], e[i].flow);
				la[ e[i].to ] = que[head];
				cur[ e[i].to ] = i;	
				if(!vis[ e[i].to ]){
					vis[ e[i].to ] = true; 
					tail++;
					if(tail > n + m + 5) tail = 1, tail_dep++;
					que[ tail ] = e[i].to;
				}
			}
		}	
		vis[ que[head] ] = false;
		head++;
		if(head > n + m + 6) head = 1, head_dep++;
	}
	return la[t] != 0;
}

inline void MCMF(){
	while( spfa() ){
		Maxcost += dis[t] * flow[t];
		Maxflow += flow[t];
		int now = t;
		while(now != s){
			e[ cur[now] ].flow -= flow[t];
			e[ cur[now] + ( (cur[now] & 1)? 1: -1) ].flow += flow[t]; 
			now = la[now];
		}
	}	
}

int main(){
	scanf("%d%d", &n, &m);	
	s = (n + m) +2; t = (n + m) + 4;
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &tmp);
			add_edge(i, m + j, 1, tmp);	
			add_edge(m + j, i, 0, -tmp);	
		} 
	}
	for(int i = 1; i <= m; i++){
		scanf("%d",&tmp);
		add_edge(s, i, 1, 0);
		add_edge(i, s, 0, 0);
		add_edge(s, i, 1, -tmp);
		add_edge(i, s, 0, tmp);
	}
	for(int i = 1; i <= n; i++){
		add_edge(i + m, t, 1, 0);
		add_edge(t, i + m, 0, 0);
	}
	MCMF();
	printf("%d",Maxcost);
}
