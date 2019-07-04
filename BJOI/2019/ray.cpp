#include <cstdio>

const int N = 5e5 + 1e4;
const int mod = 1e9 + 7;

inline int mul(int a, int b){return (1LL * a * b) % mod;}
inline int dec(int a, int b){a -= b; return a < 0? a + mod: a;}

int ksm(int a, int p = mod - 2){
	int res = 1;
	while(p){
		if(p & 1)
			res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
		p >>= 1;
	}
	return res;
}

int n;
int a[N], b[N], f[N], g[N];

int main(){
	scanf("%d", &n);
	int inv100 = ksm(100);
	for(int i = 1; i <= n; i++){
		scanf("%d%d", &a[i], &b[i]);
		a[i] = mul(inv100, a[i]);
		b[i] = mul(inv100, b[i]);
	}

	f[0] = 1;
	for(int i = 1, p; i <= n; i++){
		p = ksm( dec(1, mul(g[i - 1], b[i])) );	
		f[i] = mul(mul(f[i - 1], a[i]), p);
		g[i] = (b[i] + mul(mul(g[i - 1], mul(a[i], a[i])), p)) % mod;
	}
	printf("%d", f[n]);
}
