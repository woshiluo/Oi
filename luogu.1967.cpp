#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

const int N=11000;
const int M=51000;
const int Q=31000;

inline int Min(int a,int b){return a>b?a:b;}

// node start
struct node{
	int now,to,val;	
}te[M<<1];

bool cmp(node a,node b){
	return a.val>b.val;
}
// node end
// edge start
struct edge{
	int to,val,next;
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


// fa start
int fa[N];
int get_fa(int now){
	if(fa[now]==now) return now;
	return fa[now]=get_fa(fa[now]);
}
// fa end
int n,m;

inline void kruskal(){
	std::sort(te+1,te+m+1,cmp);
	for(int i=1;i<=m;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		int fn=get_fa(te[i].now),ft=get_fa(te[i].to);
		if(fn!=ft){
			add_edge(te[i].now,te[i].to,te[i].val);
			add_edge(te[i].to,te[i].now,te[i].val);
			fa[ft]=fn;
		}
	}
}

int fat[N][30],st[N][30];

void dfs(int now,int la){
	fat[now][0]=la;
	for(int i=1;i<=20;i++){
		fat[now][i]=fat[fat[now][(1<<(i-1))-1]][1];
	}
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].to==la) continue;
		dfs(e[i].to,now);
	}
}

int get_lca(int from,int to){
	if(from==to) return from<=to;	
	for(int i=30;i>=1;i--){
		
	}
}

int main(){
	memset(st,0x3f,sizeof(st));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d",&te[i].now,&te[i].to,&te[i].val);
	}
	kruskal();
	for(int i=1;i<=n;i++){
		if(fa[i]==i){
			add_edge(i,n+1,-1);
			add_edge(n+1,i,-1);
		}
	}
	dfs(n+1,-1);
}
