#include <cstdio>

const long long mod=1000000007;
const int N=110000;

int n,u,v;
long long f[N][2];

// edge start
struct edge{
	int next,to;
}e[N<<1];
int ehead[N],ecnt;
inline void add_edge(int now,int to){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end

void dfs(int now,int la){
	f[now][1]=1;
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].to==la) continue;
		dfs(e[i].to,now);
		f[now][0]=(f[now][0]+f[e[i].to][0]+f[e[i].to][1])%mod;
		f[now][1]=((1+f[e[i].to][1])*f[now][1])%mod;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("luogu.2796.in","r",stdin);
	freopen("luogu.2796.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	printf("%lld",(f[1][1]+f[1][0])%mod);
}
