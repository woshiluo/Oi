#include <cstdio>
#include <cstring>

struct segment{
	int left, rig;
}seg[210000];

bool vis[210000];

int T;
int n, cnt, add_cnt;

int main(){
	freopen("segment.in", "r", stdin);
	freopen("segment.out", "w", stdout);
	scanf("%d", &T);	
	for(int _case = 1; _case <= T; _case++){
		memset(vis, 0, sizeof(vis)); cnt = 0; add_cnt = 0;

		scanf("%d", &n);	
		printf("Case #%d:\n", _case);

		for(int i = 1, op, x; i <= n; i++){
			scanf("%d%d" ,&op, &x);
			if(op == 0){
				int tmp = 0; add_cnt ++;
				seg[add_cnt] = (segment){x, x + add_cnt};

				for(int j = 1; j < add_cnt; j++){
					if(vis[j]) 
						continue;
					if(seg[j].left >= seg[add_cnt].left && seg[j].rig <= seg[add_cnt].rig) 
						tmp++;
				}
				printf("%d\n", tmp);
			}
			else if(op == 1){
				vis[x] = true;	
			}
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
