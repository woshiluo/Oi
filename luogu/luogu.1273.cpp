#include <cstdio>
#include <cstring>

const int N=3100;

inline int Max(int a,int b){return a>b?a:b;}

int _case;
int ans,v,w,n,m,son[N];
int f[N][N];

// edge start
struct edge{
	int to,next,val;
}e[N];

int ehead[N],ecnt;

inline void add_edge(int now,int to,int val){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].val=val;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end
// dfs start 
void dfs(int now){
	if(now>n-m){
		son[now]=1;
		return ;
	}
	f[now][0]=0;
	for(int u=ehead[now];u;u=e[u].next){
		dfs(e[u].to);
		for(int i=son[now];i>=0;i--){
			for(int j=1;j<=son[e[u].to];j++){
				f[now][i+j]=Max(f[now][i+j],f[now][i]+f[e[u].to][j]-e[u].val);
			}
		}
		son[now]+=son[e[u].to];
	}	  
}
// dfs end
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-m;i++){
		scanf("%d",&_case);
		while(_case--){
			scanf("%d%d",&v,&w);
			add_edge(i,v,w);
		}
	}
	memset(f,-0x3f,sizeof(f));
	for(int i=1;i<=m;i++) scanf("%d",&f[n-m+i][1]);
	dfs(1);
	for(int i=1;i<=m;i++){
		if(f[1][i]>=0) ans=i;
	}
	printf("%d",ans);
}
