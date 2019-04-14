#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 110;

int n, m, k;
int a[N], b[N], f[N][N], h[N][N];

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%d", &b[i]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &f[i][j]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			h[i][j] = f[i][j]? Min(a[j], b[i]): 0;	
		}	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++)
			printf("%d ", h[i][j]);
		printf("\n");
	}
}
