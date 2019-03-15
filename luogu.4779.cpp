#include <cstdio>
#include <queue>
#include <cstring>

const int N = 1e5 + 1e4;
const int M = 2e5 + 1e4;

struct edge{
	int to, next, val;
}e[M];
int ehead[N], ecnt;

inline void add_edge(int now, int to, int val){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

struct node{
	int now, val;
	bool operator< (const node &b) const{
		return this -> val > b.val;
	}
}tmp;

std::priority_queue<node> q;

int n, m, s, u, v, w;

int dis[N];
bool vis[N];
void dijkstra(int start){
	memset(dis, 0x3f, sizeof(dis));
	dis[start] = 0;
	q.push( (node){s, 0} );
	while( !q.empty() ){
		tmp = q.top(); q.pop();
		if(vis[ tmp.now ]) 
			continue;
		vis[ tmp.now ] = true;
		for(int i = ehead[ tmp.now ]; i; i = e[i].next){
			if(dis[ e[i].to ] > dis[ tmp.now ] + e[i].val){
				dis[ e[i].to ] = dis[ tmp.now ] + e[i].val;
				if( vis[ e[i].to ] == false )
					q.push( (node){e[i].to, dis[ e[i].to ]} );
			}
		}
	}
}

int main(){
#ifdef woshiluo
	freopen("luogu.4779.in", "r", stdin);
	freopen("luogu.4779.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d", &u, &v, &w);	
		add_edge(u, v, w);
	}
	dijkstra(s);
	for(int i = 1; i <= n; i++)
		printf("%d ", dis[i]);
}
