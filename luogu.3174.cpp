#include <cstdio>

inline int Max(int a, int b){return a > b? a: b;}

const int N = 310000;

int n, m, ans;
int dis[N], val[N];

// edge start
struct edge{
	int to, next;
}e[N << 1];
int ehead[N], ecnt;

inline void add_edge(int now, int to){
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

void get_val(){
	for(int u = 1, cnt; u <= n; u++){
		cnt = 0;
		for(int i = ehead[u]; i; i = e[i].next){
			cnt ++;
		}
		val[u] = cnt - 1;
	}	
}

void get_ans(int now = 1, int la = 0){
	int max, sec_max;
	max = sec_max = 0;
	dis[now] = val[now];
	for(int i = ehead[now]; i; i = e[i].next){
		if(e[i].to == la)
			continue;
		get_ans(e[i].to, now);
		if(dis[ e[i].to ] > max){
			sec_max = max;
			max = dis[ e[i].to ];
		}
		else if(dis[ e[i].to ] > sec_max)
			sec_max = dis[ e[i].to ];
//		dis[now] += dis[ e[i].to ];
	}
	dis[now] += max;
	ans = Max(ans, Max(dis[now], max + sec_max + val[now]));
}

int main(){
#ifdef woshiluo
	freopen("luogu.3174.in", "r", stdin);
	freopen("luogu.3174.out", "w" ,stdout);
#endif
	scanf("%d%d", &n, &m);
	while(m --){
		int u, v;
		scanf("%d%d", &u, &v);
		if(u == v) continue;
		add_edge(u, v);
		add_edge(v, u);
	}

	get_val();
	get_ans();
	
	printf("%d", ans + 2);
}
