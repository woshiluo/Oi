#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int M=110000;
const int CN=5100;
const int N=51000;

double tval;
int n,m,u,v,w,s,t;
int temp,tc;
int col[N],pr[CN];

// edge start
struct edge{
	int to,next,val;
}e[M<<1];
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
struct mu{
	int l,r;
}dis[N];
bool vis[N];
struct que{
	int now,l,r;
}q[M<<2];
int head,tail;
inline void spfa(int now){
	head=tail=0;
	for(int i=1;i<=n;i++){
		dis[i].l=0;
		dis[i].r=0x3fffffff;
	}
	q[head].now=now;
	q[head].r=0;
	q[head].l=0x3fffffff;
	dis[now].l=dis[now].r=0;
	vis[now]=true;
	while(head<=tail){
		for(int i=ehead[q[head].now];i;i=e[i].next){
			if(col[q[head].now]==col[e[i].to]) tval=(double)e[i].val*(double)pr[col[e[i].to]]/100.0;
			else tval=(double)e[i].val*(double)(((double)pr[col[e[i].to]]+(double)pr[col[q[head].now]])/2.0)/100.0;
			que tmp=q[head];
			if(tval<tmp.l) tmp.l=(int)tval;
			if(tval>tmp.r) tmp.r=(int)ceil(tval);
			if(tmp.l>dis[e[i].to].l){
				tmp.now=e[i].to;
				dis[e[i].to].l=tmp.l;
				dis[e[i].to].r=tmp.r;
				if(!vis[e[i].to]){
					vis[e[i].to]=true;
					q[++tail]=tmp;
				}
			}
			else if(tmp.l==dis[e[i].to].l&&tmp.r<dis[e[i].to].r){
				tmp.now=e[i].to;
				dis[e[i].to].l=tmp.l;
				dis[e[i].to].r=tmp.r;
				if(!vis[e[i].to]){
					vis[e[i].to]=true;
					q[++tail]=tmp;
				}
			}
		}
		vis[q[head].now]=now;
		head++;
	}
}
// spfa end
int main(){
	freopen("trip.in","r",stdin);
	freopen("trip.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&temp);
		while(temp--){
			scanf("%d",&tc);
			col[tc]=i;
		}
	}
	for(int i=1;i<=n;i++) scanf("%d",&pr[i]);
	scanf("%d%d",&s,&t);
	spfa(s);
	printf("%d %d",dis[t].l,dis[t].r);
	fclose(stdin);
	fclose(stdout);
}
