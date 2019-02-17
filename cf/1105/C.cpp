#include <cstdio>

const int N = 2e5 + 1e4;
const int MOD = 1e9 + 7;

int n, l, r;
long long f[N][3], mod[3];

int main(){
	scanf("%d%d%d", &n, &l, &r);
	mod[0] = r/3 - (l-1)/3;
	mod[1] = (r + 1)/3 - l/3;
	mod[2] = (r + 2)/3 - (l + 1)/3;
	f[0][0] = 1LL;
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				f[i][(k + j)% 3] = (f[i][(k + j) % 3] + f[i - 1][k] * mod[j] * 1LL) % MOD;
			}
		}
	}
	printf("%lld",f[n][0]);
}
