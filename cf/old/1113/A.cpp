#include <cstdio>

int n, v, la;
long long ans;

int main(){
	scanf("%d%d", &n, &v);	
	if( n - 1 <= v){
		printf("%d", n - 1);
		return 0;
	}
	la = v; ans = v;
	for(int i = 2; i <= n;i ++){
		ans += i;	
		if(v >= n - i) break;
	}
	printf("%lld", ans);
}
