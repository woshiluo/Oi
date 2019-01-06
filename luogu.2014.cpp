#include <cstdio>

const int N=310;

inline int Max(int a,int b){return a>b?a:b;}

int n,m,v;
int sc[N];

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
int f[N][N];
int dfs(int now){
	int son=1,nson;	
	f[now][1]=sc[now];
	for(int u=ehead[now];u;u=e[u].next){
		nson=dfs(e[u].to);
		for(int i=son;i>=1;i--){
			for(int j=1;j<=nson;j++){
				f[now][i+j]=Max(f[now][i+j],f[now][i]+f[e[u].to][j]);
			}
		}		
		son+=nson;
	}
	return son;
}
// dp end
int main(){
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n+1;i++){
		scanf("%d%d",&v,&sc[i]);
		v++;
		add_edge(v,i);
	}
	dfs(1);
	printf("%d",f[1][m+1]);
}
