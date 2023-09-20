#include <cstdio>

const int N = 30;
const int M = 30;

struct edge{
	int to, next, val, flow;	
}e[(N * M) << 2];

int n, m, s, t;
int id[N][M], map[N][M];

int main(){
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w" ,stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			id[i][j] = (i - 1) * m + j;
		}	
	}
	s = (id[i][j] * 2) + 1;
	t = (id[i][j] * 2) + 2;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &tmp);	
		}	
	}
	// MCMF(); 
}
