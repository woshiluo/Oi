#include <cstdio>
#include <cstring>

const int N = 11000;
const int M = 510000;

int n, m, s, u, v, w;

// edge start 
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
// edge end

// spfa start 
int q[N], dis[N];
bool vis[N];
int head, tail, head_dep, tail_dep;
inline void spfa(){
	head = tail = head_dep = tail_dep = 0;
	memset(dis, 0x3f, sizeof(dis));
	q[head] = s; dis[s] = 0;
	while( head_dep < tail_dep || (head_dep == tail_dep && head <= tail) ){
		for(int i = ehead[ q[head] ]; i; i = e[i].next){
			if(dis[ e[i].to ] > dis[ q[head] ] + e[i].val){
				dis[ e[i].to ] = dis[ q[head] ] + e[i].val;
				if(vis[ e[i].to ] == false){
					vis[ e[i].to ] = true;
					tail++;
					if( tail > n ) tail_dep++, tail = 0;
					q[tail] = e[i].to;
				}
			}	
		}	
		vis[ q[head] ] = false;
		head++;
		if(head > n ) head_dep++, head = 0;
	}
}
// spfa end

int main(){
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
	}
	spfa();
	for(int i = 1; i <= n; i++){
		if(dis[i] == 0x3f3f3f3f) printf("2147483647 ");
		else printf("%d ", dis[i]);
	}
}
