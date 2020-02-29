#include <cstdio>
#include <cstring>

const int N = 50;
const int mod = 2017;

int n, m;

struct matrix {
	int f[N][N];
	matrix(int tmp = 0) {
		memset(f, 0, sizeof(f));
		if(tmp)
			for(int i = 0; i <= n; i++)
				f[i][i] = 1;
	}
	matrix operator* (matrix b) {
		matrix ans;
		for(int i = 0; i <= n; i++) {
			for(int j = 0; j <= n; j++) {
				for(int k = 0; k <= n; k++)
					ans[i][j] = (ans[i][j] + (this -> f[i][k] * b[k][j]) ) % mod;
			}
		}
		return ans;
	}
	int* operator[] (int now) { return f[now]; }
} f;

matrix ksm(matrix a, int p) {
	matrix res(1);
	while(p) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;	
		p >>= 1;
	}
	return res;
}

int main(){
#ifdef woshiluo
	freopen("luogu.3758.in", "r", stdin);
	freopen("luogu.3758.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	int u, v;
	while( m -- ) {
		scanf("%d%d", &u, &v);
		f[u][v] = f[v][u] = 1;
	}
	for(int i = 1; i <= n; i++) 
		f[i][i] = f[i][0] = 1;
	f[0][0] = 1;
	int t;
	scanf("%d", &t);
	f = ksm(f, t);
	int ans = 0;
	for(int i = 0; i <= n; i++)
		ans = (ans + f[1][i]) % 2017;
	printf("%d", ans);
}
