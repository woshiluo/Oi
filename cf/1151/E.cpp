#include <cstdio>

const int N = 1e5 + 1e4;

int n;
int a[N];
long long ans;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	ans = 1LL * (n - a[n] + 1) * a[n];
	for(int i = 1; i < n; i++){
		if(a[i] < a[i + 1])
			ans += 1LL * (a[i + 1] - a[i]) * a[i];
		if(a[i] > a[i + 1])	
			ans += 1LL * (a[i] - a[i + 1]) * (n - a[i] + 1);
	}
	printf("%lld", ans);
}
