#include <cstdio>
#include <cstring>
#include <queue>

inline long long Min(long long a, long long b){return a < b? a: b;}

const int N = 110000;
const int M = 510000;
const int INT_INF = 0x3f3f3f3f;
const long long LONG_INF = 4557430888798830399;

int T, n, m, k;
int in[N], out[N], ask[N];
bool has_ask[N];
// edge start
struct edge{
	int to, next, val;
}e[M];
int ehead[N], ecnt;
inline void add_edge(int now, int to, int val){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end
struct node{
	int now;
	long long val;
	bool operator< (const node &b) const{ return this->val > b.val; }
};

// dij start
long long dis[N];
int vis[N];
std::priority_queue<node> q;

void dij(int now){
	memset(dis, 0x3f, sizeof(long long) * (n + 5));
	while( !q.empty() ) 
		q.pop();
	q.push( (node){now, 0} );
	dis[now] = 0;
	while( !q.empty() ){
		node tmp = q.top(); q.pop();
		if(vis[ tmp.now ] == now) 
			continue;
		vis[ tmp.now ] = now;
		for(int i = ehead[ tmp.now ]; i; i = e[i].next){
			if(dis[ tmp.now ] + (long long)e[i].val < dis[ e[i].to ]){
				dis[ e[i].to ] = dis[ tmp.now ] + (long long)e[i].val;
				if( vis[ e[i].to ] != now )
					q.push( (node){e[i].to, dis[ e[i].to ]} );
			}
		}
	}
}
// dij end

namespace points_20{
	void calc(){
		long long ans = LONG_INF;
		for(int i = 1; i <= k; i++){
			dij( ask[i] );
			for(int j = 1; j <= k; j++){
				if(i != j)
					ans = dis[ ask[j] ] < ans? dis[ ask[j] ]: ans;	
			}
		}	
		printf("%lld\n", ans);
	}
}

namespace points_30{
	int q[N];
	int head, tail;
	long long ans = LONG_INF;
	void bfs(int now){
		head = tail = 0;
		q[head] = now; 
		while(head <= tail){
			for(int i = ehead[ q[head] ]; i; i = e[i].next){
				if(has_ask[ e[i].to ])
					ans = Min(ans, dis[ q[head] ] + (long long)e[i].val);
				if(dis[ q[head] ] + (long long)e[i].val < dis[ e[i].to ])
					dis[ e[i].to ] = dis[ q[head] ] + (long long)e[i].val;
				if(vis[ e[i].to ] == false){
					vis[ e[i].to ] = true;
					q[ ++tail ] = e[i].to;
				}
			}
			head++;
		}
	}
	void calc(){
		memset(dis, 0x3f, sizeof(long long) * (n + 5));
		ans = LONG_INF;
		for(int i = 1; i <= k; i++){ dis[ ask[i] ] = 0; }
		for(int i = 1; i <= n; i++){
			if(in[i] == 0 && out[i] != 0 && vis[i] == false){
				bfs(i);
			}
		}
		printf("%lld\n", ans);
	}
}

int main(){
	freopen("tourist.in", "r", stdin);
	freopen("tourist.out", "w" ,stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n, &m, &k);

		ecnt = 0;
		memset(ehead, 0, sizeof(int) * (n + 5));
		memset(vis, 0, sizeof(int) * (n + 5));
		memset(has_ask, 0, sizeof(bool) * (n + 5));
		memset(in, 0, sizeof(int) * (n + 5));
		memset(out, 0, sizeof(int) * (n + 5));

		for(int i = 1, u, v, w; i <= m; i++){
			scanf("%d%d%d", &u, &v, &w);
			if(u == v)
				continue;
			add_edge(u, v, w);
			in[v] ++;
			out[u] ++;
		}
		for(int i = 1; i <= k; i++){
			scanf("%d", &ask[i]);
			has_ask[ ask[i] ] = true;
		}

		if(n <= 2000) 
			points_20::calc();
		else 
			points_30::calc();

	}
	fclose(stdin);
	fclose(stdout);
}
