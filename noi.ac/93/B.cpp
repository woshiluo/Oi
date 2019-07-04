#include <cstdio>
 
const int N = 110000;
const long long mod = 998244353;

long long ksm(long long a, long long p){
	if(p == 0LL) 
		return 1LL;
	long long res = 1LL;
	while(p){
		if(p & 1LL) 
			res = (res * a) % mod;
		a = (a * a) % mod;
		p >>= 1LL;
	}
	return res;
}

// edge start 
// edge end

int n, t_fa, cnt;
long long ans;

int main(){
	scanf("%d", &n);	
	ans = 1;
	for(int i = 1; i < n; i++){
		ans = (ans * 257933LL + (i + 1)) % mod;
		printf("%lld\n", ans);
	}
}
