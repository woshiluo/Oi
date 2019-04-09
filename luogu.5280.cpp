#include <cstdio>

const int N = 1e6;
const int mod = 998244353;

inline int add(int x, int y){x += y; return x >= mod? x - mod: x;}
inline int sub(int x, int y){x -= y; return x >= 0? x: x + mod;}

int n, m, op, x, y, k = 1;

int sf[N], f[N], g[N], tf[N], tg[N];

inline void pushtf(int now, int val){
	f[now] = (1LL * f[now] * val) % mod;
	tf[now] = (1LL * tf[now] * val) % mod;
	sf[now] = (1LL * sf[now] * val) % mod;	
}

inline void pushtg(int now, int val){
	g[now] = (1LL * g[now] * val) % mod;
	tg[now] = (1LL * tg[now] * val) % mod;
}

inline void pushdown(int now){
	if(tf[now] != 1){
		pushtf(now << 1, tf[now]);
		pushtf(now << 1 | 1, tf[now]);
		tf[now] = 1;
	}	
	if(tg[now] != 1){
		pushtg(now << 1, tg[now]);
		pushtg(now << 1 | 1, tg[now]);
		tg[now] = 1;
	}	
}

inline void pushup(int now){
	sf[now] = add(f[now], add(sf[now << 1], sf[now << 1|1]));
}

void build(int now, int left, int rig){
	tg[now] = tf[now] = g[now] = 1;
	if(left == rig) 
		return;
	int mid = (left + rig) >> 1;
	build(now << 1, left, mid);
	build(now << 1|1, mid + 1, rig);
}

void modify(int now, int left, int rig, int from, int to){
	pushdown(now);
	if(from == left && rig == to){
		f[now] = add(f[now], k);	
		pushtf(now << 1, 2);
		pushtf(now << 1|1, 2);
	}
	else {
		int mid = (left + rig) >> 1;	
		g[now] = add(g[now], k);
		if(to <= mid){
			modify(now << 1, left, mid, from, to);
			pushdown(now << 1 | 1);
			f[now << 1|1] = add(f[now << 1|1], sub(k, g[now << 1|1]));	
			g[now << 1|1] = add(g[now << 1|1], g[now << 1|1]);	
			pushtf((now << 1|1) << 1, 2); pushtf((now << 1|1) << 1|1, 2);
			pushtg((now << 1|1) << 1, 2); pushtg((now << 1|1) << 1|1, 2);
			pushup(now << 1|1);
		}
		else if(from > mid) {
			modify(now << 1|1, mid + 1, rig, from, to);
			pushdown(now << 1);
			f[now << 1] = add(f[now << 1], sub(k, g[now << 1]));	
			g[now << 1] = add(g[now << 1], g[now << 1]);	
			pushtf((now << 1) << 1, 2); pushtf((now << 1) << 1|1, 2);
			pushtg((now << 1) << 1, 2); pushtg((now << 1) << 1|1, 2);
			pushup(now << 1);
		}
		else {
			modify(now << 1, left, mid, from, mid);	
			modify(now << 1|1, mid + 1, rig, mid + 1, to);	
		}
	}
	pushup(now);
}

int main(){
#ifdef woshiluo
	freopen("luogu.5280.in", "r", stdin);
	freopen("luogu.5280.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	while(m--){
		scanf("%d", &op);	
		if(op == 1){
			scanf("%d%d", &x, &y);	
			modify(1, 1, n, x, y);
			k = add(k, k);
		}
		else 
			printf("%d\n", sf[1]);
	}
}
