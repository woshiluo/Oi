#include <cstdio>
#include <cmath>

int T;
long long a,b;

bool prime(long long now){
	long long tmp=std::sqrt(now);
	for(int i=2;i<=tmp+1;i++){
		if(now%i==0) return false;
	}
	return true;
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&a,&b);
		if(a-b!=1) printf("NO\n");
		else if(prime(a+b)) printf("YES\n");
		else printf("NO\n");
	}
}
