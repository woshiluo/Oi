#include <cstdio>
#include <cstring>

int n, m;
int a[24];
bool vis[24];
int f[2100];

inline void pd(){
	memset(f, 0, sizeof(f));
	f[0] = true;
	for(int i = 1; i <= n; i++){
		for(int i
	}
}

void dfs(int now, int less){
	if(less == 0){
		pd();
		return ;
	}
	if(now + less >= n) return ;
	vis[now] = true;
	dfs(now + 1, less - 1);
	vis[now] = false;
	dfs(now + 1, less);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dfs(n, m);
}
