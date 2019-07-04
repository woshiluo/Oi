#include <cstdio>
#include <cstring>
#include <queue>

inline long long Min(long long a, long long b){return a < b? a: b;}

const int N = 100010;
const int M = 500010;

int T;
int n, m, k;
int ask[N], ask_head[N];
long long ans;

// edge start
struct edge{
	int to, val, next;
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
// spfa start
struct node{
    int now;
	long long val;
    bool operator< (const node &b) const{
        return this -> val > b.val;
    }
};
std::priority_queue<node> q;
bool vis[N];
long long dis[N];
void spfa(int now){
	memset(vis, 0, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
    dis[now] = 0;
    q.push( (node){now, 0} );
    while( !q.empty() ){
        node tmp = q.top(); q.pop();
        if(vis[ tmp.now ])
            continue;
        vis[ tmp.now ] = true;
        for(int i = ehead[ tmp.now ]; i; i = e[i].next){
            if(dis[ e[i].to ] > dis[ tmp.now ] + (long long)e[i].val){
                dis[ e[i].to ] = dis[ tmp.now ] + (long long)e[i].val;
                if( vis[ e[i].to ] == false )
                    q.push( (node){e[i].to, dis[ e[i].to ]} );
            }
        }
    }
}
// spfa end

inline void init(){
	ecnt = 0; ans = (1LL << 60LL);
	memset(ehead, 0, sizeof(ehead));
}

void readin(){
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1, u, v, w; i <= m; i++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
	}
	for(int i = 1; i <= k; i++){
		scanf("%d", &ask[i]);
	}
}

void calc(){
	int old_ecnt = ecnt;
	for(int i = 1; i <= k; i++){
		ask_head[i] = ehead[ ask[i] ];	
	}
	int s = n + 1, t = n + 2;
	for(int l = 1; l <= k; l <<= 1){
		for(int i = 1; i <= k; i++){
			if(i & l)
				add_edge(s, ask[i], 0);
			else 
				add_edge(ask[i], t, 0);
		}
		spfa(s);
		ans = Min(ans, dis[t]);
		ecnt = old_ecnt;
		ehead[s] = ehead[t] = 0;
		for(int i = 1; i <= k; i++){
			ehead[ ask[i] ] = ask_head[i];
		}
		for(int i = 1; i <= k; i++){
			if((i & l) == 0)
				add_edge(s, ask[i], 0);
			else 
				add_edge(ask[i], t, 0);
		}
		spfa(s);
		ans = Min(ans, dis[t]);
		ecnt = old_ecnt;
		ehead[s] = ehead[t] = 0;
		for(int i = 1; i <= k; i++){
			ehead[ ask[i] ] = ask_head[i];
		}
	}
}

int main(){
	freopen("tourist.in", "r", stdin);
	freopen("tourist.out", "w" ,stdout);
	scanf("%d", &T);
	while(T--){
		init();
		readin();
		calc();
		printf("%lld\n", ans);
	}
	fclose(stdin);
	fclose(stdout);
}
