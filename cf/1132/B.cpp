#include <cstdio>
#include <algorithm>

inline bool cmp(int a, int b){
	return a > b;
}

const int N = 3e5 + 1e4;

long long n, m;
long long sum[N], a[N], q[N];

int main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
	}
	scanf("%lld", &m);
	for(int i = 1; i <= m; i++){
		scanf("%lld", &q[i]);
	}
	std::sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++){
		sum[i] = sum[i - 1] + a[i];	
	}
	for(int i = 1; i <= m; i++){
		printf("%lld\n", sum[n] - a[ q[i] ]);
	}
}
