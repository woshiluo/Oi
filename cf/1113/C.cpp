#include <cstdio>

int n, x, a[(int)3e5];
long long ans;
int map[(int)1.5e6][2];

int main(){
	scanf("%d", &n);
	map[0][0] = 1;
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		x ^= a[i];
		ans += map[x][i & 1];
		map[x][i & 1]++;
	}
	printf("%lld", ans);
}
