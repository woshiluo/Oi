#include <cstdio>

inline int Min(int a, int b) {return a < b? a: b;}

const int N = 50000 + 100;

int T, pcnt;
int a, b, c, d, k;
long long ans;
bool vis[N + 10];
int mu[N + 10], smu[N + 10], pri[N + 10];

void pre(){
	vis[1] = 1; mu[1] = 1;
	for(long long i = 2; i <= N; i++){
		if( vis[i] == false ){ pri[ ++pcnt ] = i; mu[i] = -1; }
		for(long long j = 1; j <= pcnt; j++){
			if(i * pri[j] > N) 
				break;
			vis[ i * pri[j] ] = true;
			if( i % pri[j] == 0 ){
				mu[ i * pri[j] ] = 0;
				break;
			}
			mu[ i * pri[j] ] = -mu[i];
		}
	}
	for(int i = 1; i <= N; i++)
		smu[i] = smu[i - 1] + mu[i];
}

long long calc(int a, int b, int d = k){
	ans = 0;
	if(a > b) {int tmp = b; b = a; a = tmp;}
	for(int left = 1, rig; left <= a; left = rig + 1){
		rig = Min(a / (a / left), b / (b / left));
		ans += 1LL * (smu[rig] - smu[left - 1]) * (a / (left * d)) * (b / (left * d));
	}
	return ans;
}

int main(){
#ifdef woshiluo
	freopen("luogu.2522.in", "r", stdin);
	freopen("luogu.2522.out", "w", stdout);
#endif
	pre();
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);	
		printf("%lld\n", calc(b, d) - calc(b, c - 1) - calc(a - 1, d) + calc(a - 1, c - 1));
	}
}

