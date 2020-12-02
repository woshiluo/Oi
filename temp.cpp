#include<iostream>
#include<cstdio>
#include<cstring>
const int MAXN = 2e5 + 7;
const int P = 100003;
int n, k;
int a[MAXN], vis[MAXN];
int fac[MAXN], ifac[MAXN];
int f[MAXN];

inline int ksm(long long x, int y) {
	long long ans = 1;
	while(y) {
		if(y & 1)ans = ans * x % P;
		x = x * x % P;
		y >>= 1;
	}
	return ans;
}

inline void init() {
	fac[0] = ifac[0] = 1;
	ifac[1] = 1;
	for(int i = 1; i <= n; ++i)fac[i] = 1ll * fac[i - 1] * i % P;
	ifac[n] = ksm(fac[n], P - 2);
	for(int i = n - 1; i >= 2; --i)ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
	return ;
}

inline int ni(int x) {
	return 1ll * ifac[x] * fac[x - 1] % P;
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		vis[i] = a[i];
	}
	init();
	//printf("%d %d\n", fac[n], ifac[2]);
	int cnt = 0;
	for(int i = n; i >= 1; --i) {
		if(vis[i]) {
			for(int j = 1; j * j <= i; ++j) {
				if(i % j == 0) {
					vis[j] ^= 1;
					if(j != i / j)vis[i / j] ^= 1;
                    //判断原局面步数
				}
			}
			cnt++;
		}
	}
	if(k >= cnt)return printf("%lld\n", 1ll * cnt * fac[n] % P), 0;
	for(int i = n; i >= 1; --i) {
		f[i] = (n + (1ll * n - i) * f[i + 1]) * ni(i) % P;
		//printf("%d\n", f[i]);
	}//dp部分
	long long ans = k;
	for(int i = cnt; i > k; --i) {
		(ans += f[i]) %= P;
	}//统计答案
	printf("%lld\n", ans * fac[n] % P);
	return 0;
}
