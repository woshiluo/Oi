#include <cstdio>
#include <cmath>

const long long mod=1000003;

long long sum,ans,n;

inline long long lowbit(long long x){return x&(-x);}

inline long long ksm(long long a,long long p){
	long long res=1,base=a;	
	while(p){
		if(p&1) res=(res*base)%mod;
		base=(base*base)%mod;
		p>>=1;
	}
	return res;
}

long long dfs(long long now){
	long long tmp=lowbit(now);
	if(tmp==now){
		ans=ksm(3,(std::log(now)/std::log(2)));
		return 2; 
	}
	else{
		long long tmp1=dfs(now-tmp);
		ans=(ans+tmp1*ksm(3,(std::log(tmp)/std::log(2))))%mod;
		return tmp1*2;
	}
}

int main(){
	scanf("%lld",&n);
	dfs(n);
	if(n%2==0) sum=(((1+n)%mod)*((n/2)%mod))%mod;
	else sum=((((1+n)/2)%mod)*(n%mod))%mod;
	//sum=((((1+n)*n)%mod)*ksm(2,mod-2))%mod;
	//printf("%lld\n%lld",sum,sum-ans);
	printf("%lld",((sum-ans)%mod+mod)%mod);
}
