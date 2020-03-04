#include <cstdio>
#include <queue>

const int N = 1100;

inline int Aabs(int now) {return now < 0? (0 - now): now;}

struct node{
	int x, y, dep;
}tmp_node;

int n, m, p, kuai_cnt;
int col[N][N], cnt[12], s[N];
int que[N << 2][10], head[10], tail[10], tmp[N<<2], thead, ttail;
char str[N];
bool map[N][N];

std::queue<node> q[12], tmp;


inline bool check(node u, int k) {
	bool flag=false;
	for(int i=0;i<4;++i) {
		node v; tmp.x=u.x+dx[i], tmp.y=u.y+dy[i], tmp.dep=u.dep+1;
		if(vis[tmp.x][tmp.y] || tmp.x < 1 || tmp.y < 1 || tmp.x > n || tmp.y > m) continue;
		flag=true;
		if(tmp.dep<=s[k]) return true;
	}
	return !ret;
}

inline bool work(int k) {
	while(!q[k].empty()){
		node u=q[k].front();
		if(!check(u, k)) break;
		q[k].pop();
		for(int i=0;i<4;++i) {
			node tmp=u; tmp.x+=dx[i], tmp.y+=dy[i], tmp.dep=u.dep+1;
			if(col[tmp.x][tmp.y] || tmp.x < 1 || tmp.y < 1 || tmp.x > n || tmp.y > m) continue;
			q[k].push(tmp), col[tmp.x][tmp.y] = k;
			++tot[k];
			kuai_cnt--;
			if(kuai_cnt) return false;
		}
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("E.in", "r" , stdin);
	freopen("E.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &p);	
	for(int i = 1; i <= p; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++){
		scanf("%s", str + 1);
		for(int j = 1; j <= m; j++){
			if(str[j] == '#') map[i][j] = false; 
			else if(str[j] == '.') map[i][j] = true, kuai_cnt++; 
			else map[i][j] = false, col[i][j] = str[j] - '0', cnt[ col[i][j] ]++; q[ col[i][j] ] .push( (node){i,j} );
		}
	}
	while(1){
		for(int i = 1; i <= p; i++){
			s[i] += a[i];
			if(!work(i)) break;
		}
	}
	for(int i = 1; i <= p; i++) printf("%d ",cnt[i]);
}
