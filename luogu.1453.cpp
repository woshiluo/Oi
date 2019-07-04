#include <cstdio>
#include <cstring>

inline int Max(int a,int b){return a>b?a:b;}
inline int Min(int a,int b){return a<b?a:b;}

const int N=110000;

int n,u,v,start_x,start_y,start_edge,choose,ans;
int vis[N],p[N];
double k;

// edge start 
struct edge{
	int to,next;
}e[N<<1];

int ehead[N],ecnt;

inline void add_edge(int now,int to){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end
// find cycle start
int dfn[N],low[N],time;
void tarjan(int x,int fa){
    dfn[x]=low[x]=++time;
    for(int i=ehead[x];i;i=e[i].next)    {
        if(e[i].to==fa) continue;
        if(!dfn[e[i].to]){
            tarjan(e[i].to,x);
            low[x]=Min(low[x],low[e[i].to]);
            if(low[e[i].to]<=dfn[x]){
				start_x=x;
				start_y=e[i].to;
				start_edge=i;
			}
        }
        else low[x]=Min(low[x],dfn[e[i].to]);
    }
}
// find cycle end
// dfs start 

int f[N][2];
// 0 use
// 1 unuse
void dfs(int now,int la){
	if(now!=choose) f[now][0]=p[now];
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].to==la||i==start_edge||(e[i].to==start_x&&now==start_y)||(e[i].to==start_y&&now==start_x)) continue;
		dfs(e[i].to,now);
		if(e[i].to!=choose) f[now][1]+=Max(f[e[i].to][1],f[e[i].to][0]);
		else f[now][1]+=f[e[i].to][1];
		if(now!=choose) f[now][0]+=f[e[i].to][1];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	scanf("%lf",&k);
	tarjan(0,-1);
	//printf("%d %d\n",start_x,start_y);
	choose=start_y;
	dfs(start_x,-1);
	ans=Max(f[start_x][0],f[start_x][1]);
	memset(f,0,sizeof(f));
	choose=start_x;
	dfs(start_y,-1);
	ans=Max(f[start_y][0],f[start_y][1]);
	memset(f,0,sizeof(f));
	printf("%.1lf",ans*k);
}
