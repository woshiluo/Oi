#include <cstdio>
#include <cmath>

long long n,m,k,l;

int main(){
	scanf("%lld%lld%lld%lld",&n,&m,&k,&l);
	if(k+l>n||m>n) printf("-1");
	else {
		if((k+l)%m==0) printf("%lld",(k+l)/m);
		else if((((k+l)/m)+1)*m>n) printf("-1");
		else printf("%lld",(k+l)/m+1);
	}
}
