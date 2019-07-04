#include <cstdio>
#include <algorithm>

const int N = 2e5 + 1e4;

int n, m, k, tmp;
long long ans;
int a[N];

bool cmp(int a, int b){
	return a > b;	
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);		
	}
	std::sort(a + 1, a + n + 1, cmp);
	if( m <= k ){
		printf("%lld", 1LL * a[1] * m);
		return 0;
	}
	else {
		ans = 1LL * a[1] * k + (long long) a[2];
		ans *= (m / (k + 1) );
		m %= (k + 1);
		ans += 1LL * a[1] * m;
		printf("%lld", ans);
	}
}
