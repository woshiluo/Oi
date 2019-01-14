
#include <cstdio>
#include <cstring>

const int N=1e5+1e4;

struct edg{
	int now,to,val;
}ed[N];

// edge start 
struct edge{
	int to,next;
}e[N];
int ehead[N],ecnt;
inline void add_edge(int now, int to){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

int n,m,left,rig,mid;
int pos[N],ans[N],acnt,pcnt;

void dfs(int now){
	pos[now] = 1;
	for(int i = ehead[now]; i; i = e[i].next)
		if(pos[ e[i].to ] == 0)
			dfs( e[i].to );
	pos[now] = ++pcnt;
}

inline bool check(int lim){
	ecnt = acnt = 0;
	memset(ehead, 0, sizeof(ehead));
	memset(pos, 0, sizeof(pos));
	for(int i = 1;i <= m; i++)
		if(ed[i].val > lim) 
			add_edge(ed[i].now, ed[i].to);
	for(int i = 1;i <= n; i++)
		if(!pos[i])
			dfs(i);
	for(int i = 1; i <= m; i++)
		if(pos[ ed[i].now ] < pos[ ed[i].to ])
			if( ed[i].val > lim ) return false;
			else ans[ ++acnt ] = i;
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%d", &ed[i].now, &ed[i].to, &ed[i].val);
	rig=1e9;
	while(left!=rig){
		mid = (left + rig) >> 1;
		if( check(mid) ) rig=mid;
		else left=mid+1;
	}
	check(left);
	printf("%d %d\n", left, acnt);
	for(int i=1;i<=acnt;i++) printf("%d ", ans[i]);
}
