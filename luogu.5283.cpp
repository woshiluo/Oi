#include <cstdio>
#include <queue>

const int N = 2e7 + 1e4;

struct node{
	int id, rank;
	long long val;
	bool operator< (const node &b) const{
		return this -> val < b.val;	
	}
};

int n, k, cnt;
long long ans = 1, tmp;
long long sum[ (int)(5e5 + 1e4) ];

std::priority_queue<node> q;

// Trie Start
int son[N][2], size[N];
void insert(long long now){
	int rt = 0;
	for(int i = 31, kind; i >= 0; i--){
		kind = (now >> i) & 1; size[rt] ++;	
		if( son[rt][kind] == false ) 
			son[rt][kind] = ++ cnt;
		rt = son[rt][kind];
	}
	size[rt]++;
}

long long query(long long now, int rk){
	int rt = 0; long long res = 0;
	for(int i = 31, kind; i >= 0; i--){
		kind = (now >> i) & 1; 
		if( son[rt][kind ^ 1] == 0 )
			rt = son[rt][kind];
		else if(rk <= size[ son[rt][kind ^ 1] ])
			rt = son[rt][kind ^ 1], res |= 1LL << i;
		else 
			rk -= size[ son[rt][kind ^ 1] ], rt = son[rt][kind];
	}
	return res;
}
// Trie End

int main(){
#ifdef woshiluo
	freopen("luogu.5283.in", "r", stdin);
	freopen("luogu.5283.out", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	k <<= 1;
	for(int i = 1; i <= n; i++){
		scanf("%lld", &tmp);
		sum[i] = sum[i - 1] ^ tmp;
	}
	for(int i = 0; i <= n; i++)
		insert( sum[i] );
	for(int i = 0; i <= n; i++)
		q.push((node){i, 1, query(sum[i], 1)});
	for(int i = 1; i <= k; i++){
		node t = q.top(); q.pop();
		ans += t.val;
		if(t.rank < n) 
			q.push( (node){t.id, t.rank + 1, query( sum[t.id], t.rank + 1)} );
	}
	printf("%lld", ans >> 1);
}
