#include <cstdio>

const long long N = 1e5 + 1e4;
const long long mod = 1e9 + 7;

long long n, k, u, v, ans, tmp, son[N];

inline long long ksm(long long a, long long p){
	long long res = 1LL;
	while(p){
		if(p & 1LL) res = ( res * a ) % mod;	
		a = ( a * a ) % mod;
		p >>= 1LL;
	}	
	return res;
}

struct edge{
	long long next, to;	
	bool val;
}e[N << 1];
long long ehead[N], ecnt;

inline void add_edge(long long now, long long to, long long val){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

void dfs1(long long now, long long fa){
	son[now] = 1;
	for(long long i = ehead[now]; i; i = e[i].next){
		if( e[i].to == fa ) 
			continue;
		if( e[i].val == 0){
			dfs1( e[i].to, now );
			son[now] += son[ e[i].to ];
		}
	}
}

int main(){
	scanf("%lld%lld", &n, &k);
	for(long long i = 1; i < n; i++){
		scanf("%lld%lld%lld", &u, &v, &tmp);
		add_edge(u, v, tmp);
		add_edge(v, u, tmp);
	}
	for(int i = 1; i <= n; i++){
		if(son[i] == 0){
			dfs1(i, 0);
			if(son[i] != 1) 
				ans = (ans + ksm(son[i], k)) % mod - son[i];
		}
	}
	printf("%lld", ( ( ksm(n, k) - ans - n ) % mod + mod) %mod ) ;
}
