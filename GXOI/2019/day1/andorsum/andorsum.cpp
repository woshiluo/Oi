#include <cstdio>

const int N = 1100;
const int mod = 1e9 + 7;

int n;
int a[N][N];

int main(){
	scanf("%d", &n);	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &a[i][j]);
		}
	}
}
