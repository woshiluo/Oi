#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 50000;

int T, n, m, pcnt;
long long ans;
bool vis[N + 100];
int pri[N + 100], d[N + 100], min_p[N + 100], smu[N + 100], mu[N + 100], sum_d[N + 100];

void pre(){
	vis[1] = 1; mu[1] = d[1] = 1;
	for(int i = 2; i <= N; i++){
		if( vis[i] == false ){
			pri[ ++pcnt ] = i;
			mu[i] = -1;
			d[i] = 2;
			min_p[i] = 1;
		}
		for(int j = 1; j <= pcnt; j++){
			if( pri[j] * i > N ) 
				break;
			vis[ i * pri[j] ] = true;
			if( i % pri[j] == 0 ){
				mu[ pri[j] * i ] = 0;
				min_p[ pri[j] * i ] = min_p[i] + 1;	
				d[ pri[j] * i ] = d[i] / (min_p[i] + 1) * (min_p[i] + 2);
				break;
			}
			else {
				mu[ pri[j] * i ] = -mu[i];	
				d[ pri[j] * i ] = d[i] << 1;
				min_p[ pri[j] * i ] = 1;
			}
		}
	}
	for(int i = 1; i <= N; i++) 
		smu[i] = smu[i - 1] + mu[i];
	for(int i = 1; i <= N; i++)
		sum_d[i] = sum_d[i - 1] + d[i];	
}

int main(){
#ifdef woshiluo
	freopen("luogu.3327.in", "r", stdin);
	freopen("luogu.3327.out", "w", stdout);
#endif
	pre();
	scanf("%d", &T);
	while(T--){
		ans = 0;
		scanf("%d%d", &n, &m);
		if(n > m){ int tmp = n; n = m; m = tmp; }
		for(int left = 1, rig; left <= n; left = rig + 1){
			rig = Min(n / (n / left), m / (m / left));
			ans += 1LL * (smu[rig] - smu[left - 1]) * sum_d[ n / left ] * sum_d[ m / left ];
		}
		printf("%lld\n", ans);
	}
}
