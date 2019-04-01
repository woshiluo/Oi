#include <cstdio>
#include <cstring>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 210;
const int M = 2e4 + 1e3;
const int INF = (1<<30);

int n, m, sum;
int flow[N];

namespace Dinic{
	int start, end, head, tail;
	int dep[N << 1], que[N << 1];
	struct edge{
		int next, to, lower, flow;
	}e[M << 2];
	int ehead[N << 1], ecnt;
	inline void add_edge(int now, int to,int lower, int flow){
		ecnt++;
		e[ecnt].to = to;
		e[ecnt].lower = lower;
		e[ecnt].flow = flow; 
		e[ecnt].next= ehead[now];
		ehead[now] = ecnt;
	}
	bool bfs(){
		memset(dep, 0, sizeof(dep));
		head = tail = 0;	
		dep[ start ] = 1;
		que[ head ] = start;
		while( head <= tail ){
			for(int i = ehead[ que[ head ] ]; i; i = e[i].next){
				if( dep[ e[i].to ] == 0	&& e[i].flow > 0){
					dep[ e[i].to ] = dep[ que[head] ] + 1;
					que[ ++ tail ] = e[i].to;
				}
			}	
			head ++;
		}
		if( dep[ end ] == 0 )
			return false;
		return true;
	}
	int dfs(int now, int dist){
		if(now == end) return dist;
		int f, flow = 0;
		for(int i = ehead[now]; i; i = e[i].next){
			if(dep[ e[i].to ] == dep[now] + 1 && e[i].flow != 0){
				f = dfs(e[i].to, Min(dist, e[i].flow));
				if(f > 0){
					e[i].flow -= f;	
					e[i ^ 1].flow += f;
					flow += f;
					dist -= f;
				}
				if(dist == 0)
					return flow;
			}		
		}
		return flow;
	}
	int dinic(){
		int ans = 0;
		while( bfs() ){
			while(int d = dfs(start, INF)) 
				ans += d;
		}	
		return ans;
	}
}

int main(){
#ifdef woshiluo
	freopen("nova.103.in", "r", stdin);
	freopen("nova.103.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	Dinic::start = n + 1; Dinic::end = n + 2; Dinic::ecnt = 1;
	for(int i = 1, s, t, lower, upper; i <= m; i++){
		scanf("%d%d%d%d", &s, &t, &lower, &upper);
		flow[s] -= lower;
		flow[t] += lower;
		Dinic::add_edge(s, t, lower, upper - lower); 
		Dinic::add_edge(t, s, lower, 0);
	}
	for(int i = 1; i <= n; i++){
		if(flow[i] > 0){
			sum += flow[i];		
			Dinic::add_edge(Dinic::start, i, 0, flow[i]);
			Dinic::add_edge(i, Dinic::start, 0, 0);
		}	
		else {
			Dinic::add_edge(i, Dinic::end, 0, -flow[i]);
			Dinic::add_edge(Dinic::end, i, 0, 0);
		}
	}
	if( Dinic::dinic() != sum )
		printf("NO\n");
	else {
		printf("YES\n");
		for(int i = 2; i <= (m << 1); i += 2){ printf("%d\n", Dinic::e[i].lower + Dinic::e[i ^ 1].flow); }
	}
}
