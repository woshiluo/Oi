#include <cstdio>
#include <cstring>

inline int Min(int a,int b){return a<b?a:b;}

const int N=110;
const int M=1100;
const int INF=2147483647;

int n,m,u,v;
int son[N],f[N][N][N];
bool vis[N];

// edge start
struct edge{
	int to,next,val,un;
}e[M<<1];

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
// Dinic start 
namespace Dinic{
	int depth[N],q[N],cur[N];
	int head,tail,s,t; 
	bool bfs(){
		memset(depth,0,sizeof(depth));
		head=tail=0;
		q[head]=s;
		depth[s]=1;
		while(head<=tail){
			for(int i=ehead[q[head]];i;i=e[i].next){
				if(e[i].val&&depth[e[i].to]==0){
					depth[e[i].to]=depth[q[head]]+1;
					q[++tail]=e[i].to;
				}
			}
			head++;
		}
		if(depth[t]==0) return false;
		else return true;
	}
	
	int dfs(int now,int dist){
		if(now==t) return dist;
		for(int& i=cur[now];i;i=e[i].next){
			if(e[i].val>0&&depth[e[i].to]==depth[now]+1){	
				int di=Min(e[i].val,dist);
				e[i].val-=di;
				e[e[i].un].val+=di;
				if(di>0) dfs(e[i].to,di);
			}
		} 
		return 0;
	}
	
	inline int dinic(){
		int ans=0;
		while(bfs()){
			for(int i=1;i<=n;i++) cur[i]=ehead[i];
			while(int d=dfs(s,INF)) ans+=d; 
		}
		return ans;
	}	
}
// Dinic end
// dfs start
void dfs(int now){
	vis[now]=true;
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].un<=i) continue;
		if(son[e[i].to]==0&&vis[e[i].to]==false) dfs(e[i].to);
		son[now]+=son[e[i].to]+1; 
		e[i].val=son[e[i].to]+1;
	}
	if(son[now]==0){
		add_edge(now,n+2,INF,1);
		add_edge(n+2,now,-INF,-1);
	}
} 
// dfs end
int main(){
	freopen("orz.in","r",stdin);
	freopen("orz.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v,0,1);
		add_edge(v,u,0,-1);
		vis[v]=true;
	}
	for(int i=1;i<=n;i++) 
		if(vis[i]==false){
			add_edge(n+1,i,0,1);
			add_edge(i,n+1,0,-1);
		}
	memset(vis,0,sizeof(vis));
	dfs(n+1);
	Dinic::s=n+1;Dinic::t=n+2;
	printf("%d",Dinic::dinic());
}
