#include <cstdio>

int n, k;
int ans;

int main(){
	scanf("%d%d", &n, &k);	
	ans = (n << 1);	
	ans += n;
	ans += (k - 1) < (n - k)? (k - 1): (n - k);
	printf("%d", ans);
}
