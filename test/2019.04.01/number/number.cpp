#include <cstdio>

const int N = 30;

int n, m, k, p, cnt;
int lne[N], map[N][N];

void dfs(int x, int y, int now){
	if(x > n){
		for(int i = 1; i <= n; i++)
			if(lne[i] == 1)
				return ;
		cnt = (cnt + 1) % p;
		return ;
	}
	if(y > m){
		if(now != -1)
			return ;
		dfs(x + 1, 1, 1); 
		return ;
	}
	if(map[x][y] != 0){
		lne[y] *= map[x][y];
		dfs(x, y + 1, now * map[x][y]);
		lne[y] *= map[x][y];
		return ;
	}
	dfs(x, y + 1, now);
	lne[y] *= -1; 
	dfs(x, y + 1, -now);
	lne[y] *= -1; 
}

int main(){
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	scanf("%d%d", &n, &m);
	scanf("%d", &k);
	for(int i = 1, a, b, c; i <= k; i++){
		scanf("%d%d%d", &a, &b, &c);
		map[a][b] = c;
	}
	scanf("%d", &p);

	for(int i = 1; i <= n; i++) 
		lne[i] = 1;

	dfs(1, 1, 1);
	printf("%d", cnt);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
