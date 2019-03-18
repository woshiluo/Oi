#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 2e5 + 1e4;
const int M = 4e5 + 1e4;

struct que{
	int now, dis;	
	bool operator< (const node &b) const{
		return this -> dis > b.dis;
	}
}tmp;

struct edge{
	int to, val, next;
}e[M << 1];
int ehead[N], ecnt;

std::priority_queue<node> q;

// dijkstra start
int dis[N];
bool vis[N];
void dijkstra(){
	while( !q.empty() ) q.pop();	
	memset(vis, false, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	q.push( (que){1, 0} );
	while( !q.empty() ){
		tmp = q.top();
		q.pop();
		if( vis[ tmp.now ] )
			continue;
		for(int i = ehead[ tmp.now ]; i; i = e[i].next){
			if(dis[ tmp.now ] + e[i].val < dis[ e[i].to ]){
				dis[ e[i].to ] = dis[ tmp.now ] + e[i].val;
				if( vis[ e[i].to ] == false )
					q.push( (que){e[i].to, dis[ e[i].to ]} );
			}
		}
	}
}
// dijkstra end

// kurastra_tree start
struct kurastra_edge{
	int now, to, val;	
}kurastra_e[N];
void build_tree(){
	std::sort(kurastra_e + 1, kurastra_e + m + 1);	
	for(int i = 1; i <= m; i++){
		
	}	
}
// kurastra_tree end

inline void init(){
	memset(ehead, 0, sizeof(ehead));	
}

void readin(){
	scanf("%d%d", &n, &m); 
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d%d", &u, &v, &l, &a);
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		init();	
		readin();
		dijkstra();
		build_tree();
	}
}
