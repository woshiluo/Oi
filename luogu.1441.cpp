#include <cstdio>
#include <cstring>

inline int Max(int a, int b) {return a > b? a: b;}

int n, m, now_max, ans, cnt;
int a[30];
bool vis[30];
bool f[91000];

inline void calc(){
	memset(f, false, sizeof(f));
	f[0] = true;
	now_max = 0; cnt = 0;
	for(int i = 1; i <= n; i++){
		if( vis[i] ) continue;
		for(int j = now_max; j >= 0; j--){	
			if(f[j] && f[j + a[i]] == false){ 
				cnt++;
				f[j + a[i]] = true;	
			}
		}
		now_max += a[i];
	}
	ans = Max(ans, cnt);
}

void dfs(int now, int less){
	if(less == 0){
		calc();
		return ;
	}
	vis[now] = true;
	dfs(now + 1, less - 1);
	if(now + less > n) return ;
	vis[now] = false;
	dfs(now + 1, less);
}

int main(){
#ifdef woshiluo
	freopen("luogu.1441.in", "r", stdin);
	freopen("luogu.1441.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dfs(1 ,m);
	printf("%d", ans);
}
