#include <cstdio>

inline int Min(int a,int b){return a<b?a:b;}

int n,k,tt,ans,at,tmp,ae;
int a[110000];
int que[110000],head,tail;

// Segment tree start
int tree[410000];
inline void pushup(int now){tree[now]=Min(tree[now<<1],tree[now<<1|1]);}
void add(int now,int left,int rig,int no,int val){
	if(left==rig&&rig==no) tree[now]+=val;
	int mid=(left+rig)>>1;
	if(mid<=no) add(now<<1,left,mid,no,val);
	if(no>mid) add(now<<1|1,mid+1,rig,no,val); 
	pushup(now);
}
int query_sum(int now,int left,int rig,int from,int to){
	if(left<=from&&to<=rig){
		return tree[now];	
	}
	int res=0,mid=(left+rig)>>1;
	if(left<=mid) res+=query_sum(now<<1,left,mid,from,to);
	if(rig>mid) res+=query_sum(now<<1|1,mid+1,rig,from,to);
	return res;
}
// Segment tree end

int main(){	
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&tmp);
		add(1,1,n,tmp,i);
		tt=query_sum(1,1,n,1,n);
		if((i-tt+1)<(ae-at+1)){
			ae=i;
			at=i;
		}
	}	
	printf("%d %d",at,ae);
}
