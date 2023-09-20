#include <cstdio>
using namespace std;

long long n;
long long ans[1100000],acnt;

int main(){
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	scanf("%lld",&n);
	long long temp1=n/2+1;
	for(long long i=1;i<=temp1;i++){
		if((n-i)%i==0&&((n-i)/i)%2==0) ans[acnt++]=i;
	}
	printf("%lld ",acnt);
	for(long long i=acnt-1;i>=0;i--) printf("%lld ",n-ans[i]);
	fclose(stdin);
	fclose(stdout);
}
