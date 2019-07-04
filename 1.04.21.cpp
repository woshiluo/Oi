#include <stdio.h>
int main() {
	long long n,x,y,z;
	scanf("%lld %lld %lld",&n,&x,&y);
	z=n-(float)y/x;
	if(z<0) z=0;
	printf("%lld",z);
	return 0;
}
