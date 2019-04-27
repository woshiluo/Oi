#include <cstdio>
#include <cstring>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 60;

int n, m;
int f[N][N], g[N][N];
bool vis[N][N];

bool pd(int now){
	if(now == 0)
		return 0;
	while(now != 1){
		if(now & 1)
			return false;
		now >>= 1;
	}
	return true;
}

void dfs(int now, int start, int val){
	if(vis[start][now])
		return ;
	vis[start][now] = true;	
	if( pd(val) )
		g[start][now] = g[now][start] = 1;
	for(int i = 1; i <= n; i++){
		if(f[now][i] == 1)
			dfs(i, start, val + 1);
	}
}

int main(){
#ifdef woshiluo
	freopen("luogu.1613.in", "r", stdin);
	freopen("luogu.1613.out", "w", stdout);
#endif
	memset(f, 0x3f, sizeof(f));
	memset(g, 0x3f, sizeof(g));
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v; i <= m; i++){
		scanf("%d%d", &u, &v);
		f[u][v] = f[v][u] = 1;
	}
	for(int i = 1; i <= n; i++){
		dfs(i, i, 0);
	}
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(f[i][j]) 
				g[i][j] = 1;
		}
	}

	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				g[i][j] = Min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}
	printf("%d", g[1][n]);
}
