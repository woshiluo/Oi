#include <cstdio>

inline int Max(int a,int b){return a>b?a:b;}

const int N=6100;

int n,u,v;
int ha[N],low[N];

// edge start
struct edge{
	int next,to;
}e[N];
int ehead[N],ecnt;
inline void add_edge(int now,int to){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end
// dp start
int f[N][2];
// 0 use 
// 1 unuse
void dfs(int now){
	f[now][0]=ha[now];
	for(int i=ehead[now];i;i=e[i].next){
		dfs(e[i].to);
		f[now][0]=Max(f[now][0],f[now][0]+f[e[i].to][1]);
		f[now][1]=Max(f[now][1],Max(f[now][1]+f[e[i].to][0],f[now][1]+f[e[i].to][0]));
	}
}
// dp end 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&ha[i]);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		low[u]++;
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++){
		if(low[i]==0){
			dfs(i);
			printf("%d",Max(f[i][0],f[i][1]));
			break;
		}
	}
}
