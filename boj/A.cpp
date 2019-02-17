#include <cstdio>
#include <algorithm>

const int N = 1e5 + 1e4;

long long n, ans;
long long a[N];

int main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i += 2) ans += a[i + 1] - a[i];
	printf("%lld", ans);	
}
