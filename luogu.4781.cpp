#include <cstdio>
#include <cmath>

const int N = 2100;
const int mod = 998244353;

struct node {
	int x, y;
} a[N];

int ans, n, k; 

int ksm(int now, int p) {
	int res = 1LL;
	while(p) {
		if( p & 1LL ) 
			res = (1LL * res * now) % mod;
		now = (1LL * now * now) % mod;
		p >>= 1LL;
	}
	return res;
}
inline int inv(int now) { return ksm(now, mod - 2LL); }

int main() {
#ifdef woshiluo
	freopen("luogu.4781.in", "r", stdin);
	freopen("luogu.4781.out", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) 
		scanf("%d%d", &a[i].x, &a[i].y);

	for(int i = 1, s1, s2; i <= n; i++) {
		// s1 / s2
		s1 = a[i].y % mod;
		s2 = 1;
		for(int j = 1; j <= n; j++) {
			if( i == j ) 
				continue;
			s1 = ( 1LL * s1 * (k - a[j].x) ) % mod;
			s2 = ( 1LL * s2 * (a[i].x - a[j].x) ) % mod; 
		}
		s1 = ( 1LL * s1 * inv(s2) ) % mod;
		ans = (ans + s1) % mod;
	}
	printf("%d", (ans + mod) % mod);
}
