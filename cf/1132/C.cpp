#include <cstdio>
#include <cstring>
 
const int N = 5100;

struct sec{
	int left, rig;	
}section[N];

int n, q, ans = 0x7fffffff, cnt, tmp_left, tmp_rig;
int col[N], sum[N], single[N];
bool vis[N];

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= q; i++){
		scanf("%d%d", &section[i].left, &section[i].rig);
		for(int j = section[i].left; j <= section[i].rig; j++){
			cnt += (col[j] == 0);
			col[j]++;			
		}
	}
	for(int i = 1; i <= q; i++){
		for(int j = section[i].left; j <= section[i].rig; j++){
			if(col[j] == 1) single[i]++;
		}
	}
	for(int i = 1; i <= n; i++){
		sum[i] = sum[i - 1];
		if(col[i] == 2) sum[i]++;
	}
	for(int i = 1; i <= q; i++){
		for(int j = 1; j <= q; j++){
			if(i == j) continue;
			tmp_left = section[i].left > section[j].left? section[i].left: section[j].left;
			tmp_rig = section[i].rig < section[j].rig? section[i].rig: section[j].rig;
			int tmp;
			if(tmp_left <= tmp_rig) tmp = sum[tmp_rig] - sum[tmp_left - 1] + single[i] + single[j];
			else tmp = single[i] + single[j];
			ans = tmp < ans? tmp : ans;
		}
	}
	printf("%d", cnt - ans); 
}
