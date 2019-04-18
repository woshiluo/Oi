#include <cstdio>

const int N = 2e6 + 10;

int T, n;
int sum_mu[N], sum_mu2[3400];
int mu[N], phi[N], pri[N], pcnt;
int has_phi[3400], has_mu[3400];
long long sum_phi[N], sum_phi2[3400];
bool vis[N];

void pre(){
	vis[1] = true; mu[1] = 1; phi[1] = 1;
	sum_mu[1] = sum_phi[1] = 1;
	for(int i = 2; i < N; i++){
		if(vis[i] == false){
			pri[ ++pcnt ] = i;
			mu[i] = -1;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= pcnt; j++){
			int tmp = pri[j] * i;
			if(tmp >= N) 
				break;
			vis[tmp] = true;
			if(i % pri[j] == 0){
				mu[tmp] = 0;
				phi[tmp] = phi[i] * pri[j];
				break;
			}
			mu[tmp] = -mu[i];
			phi[tmp] = phi[i] * (pri[j] - 1);
		}
		sum_mu[i] = sum_mu[i - 1] + mu[i];
		sum_phi[i] = sum_phi[i - 1] + (long long)phi[i];
	}
}

long long ask_phi(int x){
	if(x < N) return sum_phi[x];
	int tmp = n / x;
	if(has_phi[tmp] == n)
		return sum_phi2[tmp];
	has_phi[tmp] = n;
	long long &ans = sum_phi2[tmp];
	ans = (1LL * (1LL + x) * x) / 2;
	for(int left = 2, rig; left <= x; left = rig + 1){
		rig = x / (x / left);
		ans -= (rig - left + 1) * ask_phi(x / left);
	}
	return ans;
}

int ask_mu(int x){
	if(x < N) return sum_mu[x];
	int tmp = n / x;
	if(has_mu[tmp] == n)
		return sum_mu2[tmp];
	has_mu[tmp] = n;
	int &ans = sum_mu2[tmp];
	ans = 1;
	for(int left = 2, rig; left <= x; left = rig + 1){
		rig = x / (x / left);
		ans -= (rig - left + 1) * ask_mu(x / left);
	}
	return ans;
}

int main(){
#ifdef woshiluo
	freopen("luogu.4213.in", "r", stdin);
	freopen("luogu.4213.out", "w" ,stdout);
#endif
	pre();
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		printf("%lld %d\n", ask_phi(n), ask_mu(n)); 
	}
	fclose(stdin);
	fclose(stdout);
}
