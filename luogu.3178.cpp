#include <cstdio>
using namespace std;

const long long N=110000;

long long n,m,u,v;
long long val[N];

// edge start
struct edge{
	long long to,next;
}e[N<<1];

long long ehead[N],ecnt;

inline void add_edge(long long now,long long to){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end
// Heavy-Light Docompostion start
long long dep[N],fa[N],son[N],mson[N];

void dfs1(long long now,long long la,long long depth){
	fa[now]=la;
	dep[now]=depth;
	long long Mson=-1;
	for(long long i=ehead[now];i;i=e[i].next){
		if(e[i].to==la) continue;
		dfs1(e[i].to,now,depth+1);
		son[now]+=son[e[i].to]+1;
		if(son[e[i].to]>Mson) {
			Mson=son[e[i].to];
			mson[now]=e[i].to;
		}
	}
}

long long nval[N],id[N],top[N],idcnt;

void dfs2(long long now,long long la){
	id[now]=++idcnt;
	nval[id[now]]=val[now];
	if(top[now]==0) top[now]=now; 
	if(son[now]==0) return ;
	top[mson[now]]=top[now];
	dfs2(mson[now],now);
	for(long long i=ehead[now];i;i=e[i].next){
		if(e[i].to==la||e[i].to==mson[now]) continue;
		dfs2(e[i].to,now);
	}
}
void print_tree(long long now,long long la){
	if(top[now]==now) printf("\n");
	printf("%lld ",now);
	if(son[now]==0) return ;
	print_tree(mson[now],now);
	for(long long i=ehead[now];i;i=e[i].next){
		if(e[i].to==la||e[i].to==mson[now]) continue;
		print_tree(e[i].to,now);
	}
}
// Heavy-Light Docompostion end 
// Segment Tree start
long long tree[N<<2],lazy[N<<2];

inline void pushup(long long now){
	tree[now]=tree[now<<1]+tree[now<<1|1];
}

inline void pushdown(long long now,long long lson,long long rson){
	if(lazy[now]!=0){
		lazy[now<<1]+=lazy[now];
		lazy[now<<1|1]+=lazy[now];
		tree[now<<1]+=lazy[now]*lson;
		tree[now<<1|1]+=lazy[now]*rson;
		lazy[now]=0;
	}
}

void build_tree(long long now,long long left,long long rig){
	if(left==rig){
		tree[now]=nval[left];
		return ;
	}
	build_tree(now<<1,left,(left+rig)>>1);
	build_tree(now<<1|1,((left+rig)>>1)+1,rig);
	pushup(now);
}

void query_add(long long now,long long left,long long rig,long long from,long long to,long long val){
	if(from<=left&&rig<=to){
		tree[now]+=val*(rig-left+1);
		lazy[now]+=val;
		return ;
	}
	long long mid=(left+rig)>>1;
	pushdown(now,mid-left+1,rig-mid);
	if(from<=mid) query_add(now<<1,left,mid,from,to,val);
	if(to>mid) query_add(now<<1|1,mid+1,rig,from,to,val);
	pushup(now);
	return ;
}

long long query_sum(long long now,long long left,long long rig,long long from,long long to){
	if(from<=left&&rig<=to) return tree[now];
	long long mid=(left+rig)>>1,res=0;
	pushdown(now,mid-left+1,rig-mid);
	if(from<=mid) res+=query_sum(now<<1,left,mid,from,to);
	if(to>mid) res+=query_sum(now<<1|1,mid+1,rig,from,to);
	pushup(now);
	return res;
}
// Segment Tree end
// ask answer start
inline long long find_ans(long long from,long long to){
	long long res=0;
	while(top[from]!=top[to]){
		if(dep[top[from]]<dep[top[to]]){
			long long tmp=to;
			to=from;
			from=tmp;
		}
		res+=query_sum(1,1,n,id[top[from]],id[from]);
		from=fa[top[from]];
	}
	if(id[from]>id[to]){
		long long tmp=to;
		to=from;
		from=tmp;
	}
	res+=query_sum(1,1,n,id[from],id[to]);
	return res;
}
// ask answer end
long long x,y,z;
int main(){
	freopen("luogu.3178.in","r",stdin);
	freopen("luogu.3178.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=n;i++) scanf("%lld",&val[i]);
	for(long long i=1;i<n;i++){
		scanf("%lld%lld",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0,1);
	dfs2(1,0);
	//print_tree(1,0);
	build_tree(1,1,n);
	while(m--){
		scanf("%lld",&x);
		if(x==1){
			scanf("%lld%lld",&y,&z);
			query_add(1,1,n,id[y],id[y],z);
		}
		else if(x==2){
			scanf("%lld%lld",&y,&z);
			query_add(1,1,n,id[y],id[y]+son[y],z);
		}
		else if(x==3) {
			scanf("%lld",&y);
			printf("%lld\n",find_ans(1,y));
		}
	}
	fclose(stdin);
	fclose(stdout);
}
