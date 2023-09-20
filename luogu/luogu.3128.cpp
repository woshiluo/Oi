#include <cstdio>
using namespace std;

inline int Max(int a,int b){return a>b?a:b;}

const int N=51000;

int x,y,n,k;

// edge start
struct edge{
	int next,to;
}e[N<<1];
int ehead[N],ecnt;
// edge end

inline void add_edge(int now,int to){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end

// Heavy-Light Decompostion start
int dep[N],son[N],mson[N],fa[N];
void find_son(int now,int la,int depth){
	fa[now]=la;
	dep[now]=depth;
	mson[now]=0;
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].to==la) continue;
		find_son(e[i].to,now,depth+1);
		son[now]+=son[e[i].to]+1;
		if(son[e[i].to]>son[mson[now]]) mson[now]=e[i].to;
	}
}

int id[N],top[N],idcnt;
void get_edge(int now,int la){
	id[now]=++idcnt;
	if(top[now]==0) top[now]=now;
	if(son[now]==0) return ;
	top[mson[now]]=top[now];
	get_edge(mson[now],now);
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].to==la||e[i].to==mson[now]) continue;
		get_edge(e[i].to,now);
	}
}
// Heavy-Light Decompostion end
// Segment Tree start
int tree[N<<2],lazy[N<<2];

inline void pushup(int now){
	tree[now]=Max(tree[now<<1],tree[now<<1|1]);
}

inline void pushdown(int now){
	if(lazy[now]){
		tree[now<<1]+=lazy[now];
		tree[now<<1|1]+=lazy[now];
		lazy[now<<1]+=lazy[now];
		lazy[now<<1|1]+=lazy[now];
		lazy[now]=0;
	}	
}

inline void query_add(int now,int left,int rig,int from,int to,int val){
	if(from<=left&&rig<=to){
		tree[now]+=val;
		lazy[now]+=val;
		return ;
	}
	int mid=(left+rig)>>1;
	pushdown(now);
	if(from<=mid) query_add(now<<1,left,mid,from,to,val);
	if(to>mid) query_add(now<<1|1,mid+1,rig,from,to,val);
	pushup(now);
}

inline int query_Max(int now,int left,int rig,int from,int to){
	if(from<=left&&rig<=to) return tree[now];
	int mid=(left+rig)>>1,res=-1;;
	pushdown(now);
	if(from<=mid) res=Max(res,query_Max(now<<1,left,mid,from,to));
	if(to>mid) res=Max(res,query_Max(now<<1|1,mid+1,rig,from,to));
	pushup(now);
	return res;
}
// Segment Tree end
// Answer start
inline void change(int from,int to,int val){
	while(top[from]!=top[to]){
		if(dep[top[from]]<dep[top[to]]){
			int tmp=to;
			to=from;
			from=tmp;
		}
		query_add(1,1,n,id[top[from]],id[from],val);
		from=fa[top[from]];
	}
	if(id[from]>id[to]){
		int tmp=to;
		to=from;
		from=tmp;
	}
	query_add(1,1,n,id[from],id[to],val);
}
// Answer end


int main(){
	son[0]=-1;
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	find_son(1,0,1);
	get_edge(1,0);
	while(k--){
		scanf("%d%d",&x,&y);
		change(x,y,1);
	}
	printf("%d",query_Max(1,1,n,1,n));
}
