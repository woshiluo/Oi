#include <cstdio>

inline long long Min(long long a,long long b){return a<b?a:b;}
inline long long Max(long long a,long long b){return a>b?a:b;}

long long n,m;

int main(){
	scanf("%lld%lld",&n,&m);
	long long ans=0,ai=0;
	if(m==0) {
		printf("%lld %lld",n,n);
		return 0;
	}
	for(long long i=1;i<n;i++){
		ans+=i;
		ai=i+1;
		if(ans>=m){
			break;
		}
	}
	printf("%lld %lld",Max(n-2*m,0LL),Max(n-ai,0LL));
}
