#include <cstdio>

int T;
unsigned long long s,a,b,c;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%llu%llu%llu%llu",&s,&a,&b,&c);
		printf("%llu\n",(s/c)+((s/c/a*b)));
	}
}
