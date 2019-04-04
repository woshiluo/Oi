#include <cstdio>

int n;
long long ans;

int main(){
	scanf("%d", &n);
	for(int left = 1, rig; left <= n; left = rig + 1){
		rig  = n / (n / left);
		ans += 1LL * (n / left) * (rig - left + 1);
	}
	printf("%lld", ans);
}
