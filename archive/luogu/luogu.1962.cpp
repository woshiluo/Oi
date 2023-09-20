#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;

struct matrix {
	int f[N][N];
	matrix(int tmp) {
		memset(f, 0, sizeof(f));
		if(tmp) {
			for(int i = 1; i <= n; i++) 
				f[i][i] = tmp;
		}
	}
	matrix operator* (matrix b) {
		matrix ans(0);
		for(int i = 1; i <= 3; i++) {
			for(int j = 1; j <= 3; j++) {
				for(int k = 1; k <= 3; k++)
					ans[i][j] = (ans[i][j] + (this -> a[i][k] * b[k][j]) ) % mod;
			}
		}
	}
}

int T, n;

int main() {
	scanf("%d%d", &T, &n);
	while( T -- ) {
	}
}
