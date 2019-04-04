#include <cstdio>
#include <cstring>

const int N = 410;
const int INF = 0x3f3f3f3f;

int n, k;
int a[N], sum[N], f[N][N];
// bool vis[N][N];

int main(){
	memset(f, INF, sizeof(f));
	scanf("%d%d", &n, &k);	
	for(int i = 1; i <= n; i++){
		f[i][i] = 0;
		scanf("%d", &a[i]);	
		for(int j = i - 1; j >= 1; j--){
			if(a[j] < a[i]) 
				break;
			f[i][j] = Min(f[i][j], (i - j + 1) * a[i] - (sum[i] - sum[ j - 1 ]));
		}
	}
	for(int len = 1; len <= n; len++){
		for(int i = 1, j; i <= n - len; i++){
			j = i + len;
			for(int k = i; k < j; k++){
				f[i][j] = Min(f[i][j], f[i][k] + f[k + 1][j]);			
			}
		}
	}
}
