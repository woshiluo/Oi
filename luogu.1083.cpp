#include <cstdio>

inline int Min(int a,int b){return a<b?a:b;}

const int N=1100000;

int n,m;
int d,s,t;

// Segment start
int tree[N<<2],lazy[N<<2];
inline void pushup(int now){
	tree[now]=Min(tree[now<<1],tree[now<<1|1]);
}

inline bool pushdown(int now){
	if(!lazy[now]){
		tree[now<<1]+=lazy[now];
		tree[now<<1|1]+=lazy[now];
		lazy[now<<1]+=lazy[now];
		lazy[now<<1|1]+=lazy[now];
		if(tree[now<<1]<0||tree[now<<1|1]<0) return false;
		lazy[now]=0;
	}
	return true;
}

void build_tree(int now,int left,int rig){
	if(left==rig){
		scanf("%d",&tree[now]);	
		return ;
	}
	build_tree(now<<1,left,(left+rig)>>1);
	build_tree(now<<1|1,((left+rig)>>1)+1,rig);
	pushup(now);
}

inline bool query_add(int now,int left,int rig,int from,int to,int val){
	if(from<=left&&rig<=to){
		tree[now]+=val;
		lazy[now]+=val;
		return tree[now]>=0;
	}
	if(pushdown(now)==false) return false;
	int mid=(left+rig)>>1;
	if(from<=mid) if(query_add(now<<1,left,mid,from,to,val)==false) return false;
	if(to>mid) if(query_add(now<<1|1,mid+1,rig,from,to,val)==false) return false;
	pushup(now);
	return tree[now]>=0;
}
// Setment end

int main(){
	scanf("%d%d",&n,&m);
	build_tree(1,1,n);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&d,&s,&t);
		if(query_add(1,1,n,s,t,(0-d))==false){
			printf("-1\n%d",i);
			return 0;
		}
	}
	printf("0");
}
