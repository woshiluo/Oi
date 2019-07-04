#include <cstdio>
#include <iostream>
#include <algorithm>

inline int Min(int a, int b){return a < b? a: b;}
inline int Max(int a, int b){return a > b? a: b;}

const int N = 1e5 + 1e4;
const int M = 1e6 + 1e5;

int n, m, k_n;
int happy[N << 1];
long long ans;
// 30% start
namespace point_30{
	const int N = 210;	
	
	int f[N][N], vis[N][N];
	void calc(){
		for(int i = 1; i <= n; i++){ vis[i][i] = true; scanf("%d", &f[i][i]);}
		for(int i = 1, u, v; i <= m; i++){
			scanf("%d%d", &u, &v);	
			f[u][v] = f[v][u] = Min(f[u][u], f[v][v]); 
			vis[u][v] = vis[v][u] = 1;
		}	
		for(int k = 1; k <= n; k++){
			for(int i = 1; i <= n; i++){
				for(int j = 1; j <= n; j++){
					if(vis[i][k] && vis[k][j]) 
						vis[i][j] = true;
					if(vis[i][k] && vis[k][j] && vis[i][j])
						f[i][j] = Max( Min(f[i][k], f[k][j]) , f[i][j]);
				}
			}
		}
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				if(i == j) 
					continue;
				ans += (long long)f[i][j];
			}
		}
		std::cout << ans;
	}
};
// 30% end
// edge start
struct edge{
	int to, next;
}e[N << 1];
int ehead[N << 1], ecnt;

inline void add_edge(int now, int to){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end
// kurstra start
struct k_edge{
	int now, to, val;
	bool operator< (const k_edge &b) const{
		return this -> val > b.val;
	}
}k_e[M << 1];
int k_ecnt;

struct uds{
	int fa[N << 1];
	inline void init(int now){now <<= 1; for(int i = 0; i <= now; i++) fa[i] = i;}
	int get_fa(int now){return fa[now] = (fa[now] == now? now: get_fa( fa[now] ));}
	int& operator[](int now){return fa[now];}
}set;

void kurstra(){
	k_n = n;
	set.init(n);	
	std::sort(k_e + 1, k_e + k_ecnt + 1);

	for(int i = 1, tmp_x, tmp_y; i <= k_ecnt; i++){
		tmp_x = set.get_fa( k_e[i].now ); tmp_y = set.get_fa( k_e[i].to );	
		if(tmp_x != tmp_y){
			++k_n;
			happy[k_n] = k_e[i].val;
			add_edge(k_n, tmp_x);
			add_edge(k_n, tmp_y);
			set[tmp_y] = k_n;
			set[tmp_x] = k_n; 
		}
	}	
}
// kurstra end
int son[N << 1];
void dfs(int now){
	long long tmp = 1LL;
	if(now <= n)
		son[now] = 1;
	for(int i = ehead[now]; i; i = e[i].next){
		dfs(e[i].to);	
		son[now] += son[ e[i].to ];
		tmp *= (long long)son[ e[i].to ];
	}		
	if(now > n)
		ans += 1LL * tmp * (long long)happy[now];		
}
int main(){
	freopen("zoo.in", "r", stdin);
	freopen("zoo.out", "w", stdout);
	scanf("%d%d", &n, &m);	
	if(n <= 200){
		point_30::calc();
		return 0;
	}
	for(int i = 1; i <= n; i++){ scanf("%d", &happy[i]); }
	for(int i = 1, u, v; i <= m; i++){
		scanf("%d%d", &u, &v);
		k_e[++k_ecnt] = (k_edge){u, v, Min(happy[u], happy[v])};	
		k_e[++k_ecnt] = (k_edge){v, u, Min(happy[u], happy[v])};	
	}

	kurstra();
	
	dfs(k_n);
	 
	std::cout << (ans << 1LL);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
