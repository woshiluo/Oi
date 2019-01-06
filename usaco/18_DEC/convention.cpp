#include <cstdio>
#include <algorithm>

const int N=1e5+1e4;
const int INF=0x7fffffff;

inline int Min(int a,int b){return a<b?a:b;}

int n,m,c,l,r,mid,ans;
int a[N];

int pd(int now){
	int tmp=m,la=1;
	for(int i=1;i<=n;i++){
		if(tmp<=0) return -INF;
		if(i-la>=c) {tmp--;{if(tmp==0) return -INF;};la=i;continue;}
		if(a[i]-a[la]>now) {tmp--;{if(tmp==0) return -INF;}la=i;continue;}
	}
	return now;
}

int main(){
	freopen("convention.in","r",stdin);
	freopen("convention.out","w",stdout);

	scanf("%d%d%d",&n,&m,&c);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	std::sort(a+1,a+n+1);

	l=1,r=a[n];ans=pd((l+r)>>1);
	while(l<=r){
		mid=(l+r)>>1;	
		if(pd(mid)<0) l=mid+1;
		else r=mid-1;
		if(pd(mid)>0) ans=Min(ans,mid);
	}
	printf("%d",ans);
}
