#include <cstdio>
#include <queue>

inline int Max(int a, int b){return a > b? a: b;}

const int N = 2e5 + 1e4;

int n, cnt;
long long ans = 0;
int val[N], size[N], son[N], top[N], tmp[N];

struct edge{
	int next, to;
}e[N];

int ehead[N], ecnt;

std::priority_queue<int> q[N];

inline void add_edge(int now, int to){
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

void dfs1(int now){
	for(int i = ehead[now]; i;i = e[i].next){
		dfs1(e[i].to);			
		if(size[e[i].to] > size[ son[now] ])
			son[now] = e[i].to;
		size[now] = Max(size[now], size[ e[i].to ]);
	}
	size[now] ++;
}

void dfs2(int now, int la){
	top[now] = la;
	if( son[now] )
		dfs2(son[now], la);
	for(int i = ehead[now]; i; i = e[i].next){
		if(e[i].to == son[now]) 
			continue;
		dfs2(e[i].to, e[i].to);
		while( !q[ top[now] ].empty() && !q[ e[i].to ].empty() ){
			tmp[ ++cnt ] = Max( q[ e[i].to ].top(), q[ top[now] ].top());
			q[ top[now] ].pop(); q[ e[i].to ].pop();
		}
		while( !q[ e[i].to ].top() )
			tmp[ ++cnt ] = q[ e[i].to ].top(), q[ e[i].to ].pop();
		while(cnt)
			q[ top[now] ].push( tmp[ cnt -- ] );
	}
	q[ top[now] ].push( val[now] );
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &val[i]);
	for(int i = 2, u; i <= n; i++){
		scanf("%d", &u);
		add_edge(u, i);
	}
	dfs1(1);
	dfs2(1, 1);
	while( !q[1].empty() ) 
		ans += q[1].top(), q[1].pop();
	printf("%lld", ans);
}
