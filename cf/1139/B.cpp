#include <cstdio>

const int N = 2e5 + 1e4;

int n;
long long ans, a[N], la;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
	}
	ans = a[n]; la = a[n];
	for(int i = n - 1; i >= 1; i--){
		if(la){
			la--;
			la = la < a[i] ? la: a[i];
			ans += la;
		}
		else 
			break;
	}
	printf("%lld", ans);
}
