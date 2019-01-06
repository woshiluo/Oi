#include <cstdio>
#include <cmath>

inline int Min(int a,int b){return a<b?a:b;}

const int N=110000;

int n,k,tmp;
int p[N],cnt;
long long ans;

inline void init(){
	tmp=Min((int)std::sqrt(k)+1,k/2);
	for(int i=1;i<=tmp;i++) if(k%i==0) p[++cnt]=i;
//	if(p[cnt]!=tmp) p[++cnt]=tmp;
}

inline long long dc(int l,int r){
	if(l==r) return 0;
	return (l+r)*(r-l+1)>>1;
}

int main(){
	scanf("%d%d",&n,&k);
	init();
	for(int i=2;i<=cnt;i++){
		ans+=(dc((p[i]+1)%k,((p[i]+1)%k)+p[i]-p[i-1]-1));	
	}
	if(tmp!=p[cnt]) ans+=dc(0,tmp-p[cnt]);
	if(k/2+1==tmp) tmp=k/2+2;
	else tmp=k/2+1;
	ans+=dc(0,k-tmp);
	ans+=k*(n-k>0?n-k:0);
	printf("%lld",ans);
}
