#include <cstdio>
using namespace std;

const long long N=110000;

long long n,m,op,x,y,z;
long long a[N];

// Segment_Tree start
struct Segment_Tree{
	long long tree[N<<2],lazy[N<<2];	
	
	inline void push_up(long long now){
		tree[now]=tree[now<<1]+tree[now<<1|1];
	}
	
	inline void push_down(long long now,long long lson,long long rson){
		if(lazy[now]){
			lazy[now<<1]+=lazy[now];
			lazy[now<<1|1]+=lazy[now];
			tree[now<<1]+=1LL*lson*lazy[now];
			tree[now<<1|1]+=1LL*rson*lazy[now];
			lazy[now]=0;
		}
	}

	void build_tree(long long now,long long left,long long rig){
		if(left==rig){
			tree[now]=a[left];
			return ;
		}
		build_tree(now<<1,left,(left+rig)>>1);
		build_tree(now<<1|1,((left+rig)>>1)+1,rig);
		push_up(now);
	}

	void query_add(long long now,long long left,long long rig,long long from,long long to,long long val){
		if(from<=left&&rig<=to){
			tree[now]+=1LL*(rig-left+1)*val;
			lazy[now]+=val;
			return ;
		}
		long long mid=(left+rig)>>1;
		push_down(now,mid-left+1,rig-mid);
		if(from<=mid) query_add(now<<1,left,mid,from,to,val);
		if(to>mid) query_add(now<<1|1,mid+1,rig,from,to,val);
		push_up(now);
	}

	long long query_sum(long long now,long long left,long long rig,long long from,long long to){
		if(from<=left&&rig<=to) return tree[now];
		long long mid=(left+rig)>>1;long long res=0;
		push_down(now,mid-left+1,rig-mid);
		if(from<=mid) res+=query_sum(now<<1,left,mid,from,to);
		if(to>mid) res+=query_sum(now<<1|1,mid+1,rig,from,to);
		return res;
	}
}T;
// Segment_Tree end

int main(){
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);

	T.build_tree(1,1,n);

	while(m--){
		scanf("%lld",&op);
		if(op==1){
			scanf("%lld%lld%lld",&x,&y,&z);
			T.query_add(1,1,n,x,y,z);
		}
		if(op==2){
			scanf("%lld%lld",&x,&y);
			printf("%lld\n",T.query_sum(1,1,n,x,y));
		}
	}
}
