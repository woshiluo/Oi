#include <cstdio>
#include <cstring>

const int N = 110;
const int mod = 1e9 + 7;

int T, n;

struct matrix {
	int a[N][N];
	matrix(int now = 0) {
		memset(a, 0, sizeof(a));
		if(now) {
			for(int i = 0; i < N; i++)
				a[i][i] = now;
		}
	}
	int* operator[] (int now) { return a[now]; }
	matrix operator* (matrix b) {
		matrix res(0);
		for(int i = 1; i <= 3; i++) {
			for(int j = 1; j <= 3; j++) {
				for(int k = 1; k <= 3; k++) 
					res[i][j] = ( res[i][j] + ( ( 1LL * this -> a[i][k] * b[k][j] ) % mod ) ) % mod;
			}
		}
		return res;
	}	
} f, B;
// [ f_i f_{i-1] f_{i-2} ]
// [ 1 1 0 ]
// [ 0 0 1 ]
// [ 1 0 0 ]

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

int main() {
#ifdef woshiluo 
	freopen("luogu.1939.in", "r", stdin);
	freopen("luogu.1939.out", "w", stdout);
#endif
	scanf("%d", &T);
	while( T -- ) {
		scanf("%d", &n);
		if( n <= 3 ) {
			printf("1\n");
			continue;
		}
		f = B = matrix(0);
		f[1][1] = f[1][2] = f[1][3] = B[1][1] = B[1][2] = B[2][3] = B[3][1] = 1;
		f = f * ksm(B, n - 3);
		printf("%d\n", f[1][1]);
	}
}
