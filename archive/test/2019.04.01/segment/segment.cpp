#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 210000;
const int INF = 0x7f7f7f7f;

inline int lowbit(int now){return now & (-now);};

int T, n, x, op, cnt, in_cnt;
int tmp[N << 1], ori[N], id[N];

struct segment{
	int left, rig;
}seg[N];

struct BIT{
	int tree[N << 1];	
	inline void init(int n){ n <<= 1; memset(tree, 0, sizeof(int) * (n + 1)); }
	int sum(int now){
		int res = 0;
		for(;now ; now -= lowbit(now))
			res += tree[now];
		return res;
	}
	void add(int now, int val){
		for(;now <= (n << 1); now += lowbit(now))
			tree[now] += val;
	}
}t1, t2;


inline void init(){
	cnt = in_cnt = 0;
	t1.init(n); t2.init(n);
}

int binary_serach(int now){
	int left = 1, rig = cnt, ret, mid;
	while( left <= rig ){
		mid = ( left + rig ) >> 1;
		if( ori[mid] == now )
			ret = mid;
		if( ori[mid] > now )
			rig  = mid - 1;
		else 
			left = mid + 1;
	}
	return ret;
}

int main(){
#ifdef woshiluo
	freopen("segment.in", "r", stdin);
	freopen("segment.out", "w", stdout);
#endif
	scanf("%d", &T);	
	for(int _case = 1; _case <= T; _case++){
		printf("Case #%d:\n", _case);
		scanf("%d", &n);
		for(int i = 1, q; i <= n; i++){
			scanf("%d%d", &op, &x);
			if( op == 1 ) 
				seg[i].left = INF, seg[i].rig = x;
			else 
				seg[i].left = x, seg[i].rig = x + (++ in_cnt), id[in_cnt] = i;
			q = (i - 1) << 1;	
			tmp[q + 1] = seg[i].left; tmp[q + 2] = seg[i].rig;
		}
		
		init();

		std::sort(tmp + 1, tmp + (n << 1) + 1);
		for(int i = 1; i <= (n << 1); i++){
			if( tmp[i] != tmp[i - 1] || i == 1 ) 
				cnt++;
			ori[cnt] = tmp[i];
		}
		for(int i = 1; i <= n; i++){
			if( seg[i].left != INF ){
				seg[i].left = binary_serach( seg[i].left ), seg[i].rig = binary_serach( seg[i].rig );
				printf("%d\n", t2.sum( seg[i].rig ) - t1.sum( seg[i].left - 1 ));
				t1.add( seg[i].left, 1);
				t2.add( seg[i].rig,  1);
			}
			else {
				t1.add( seg[ id[ seg[i].rig ] ].left, -1);
				t2.add( seg[ id[ seg[i].rig ] ].rig,  -1);
			}
		}
	}
}
