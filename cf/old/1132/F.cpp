#include <cstdio>

const int N = 510;

inline int Min(int a, int b){return a < b? a: b;}

int n;
char read_str, la;
int f[N][N];
char str[N];

int main(){
#ifdef woshiluo
	freopen("F.in", "r", stdin);
	freopen("F.out", "w" ,stdout);
#endif
	scanf("%d", &n);
	n = 0;
	while(scanf("%c", &read_str) != EOF){
		if(read_str >='a' && read_str <= 'z'){
			if(read_str != la){
				str[++n] = read_str;
				la  = read_str;
			}
		}	
	}
	for(int i = 1; i <= n; i++) f[i][i] = 1;
	for(int len = 2; len <= n; len++){
		for(int left = 1, rig; left + len - 1 <= n; left++){
			rig = left + len - 1;
			f[left][rig] = rig - left + 1;
			f[left][rig] = Min(f[left + 1][rig], f[left][rig - 1]) + (str[left] != str[rig]);
			for(int k = left + 1; k <= rig; k++)
				f[left][rig] = Min(f[left][k - 1] + f[k][rig], f[left][rig]);
		}
	}	
	printf("%d\n", f[1][n]);
}
