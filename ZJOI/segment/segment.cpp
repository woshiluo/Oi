#include <cstdio>
#include <cstring>

const int N = 1010;

int n, m, x, y, op, tag_ans, tree_cnt = 1;

struct Segment_tree{
	int tag[N << 2];	
	inline void pushdown(int now){
		if(tag[now] == 1){
			tag_ans           += (tag[now] == 1? -1: 0);
			tag_ans           += (tag[now << 1] == 1? 0: 1);
			tag_ans           += (tag[now << 1 | 1] == 1? 0: 1);
			tag[now << 1]     =  1;
			tag[now << 1 | 1] =  1;
			tag[now]          =  0;
		}	
	}

	void modify(int now, int left, int rig, int from, int to){
		if(from <= left && rig <= to){
			tag_ans  += (tag[now] == 1? 0: 1);
			tag[now] =  1;
			return ;
		}
		int mid = (left + rig) >> 1;
		pushdown(now);
		if(from <= mid) modify(now << 1, left, mid, from, to);
		if(to > mid) modify(now << 1 | 1, mid + 1, rig, from, to);
	}	
}tree[N * (1 << 10)];

int main(){
	freopen("segment.in", "r", stdin);
	freopen("segment.out", "w", stdout);

	scanf("%d%d", &n, &m);
	while(m--){
		scanf("%d", &op);
		if(op == 1){
			scanf("%d%d", &x, &y);
			tag_ans <<= 1;
			for(int i = tree_cnt; i >= 1; i--){
				tree[i << 1]     = tree[i];	
				tree[i << 1 | 1] = tree[i];
				if((i << 1) & 1)
					tree[i << 1].modify(1, 1, n, x, y);
				else 
					tree[i << 1 | 1].modify(1, 1, n, x, y);
			}	
			tree_cnt <<= 1;
		}
		else if(op == 2)
			printf("%d\n", tag_ans);
	}
}
