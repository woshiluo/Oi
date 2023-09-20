#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 1e7 + 1e5;
const int mod = 20101009;

int x, y, inv2, pcnt;
int pri[N], mu[N];
bool vis[N];

void pre(){
	inv2 = (mod + 1LL) / 2LL;
	mu[1] = 1; vis[1] = 1;
	for(int i = 2; i < N; i++){
		if(vis[i] == false){
			pri[ ++pcnt ] = i;
			mu[i] = -1;
		}
		for(int j = 1, tmp; j <= pcnt; j++){
			tmp = pri[j] * i;
			if(tmp > N)
				break;
			vis[tmp] = true;
			if(i % pri[j] == 0){
				mu[tmp] = 0;
				break;
			}
			mu[tmp] = -mu[i];
		}
		mu[i] = (mu[i - 1] + ( ( (1LL * i * i) % mod ) * mu[i]) % mod ) % mod;
	}
}

inline int sum(int left, int rig){
	return (((1LL * (rig - left + 1) * (left + rig)) % mod) * inv2) % mod;
}

int g(int n, int m){
	if(n > m){ int tmp = n; n = m; m = tmp; }
	int res = 0;
	for(int left = 1, rig; left <= n; left = rig + 1){
		rig = Min(n / (n / left), m / (m / left));	 
		res = (res + ( ( (1LL * (mu[rig] - mu[left - 1]) * sum(1, n / left) ) % mod) * sum(1, m / left) ) % mod) % mod;
	}
	return res;
} 

int calc(int n, int m){
	if(n > m){ int tmp = n; n = m; m = tmp; }
	int res = 0;
	for(int left = 1, rig; left <= n; left = rig + 1){
		rig = Min(n / (n / left), m / (m / left));
		res = (res + (1LL * sum(left, rig) * g(n/left, m/left)) % mod) % mod;
	}		
	return res;
}

int main(){
#ifdef woshiluo
	freopen("luogu.1829.in", "r", stdin);
	freopen("luogu.1829.out", "w", stdout);
#endif
	pre();
	scanf("%d%d", &x, &y);
	printf("%d\n", ( (calc(x, y) % mod) + mod) % mod);
}
