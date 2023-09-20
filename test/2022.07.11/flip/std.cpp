#include <stdio.h>
const int maxn = 3005, maxm = 5005, mod = 998244353;
int n, m, ans, tot;
int a[maxn], b[maxn], f[maxm][maxn][2];
int main() {
    freopen("flip.in","r",stdin);
    freopen("std.out","w",stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + 1; i++) scanf("%d", &a[i]), b[i] = a[i] ^ a[i - 1], tot += b[i];
    f[m][tot][1] = (m & 1) ? (mod - 1) : 1;
	for (int i = m; i >= 1; i--) {
		for( int j = 0; j <= n + 1; j ++ ) {
			printf( "%d %d\n", f[i][j][0], f[i][j][1] );
			for( int c = 0; c <= 1; c ++ )
				if (f[i][j][c]) {
					f[i - 1][j][c ^ 1] = (f[i - 1][j][c ^ 1] + 1ll * (i - 1) * f[i][j][c]) % mod;
					int v = mod - f[i][j][c];
					if (c == 0) {
						f[i - 1][j][1] = (f[i - 1][j][1] + 1ll * (n + 1) * n / 2 * v) % mod;
						continue;
					}
					if (j >= 2)
						f[i - 1][j - 2][1] = (f[i - 1][j - 2][1] + 1ll * j * (j - 1) / 2 * v) % mod;
					f[i - 1][j][1] = (f[i - 1][j][1] + 1ll * j * (n + 1 - j) * v) % mod;
					if (j + 2 <= n + 1)
						f[i - 1][j + 2][1] = (f[i - 1][j + 2][1] + 1ll * (n + 1 - j) * (n - j) / 2 * v) % mod;
				}
		}
		printf( "\n" );
	}
	printf("%d\n", f[0][0][1]);
	return 0;
}

