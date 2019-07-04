#include <cstdio>
using namespace std;

long long n;
long long a,b,ans;

inline int Max(int a,int b){return a>b?a:b;}

inline int ask_sum(long long now){
	int cnt=0;	
	while(now){
		cnt+=now%10;
		now/=10;
	}
	return cnt;
}

int main(){	
	scanf("%lld",&n);	
	if(n<10){
		printf("%lld",n);
		return 0;
	}
	a=9,b=n-a;	
	while(a<=n){
		ans=Max(ans,ask_sum(a)+ask_sum(b));
		a=a*10+9;
		b=n-a;
	}
	printf("%lld",ans);
}
