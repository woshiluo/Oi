#include <cstdio>
#include <cstdlib>

struct que{
	int x, y;
}q[30];
int qcnt;

int map[10][10];
bool vis[10][10];
char str[5];

inline void check(){
	qcnt = 0;	
	for(int i = 1; i <= 4; i++){
		for(int j = 1; j <= 4; j++){
			if(vis[i][j])
				q[ ++qcnt ] = (que){i, j};
			if(map[i][j]) 
				return ;
		}
	}
	printf("%d\n", qcnt);
	while(qcnt > 0){
		printf("%d %d\n", q[qcnt].x, q[qcnt].y);
		qcnt--;
	}
	exit(0);
}

void dfs(int x, int y){
	if(x > 4){
		check();
		return ;
	}
	if(y > 4){
		dfs(x + 1, 1);
		return ;
	}
	vis[x][y] = true;
	for(int i = 1; i <= 4; i++){
		map[i][y] ^= 1;
		map[x][i] ^= 1;
	}
	map[x][y] ^= 1;
	dfs(x, y + 1);
	vis[x][y] = false;
	for(int i = 1; i <= 4; i++){
		map[i][y] ^= 1;
		map[x][i] ^= 1;
	}
	map[x][y] ^= 1;
	dfs(x, y + 1);
}

int main(){
#ifdef woshiluo
	freopen("poj.2965.in", "r", stdin);
	freopen("poj.2965.out", "w", stdout);
#endif
	for(int i = 1; i <= 4; i++){
		scanf("%s", str);
		for(int j = 0; j < 4; j++){
			if(str[j] == '-') 
				map[i][j + 1] = 0;
			else 
				map[i][j + 1] = 1;
		}
	}
	dfs(1, 1);
}
