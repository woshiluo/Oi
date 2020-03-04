#include <cstdio>
#include <cstring>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 5100;

int n;
int a[N], l[N], r[N], f[N][N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	l[1] = 1;	
	for(int i = 2; i <= n; i++){
		if(a[i] == a[i - 1]) l[i] = l[i - 1];
		else l[i] = i;
	}
	r[n] = n;
	for(int i = n - 1; i >= 1; i--){
		if(a[i] == a[i + 1]) r[i] = r[i + 1];
		else r[i] = i;
	}
	memset(f, 0x3f, sizeof(f));
	for(int i = 1; i<= n;i ++) f[ l[i] ][ r[i] ] = 0;
	for(int len = 0; len < n; len++){
		for(int i = 1,j; i + len <= n; i++){
			j = i + len;
			if(i > 1 && j < n && a[i - 1] == a[j + 1])
				f[ l[i - 1] ][ r[j + 1] ] = Min(f[ l[i - 1] ][ r[j + 1] ],f[i][j] + 1);
			if(i > 1)
				f[ l[i - 1] ][j] = Min(f[ l[i - 1] ][j], f[i][j] + 1);
			if(j < n) 
				f[i][ r[j + 1] ] = Min(f[i][ r[j + 1] ], f[i][j] + 1);
		}
	}
	printf("%d", f[1][n]);
}
