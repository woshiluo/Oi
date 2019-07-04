#include <cstdio>

const int N = 1100;
const int P = 13;

int n, m, p;
int s[P], a[P], cnt[P];
bool map[N][N], vis[N][N];
char str[N];

int q[N << 2][P], head[P], tail[P], head_dep[P], tail_dep[P];

int main(){
	scanf("%d%d%d", &n, &m, &p);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		tail[i] = -1;
	}
	for(int i = 1; i <= n; i++){
		scanf("%s", str + 1);
		for(int j = 1; j <= n; j++){
			if(str[j] == '.') map[i][j] = true;
			else if(str[j] == '#') map[i][j] = false;
			else map[i][j] = true, cnt[ str[j] - '0' ]++,q[ ++tail[ str[j] - '0' ] ] = (node){i, j};
		}
	}
	while(1){
		for(int i = 1; i <= p; i++){
		
		}
	}
}
