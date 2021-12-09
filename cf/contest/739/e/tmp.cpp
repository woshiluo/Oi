#include<bits/stdc++.h>
using namespace std;
typedef double db;
const int N=2020;
int n,a,b,cnta[N],cntb[N];
db s,eps=1e-10,dp[N],p[N],q[N];
inline void ck2(db ca,db cb){
	for(int i=1;i<=n;++i){
		dp[i]=dp[i-1],cnta[i]=cnta[i-1],cntb[i]=cntb[i-1];
		if(dp[i]<dp[i-1]+p[i]-ca-eps)
			dp[i]=dp[i-1]+p[i]-ca,cnta[i]=cnta[i-1]+1,cntb[i]=cntb[i-1];
		if(dp[i]<dp[i-1]+q[i]-cb-eps)   dp[i]=dp[i-1]+q[i]-cb,cntb[i]=cntb[i-1]+1,cnta[i]=cnta[i-1];
		if(dp[i]<dp[i-1]+p[i]-ca+q[i]-cb-p[i]*q[i]-eps)
			dp[i]=dp[i-1]+p[i]-ca+q[i]-cb-p[i]*q[i],cnta[i]=cnta[i-1]+1,cntb[i]=cntb[i-1]+1;   
	}
}
inline db ck1(db x){
	db l=0,r=1;
	for(int i=1;i<=50;++i){
		db mid=(l+r)/2;
		ck2(x,mid);
		if(cntb[n]>b)   l=mid;
		else    r=mid;
	}
	return l;
}
int main(){
	freopen( "e.in", "r", stdin );
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;++i)   scanf("%lf",&p[i]);
	for(int i=1;i<=n;++i)   scanf("%lf",&q[i]);
	db l=0,r=1;
	for(int i=1;i<=50;++i){
		db mid=(l+r)/2;
		s=ck1(mid);
		if(cnta[n]>a)   l=mid;
		else    r=mid;  
	}
	ck2(l,s);
	printf("%.5lf\n",dp[n]+l*a+s*b);
	return 0;
}
