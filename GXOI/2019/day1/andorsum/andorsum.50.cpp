#include <cstdio>

const int N = 1100;
const int mod = 1e9 + 7;

int n, and_sum, or_sum;
int sum[N][N][32];

int main(){
	freopen("andorsum.in", "r", stdin);
	freopen("andorsum.out", "w" ,stdout);
	scanf("%d", &n);
	for(int i = 1, tmp; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &tmp);

			for(int k = 0; k < 7; k++){
				sum[i][j][k] = sum[i - 1][j][k] + sum[i][j - 1][k] + ( (tmp >> k) & 1) - sum[i - 1][j - 1][k];
			}
		}
	}

	for(int i = 1, tmp, mat, tmp_and, tmp_or; i <= n; i++){
		for(int j = 1; j <= n; j++){
			for(int x = i;  x <= n; x++){
				for(int y = j; y <= n; y++){
					mat = (y - j + 1) * (x - i + 1);	
					tmp_and = tmp_or = 0;
					for(int k = 0; k < 7; k++){
						tmp = (sum[x][y][k] - sum[x][j - 1][k] - sum[i - 1][y][k] + sum[i - 1][j - 1][k]);
						if(tmp != 0)
							tmp_or += (1 << k);
						if(tmp == mat) 
							tmp_and += (1 << k);
					}
					tmp_and %= mod;
					tmp_or %= mod;
					and_sum = (and_sum + tmp_and) % mod;
					or_sum = (or_sum + tmp_or) % mod;
				}
			}
		}
	}
	printf("%d %d", and_sum, or_sum);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
