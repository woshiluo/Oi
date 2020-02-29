#include <cstdio>

inline int Min(int a, int b) {return a < b? a: b;}

const int N = 1e7 + 10;

int T, n, m, pcnt;
long long ans;
bool vis[N + 10];
int mu[N + 10], f[N + 10], smu[N + 10], pri[N + 10];

void pre(){
	mu[1] = vis[1] = 1;;
	for(int i = 2; i <= N; i++){
		if( vis[i] == false ){
			pri[ ++pcnt ] = i;
			mu[i] = -1; f[i] = 1;
		}
		for(int j = 1; j <= pcnt; j++){
			if( i * pri[j] > N ) 
				break;
			vis[ i * pri[j] ] = true;	
			if(i % pri[j] == 0){
				f[ i * pri[j] ] = mu[i];
				mu[ i * pri[j] ] = 0;
				break;
			}
			f[ i * pri[j] ] = -f[i] + mu[i];
			mu[ i * pri[j] ] = -mu[i];
		}	
	}
	for(int i = 1; i <= N; i++)
		smu[i] = smu[i - 1] + f[i];
	
}

int main(){
	pre();
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		if(n > m) {int tmp = m; m = n; n = tmp;}
		for(int left = 1, rig; left <= n; left = rig + 1){
			rig = Min( n / (n / left), m / (m / left));	
			ans += 1LL * (smu[rig] - smu[left - 1]) * (n / left) * (m / left);
		}
		printf("%lld\n", ans);
		ans = 0;
	}
}
