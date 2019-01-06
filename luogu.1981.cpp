#include <cstdio>
using namespace std;


long long ans;
char x;

long long jf(long long);
long long xf(long long);

long long  cf(long long  temp2){
	long long  temp1;
	scanf("%lld",&temp1);
	scanf("%c",&x);
	long long ans=(temp1*temp2)%10000;
	if(x=='+') return jf(ans);
	if(x=='*') return cf(ans);
	return ans;
}

long long  jf(long long temp2){
	long long temp1;
	scanf("%lld",&temp1);
	scanf("%c",&x);
	ans=(temp1+temp2)%10000;
	if(x=='+') return jf(ans);
	if(x=='*') return temp2+cf(temp1);
	return ans;
}

int main(){
	long long temp1;
	scanf("%lld",&temp1);
	scanf("%c",&x);
	if(x=='+') ans=jf(temp1);
	else if(x=='*')ans=cf(temp1);
	else ans=temp1%10000;
	printf("%d",ans%10000);
}
