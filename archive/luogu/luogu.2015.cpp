#include <cstdio>

const int N=210;

int n,q,u,v,w;
int f[N][N],son[N];

// edge start
struct edge{
	int to,next,val
}e[N<<1];
int ehead[N],ecnt;
inline void add_edge(int now,int to,int val){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	e[ecnt].val=val;
	ehead[now]=ecnt;
}
// edge end

void dfs1(int now,int la){
	son[now]=0;
	for(int i=ehead[now];i;i=e[i].next){
		if(la==e[i].to) continue;
		f[e[i].to][0]=e[i].val;
		dfs(e[i].to,now);
		for(int j=son[e[i].to];j>=0;j--){
			for(int k=1;k<=son[now];k++){
				f[now][j+k+1]=Max(f[now][j+k+1],f[now][k]+f[e[i].to][j]);
			}
		}	
	}	
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}	
	dfs(1,0);
	printf("%d",f[1][q]);
}
