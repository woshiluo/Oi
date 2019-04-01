#include <cstdio>

int n, k, m, c, a[20], b[20], res;
bool map[20][20];

bool pd(){
    for(int i = 1; i < n; i++)
        for(int j = i + 1; j <= n; j++)
            if(map[i][j] && b[i] == b[j])
                return false;
    return true;
}

void dfs(int x, int last){
    if(x>n){
        res += pd();
        return ;
    }
    for(int i = 1; i < last; i++){
        b[x] = i; 
		dfs(x + 1, i);
		b[x] = 0;
	}
    for(int i = last + 1; i <= c; i++){
        b[x] = i;
		dfs(x + 1, i);
		b[x] = 0;
	}
}

int main(){
	scanf("%d%d%d%d", &n, &k, &m, &c);
    for(int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
    map[1][n] = map[n][1] = true;
    for(int i = 1, u, v; i <= m; i++){
		scanf("%d%d", &u, &v);
        map[ a[u] ][ a[v] ] = map[ a[v] ][ a[u] ] = true;
    }
    dfs(1, 0);
    printf("%d\n", res);
	return 0;
}
