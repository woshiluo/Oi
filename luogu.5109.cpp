#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
#include <algorithm>

inline long long Min(long long a, long long b){return a < b? a: b;}

const int N = 2e5 + 1e4;
const int M = 4e5 + 1e4;
const int INF = (1 << 30);
const long long LONG_INF = (1LL << 62);

int n, m, u, v, a, l, T, Q, K, S;
long long ans;

struct que{
	int now; 
	long long dis;	
	bool operator< (const que &b) const{
		return this -> dis > b.dis;
	}
}tmp;

struct node{
	long long Min_dis;
	int val, dep;
	int fa[25];
}nodes[N << 1];

struct edge{
	int to, val, next;
}e[M << 1];
int ehead[N << 1], ecnt;

inline void add_edge(int now, int to, int val = 0){
	 ecnt++;
	 e[ecnt].to = to;
	 e[ecnt].val = val;
	 e[ecnt].next = ehead[now]; 
	 ehead[now] = ecnt;
}

std::priority_queue<que> q;

// dijkstra start
long long dis[N];
bool vis[N];
void dijkstra(){
	while( !q.empty() ) q.pop();	
	memset(vis, false, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	q.push( (que){1, 0} );
	while( !q.empty() ){
		tmp = q.top();
		q.pop();
		if( vis[ tmp.now ] )
			continue;
		vis[ tmp.now ] = true;
		for(int i = ehead[ tmp.now ]; i; i = e[i].next){
			if(dis[ tmp.now ] + e[i].val < dis[ e[i].to ]){
				dis[ e[i].to ] = dis[ tmp.now ] + e[i].val;
				if( vis[ e[i].to ] == false )
					q.push( (que){e[i].to, dis[ e[i].to ]} );
			}
		}
	}
}
// dijkstra end

// kurastra_tree start
int kurastra_n;
struct kurastra_edge{
	int now, to, val;	
	bool operator< (kurastra_edge b){
		return this -> val > b.val;
	}
}kurastra_e[M];

struct uds{
	int fa[N << 1];
	void init(int now){now <<= 1; for(int i = 1; i <= now; i++) fa[i] = i;}
	int get_fa(int now){return fa[now] == now? now: fa[now] = get_fa(fa[now]);}
	int& operator[] (int now){
		return fa[now];
	}
}set;

void build_tree(){
	ecnt = 0;
	memset(ehead, 0, sizeof(ehead)); 
	kurastra_n = n;
	set.init(n);
	std::sort(kurastra_e + 1, kurastra_e + m + 1);	
	for(int i = 1; i <= m; i++){
		int tmp_x = set.get_fa(kurastra_e[i].now), tmp_y = set.get_fa(kurastra_e[i].to);		
		if(tmp_x != tmp_y){
			++kurastra_n;	
			nodes[kurastra_n].val = kurastra_e[i].val;
			add_edge(kurastra_n, tmp_x);
			add_edge(kurastra_n, tmp_y);
			set[ tmp_x ] = kurastra_n;
			set[ tmp_y ] = kurastra_n;
		}
	}
}

void get_st(int now, int fa, int dep){
	memset(nodes[now].fa, 0, sizeof(nodes[now].fa));
	nodes[now].fa[0] = fa;
	nodes[now].dep = dep;
	if( now >= 1 && now <= n ) 
		nodes[now].Min_dis = dis[now], nodes[now].val = INF;
	else 
		nodes[now].Min_dis = LONG_INF;
	for(int k = 1; k <= (int)std::log2(dep); k++)
		nodes[now].fa[k] = nodes[ nodes[now].fa[k - 1] ]. fa[ k - 1 ];
	for(int i = ehead[now]; i; i = e[i].next){
		get_st(e[i].to, now, dep + 1);	
		nodes[now].Min_dis = Min(nodes[now].Min_dis, nodes[ e[i].to ].Min_dis);
	}
}

long long work(int now, int P){
	for(int k = (int)std::log2(nodes[now].dep); k >= 0; k--){
		if(nodes[ nodes[now].fa[k] ].val > P && nodes[now].fa[k]){
			now = nodes[now].fa[k];
		}	
	}
	return nodes[now].Min_dis;
}
// kurastra_tree end

inline void init(){
	ecnt = 0;
	memset(ehead, 0, sizeof(ehead));	
}

void readin(){
	scanf("%d%d", &n, &m); 
	for(int i = 1; i <= m; i++){
		scanf("%d%d%d%d", &u, &v, &l, &a);
		kurastra_e[i] = (kurastra_edge){u, v, a};
		add_edge(u, v, l);
		add_edge(v, u, l);
	}
}

void get_ans(){
	int from, to;
	scanf("%d%d%d", &Q, &K, &S);
	ans = 0;
	while(Q--){
		scanf("%d%d", &u, &v);
		from = ( (u + K * ans - 1) % n ) + 1; 
		to = (v + K * ans) % (S + 1);
		ans = work(from, to);
		printf("%lld\n", ans);
	}
}

int main(){
	freopen("return.in", "r", stdin);
	freopen("return.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		init();	
		readin();
		dijkstra();
		build_tree();
		get_st(kurastra_n, kurastra_n, 1);
		get_ans();
	}
}
