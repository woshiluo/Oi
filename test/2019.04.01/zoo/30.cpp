#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}
inline int Max(int a, int b){return a > b? a: b;}

int n, m, ans;

namespace point_30{
	const int N = 210;	
	
	int f[N][N], vis[N][N];
	void calc(){
		for(int i = 1; i <= n; i++){ vis[i][i] = true; scanf("%d" ,&f[i][i]);	}
		for(int i = 1, u, v; i <= m; i++){
			scanf("%d%d", &u, &v);	
			f[u][v] = f[v][u] = Min(f[u][u], f[v][v]); 
			vis[u][v] = vis[v][u] = 1;
		}	
		for(int k = 1; k <= n; k++){
			for(int i = 1; i <= n; i++){
				for(int j = 1; j <= n; j++){
					if(vis[i][k] && vis[k][j]) 
						vis[i][j] = true;
					if(vis[i][k] && vis[k][j] && vis[i][j])
						f[i][j] = Max( Min(f[i][k], f[k][j]) , f[i][j]);
				}
			}
		}
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				if(i == j) 
					continue;
				ans += f[i][j];
			}
		}
		printf("%d", ans);
	}
};

int main(){
	freopen("zoo.in", "r", stdin);
	freopen("zoo.out", "w", stdout);
	scanf("%d%d", &n, &m);
	point_30::calc();
}
