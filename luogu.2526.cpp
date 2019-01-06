#include <cmath>
#include <cstdio>
#include <cstring>

inline int Aabs(int a){return a>0?a:(0-a);}

const int N=110;
const int INF=0x7fffffff;

int n,m;
// node start 
struct node{
	int x,y,val,un;
}G[N],P[N];

inline double dis(node from,node to){
    return std::sqrt((from.x-to.x)*(from.x-to.x)+(from.y-to.y)*(from.y-to.y));		
}
// node end
// Dinic start
namespace Dinic{
	int s,t;
	int depth[N],que[N];
	
	inline bool bfs(){
		head=tail=0;
		memset(depth,0,sizeof(depth));
		while(head<=tail){
			for(int i=ehead[q[head]];i;i=e[i].next){
				if(depth[e[i].to]==0&&e[i].val>0){
					depth[e[i].to]=depth[q[head]]+1;
					q[++tail]=e[i].to;
				}
			}
			head++;
		}
		if(depth[t]==0) return false;
		return true;
	}

	inline int dinic(){
		int ans=0;
		while(bfs()){
			while(int d=dfs(s,INF)) ans+=d;
		}
		return ans;
	}
}
// Dinic end
// edge start 
struct edge {
	int next,to;
}e[N*N];
int ehead[N],ecnt;
inline void add_edge(int now,int to,int val,int un){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	e[ecnt].val=val;
	e[ecnt].un=ecnt+un;
	ehead[now]=ecnt;
}
// edge end

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&G[i].x,&G[i].y);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&P[i]);
		for(int j=1;j<=n;j++){
			if(dis(G[i]-P[j])<=dis(G[i+1]-G[i])){	
				add_edge(i,n+j,INF,1);
				add_edge(n+j,i,0,-1);
			}
		}
	}
}
