#include <cstdio>
#include <cstring>

const int N=10000;
const int M=500000;

int n,m,s,u,v,w;
// edge start
struct edge {
	int to,next,val;
}e[M];
int ehead[N],ecnt;
inline void add_edge(int now,int to,int val){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].val=val;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end
// spfa start
int head,tail;
int q[N],dis[N];
bool vis[N];
void spfa(int now){
	head=tail=0;
	memset(dis,0x3f,sizeof(dis));
	dis[now]=0;
	vis[now]=true;
	q[head]=now;
	while(head<=tail){
		for(int i=ehead[q[head]];i;i=e[i].next){
			if(dis[q[head]]+e[i].val<dis[e[i].to]){
				dis[e[i].to]=dis[q[head]]+e[i].val;
				if(!vis[e[i].to]){
					vis[e[i].to]=true;
					q[++tail]=e[i].to;
				}
			}
		}
		vis[q[head]]=false;
		head++;
	}
}
// spfa end
int main(){
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
	}
	spfa(s);
	for(int i=1;i<=n;i++){
		if(dis[i]>=0x3f3f3f3f) printf("2147483647 ");
		else printf("%d ",dis[i]);
	}
}
