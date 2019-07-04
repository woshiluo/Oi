#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 51000;

int _case;
int n, m, pcnt;
long long ans;
bool vis[N + 20];
int pri[N + 20], mu[N + 20], smu[N + 20], d[N + 20], sum_d[N + 20], Min_pri[N + 20];

void pre(){
	mu[1] = 1; d[1] = 1; vis[1] = true;
	for(int i = 2; i <= N; i++){
		if( vis[i] == false ){
			pri[ ++pcnt ] = i;
			d[i] = 2; Min_pri[i] = 1;
			mu[i] = -1;
		}
		for(int j = 1; j <= pcnt; j++){
			if( pri[j] * i > N )
				break;
			vis[ pri[j] * i ] = true;
			if( i % pri[j] == 0 ){
				mu[ pri[j] * i ] = 0;	
				d[ pri[j] * i ] = d[i] / (Min_pri[i] + 1) * (Min_pri[i] + 2);
				Min_pri[ pri[j] * i ] = Min_pri[i] + 1;
			}
			else {
				mu[ pri[j] * i ] = -mu[i];
				d[ pri[j] * i ] = d[i] << 1;
				Min_pri[ pri[j] * i ] = 1;
			}
		}
	}
	for(int i = 1; i <= N; i++)
		smu[i] = smu[i - 1] + mu[i];
	for(int i = 1; i <= N; i++)
		sum_d[i] = sum_d[i - 1] + d[i];
}

int main(){
	pre();
	scanf("%d", &_case);
	while( _case -- ){
		scanf("%d%d", &n, &m);
		ans = 0;
		if(n > m) {int tmp = m; m = n; n = tmp;}
		for(int left = 1, rig; left <= n; left = rig + 1){
			rig = Min(n / (n / left), m / (m / left));	
			ans += 1LL * (smu[rig] - smu[left - 1]) * sum_d[n / left] * sum_d[m / left];
		}
		printf("%lld\n", ans);
	}
}
