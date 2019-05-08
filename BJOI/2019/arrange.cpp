#include <cstdio>
#include <algorithm>

inline int Max(int a, int b) { return a > b ? a : b; }

const int N = 110;

int s, n, m;
int ans;
int wt[N][N], tmp_s[N], val[N][N];
int f[N][(N * N) << 2];

int main() {
    scanf("%d%d%d", &s, &n, &m);
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &wt[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= s; j++) {
            tmp_s[j] = (wt[j][i] << 1) + 1;
        }
        std::sort(tmp_s + 1, tmp_s + s + 1);
        for (int j = 1; j <= s; j++) {
            val[i][j] = tmp_s[j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k <= s; k++) {
                if (j - val[i][k] < 0)
                    break;
                f[i][j] = Max(f[i][j], f[i - 1][j - val[i][k]] + (i * k));
                ans = Max(ans, f[i][j]);
            }
        }
    }
    printf("%d", ans);
    fclose(stdin);
    fclose(stdout);
}

