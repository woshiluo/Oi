#include <cstdio>
#include <map>

const long long N = 8000000;

long long mod, inv_2, inv_6, pcnt;
long long pri[N + 10];
long long phi[N + 10];
bool vis[N + 10];
std::map<long long, long long> S;

long long sum(long long n){
	n %= mod;
	return (((n * (n + 1LL)) % mod) * inv_2) % mod;
}

long long sum_2(long long n){
	n %= mod;
	return (((((n * (n + 1LL)) % mod) * (n + n + 1LL)) % mod) * inv_6) % mod;
}

long long ksm(long long a, long long p){
	long long res = 1LL;
	while(p){
		if(p & 1LL)
			res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
		p >>= 1LL;
	}
	return res;
}

void pre(){
	vis[1] = true; phi[1] = 1LL; 
	for(long long i = 2LL; i < N; i++){
		if(vis[i] == false){
			pri[ ++pcnt ] = i;
			phi[i] = i - 1LL;
		}
		for(long long j = 1LL; j <= pcnt; j++){
			long long tmp = pri[j] * i;
			if(tmp > N) 
				break;
			vis[tmp] = true;
			if(i % pri[j] == 0LL){
				phi[tmp] = (phi[i] * pri[j]) % mod;
				break;
			}
			phi[tmp] = (phi[i] * (pri[j] - 1LL))% mod;
		}
	}
	for(long long i = 1LL; i < N; i++)
		phi[i] = (phi[i - 1LL] + ((((1LL * phi[i] * i) % mod) * i) % mod)) % mod;
}

long long ask_S(long long n){
	if(n < N) 
		return phi[n];
	if(S[n]) 
		return S[n];
	long long &ans = S[n];
	ans = sum(n);
	ans = (ans * ans) % mod;
	for(long long left = 2LL, rig; left <= n; left = rig + 1LL){
		rig = n / (n / left);
		ans = (ans - (ask_S(n / left) * ((sum_2(rig) - sum_2(left - 1LL) % mod))) % mod) % mod;	
	}
	return ans;
}

int main(){
#ifdef woshiluo
	freopen("luogu.3768.in", "r", stdin);
	freopen("luogu.3768.out", "w", stdout);
#endif
	long long n, ans = 0LL;
	scanf("%lld%lld", &mod, &n);
	pre();
	inv_2 = ksm(2LL, mod - 2LL);
	inv_6 = ksm(6LL, mod - 2LL);
	for(long long left = 1LL, rig, tmp; left <= n; left = rig + 1LL){
		rig = n / (n / left);
		tmp = sum(n / left);
		tmp = (tmp * tmp) % mod;
		ans = ((ans + (((ask_S(rig) - ask_S(left - 1LL)) % mod)) * tmp) % mod) % mod;
	}
	printf("%lld", (ans + mod) % mod);
	fclose(stdin);
	fclose(stdout);
}
