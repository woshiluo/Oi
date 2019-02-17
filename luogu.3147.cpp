#include <cstdio>

const int N = 262144 + 10;

int n, tmp, ans;
int f[60][N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &tmp);
		f[tmp][i] = i + 1;
	}
	for(int i = 2; i <= 58; i++){
		for(int j = 1; j <= n; j++){
			if(!f[i][j]) f[i][j] = f[i - 1][ f[i - 1][j] ];
			if(f[i][j]) ans = i;
		}
	}
	printf("%d", ans);
}
