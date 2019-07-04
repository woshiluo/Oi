#include <cstdio>
using namespace std;

const int N=100010;
const int M=100010;

int n,m,u,v,x,y,z;
int col[N],ncol[N];
char op[3];

// edge start
struct edge{
	int to,next;
}e[M<<1];
int ecnt,ehead[N];

inline void add_edge(int now,int to){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end
// Heavy-Light Docompostion start
int son[N],dep[N],mson[N],fa[N];
void dfs1(int now,int la,int depth){
	fa[now]=la;
	dep[now]=depth;
	int Max=-1;
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].to==la) continue;
		dfs1(e[i].to,now,depth+1);	
		son[now]+=son[e[i].to]+1;
		if(son[e[i].to]>Max){Max=son[e[i].to];mson[now]=e[i].to;}
	}
}

int id[N],top[N],idcnt;
void dfs2(int now,int la){
	id[now]=++idcnt;
	ncol[id[now]]=col[now];
	if(top[now]==0) top[now]=now;
	if(son[now]==0) return ;
	top[mson[now]]=top[now];
	dfs2(mson[now],now);
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].to==la||e[i].to==mson[now]) continue;
		dfs2(e[i].to,now);
	}
}

void print_tree(int now,int la){
	if(top[now]==now) printf("\n");	
	printf("%d ",now);
	if(son[now]==0) return ;
	top[mson[now]]=top[now];
	print_tree(mson[now],now);
	for(int i=ehead[now];i;i=e[i].next){
		if(e[i].to==la||e[i].to==mson[now]) continue;
		print_tree(e[i].to,now);
	}
}
// Heavy-Light Docompostion end
// Segment Tree start
struct T{
	int left,rig,colnum;
}tree[N<<2];
int lazy[N<<2];
inline void pushup(int now){
	tree[now].colnum=tree[now<<1].colnum+tree[now<<1|1].colnum;
	if(tree[now<<1].rig==tree[now<<1|1].left) tree[now].colnum--;
	tree[now].rig=tree[now<<1|1].rig;tree[now].left=tree[now<<1].left;
}
inline void pushdown(int now){
	if(lazy[now]!=0){
		tree[now<<1].left=tree[now<<1].rig=tree[now<<1|1].left=tree[now<<1|1].rig=lazy[now];
		tree[now<<1].colnum=tree[now<<1|1].colnum=1;
		lazy[now<<1]=lazy[now<<1|1]=lazy[now];
		lazy[now]=0;
	}
}
void build_tree(int now,int left,int rig){
	if(left==rig){
		tree[now].rig=tree[now].left=ncol[left];
		tree[now].colnum=1;
		return ;
	}
	build_tree(now<<1,left,(left+rig)>>1);
	build_tree(now<<1|1,((left+rig)>>1)+1,rig);
	pushup(now);
}
void change_col(int now,int left,int rig,int from,int to,int val){
	if(from<=left&&rig<=to){
		tree[now].rig=tree[now].left=val;
		tree[now].colnum=1;
		lazy[now]=val;
		return ;
	}
	pushdown(now);
	int mid=(left+rig)>>1;
	if(from<=mid) change_col(now<<1,left,mid,from,to,val);
	if(to>mid) change_col(now<<1|1,mid+1,rig,from,to,val);
	pushup(now);
}
int query_col(int now,int left,int rig,int from,int to){
	if(from<=left&&rig<=to) return tree[now].colnum;
	pushdown(now);
	int mid=(left+rig)>>1,res=0;
	if(from<=mid) res+=query_col(now<<1,left,mid,from,to);
	if(to>mid) res+=query_col(now<<1|1,mid+1,rig,from,to);
	if(from<=mid&&to>mid&&tree[now<<1].rig==tree[now<<1|1].left) res--;
	pushup(now);
	return res;
}

inline int find_col(int now,int left,int rig,int en){
	if(left==rig&&left==en) return tree[now].left;
	int mid=(left+rig)>>1;
	pushdown(now);
	pushup(now);
	if(en<=mid) return find_col(now<<1,left,mid,en);
	if(en>mid) return find_col(now<<1|1,mid+1,rig,en);
	return 0;
}
// Segment Tree end
// Answer start
inline void ask_change(int left,int rig,int col){
	while(top[left]!=top[rig]){
		if(dep[top[left]]<dep[top[rig]]){
			int tmp=left;
			left=rig;
			rig=tmp;
		}
		change_col(1,1,n,id[top[left]],id[left],col);
		left=fa[top[left]];
	}
	if(id[left]>id[rig]){
		int tmp=left;
		left=rig;
		rig=tmp;
	}
	change_col(1,1,n,id[left],id[rig],col);
}
inline int ask_colnum(int left,int rig){
	int res=0;
	while(top[left]!=top[rig]){
		if(dep[top[left]]<dep[top[rig]]){
			int tmp=left;
			left=rig;
			rig=tmp;
		}
		res+=query_col(1,1,n,id[top[left]],id[left]);
		int ta=find_col(1,1,n,id[top[left]]);
		int tb=find_col(1,1,n,id[fa[top[left]]]);
		if(ta==tb) res--;
		left=fa[top[left]];
	}
	if(id[left]>id[rig]){
		int tmp=left;
		left=rig;
		rig=tmp;
	}
	res+=query_col(1,1,n,id[left],id[rig]);
	return res;
}
// Answer end

int main(){
	freopen("luogu.2486.in","r",stdin);
	freopen("luogu.2486.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&col[i]);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0,1);
	dfs2(1,0);	
	build_tree(1,1,n);
	while(m--){
		scanf("%s",op);
		if(op[0]=='C'){
			scanf("%d%d%d",&x,&y,&z);
			ask_change(x,y,z);
		}
		else if(op[0]=='Q'){
			scanf("%d%d",&x,&y);
			printf("%d\n",ask_colnum(x,y));
		}
	}
	fclose(stdin);
	fclose(stdout);
	//print_tree(1,0);
}
