#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 30;

int n, k, A, B, len;
int a[N], sum[N];

int dfs(int left, int rig){
	int now = (sum[rig] - sum[left - 1]);
	int mid = (left + rig) >> 1;
	if(now == 0) return A;
	else now = now  * (rig - left + 1) * B;
	if(left != rig) now = Min(now, dfs(left, mid) + dfs(mid + 1, rig));
	return now;
}

int main(){
	scanf("%d%d%d%d", &n, &k, &A, &B);	
	len = 1;
	for(int i = 1; i <= n; i++) len *= 2;
	for(int i = 1, tmp; i <= k; i++){
		scanf("%d", &tmp);
		a[tmp]++;
	}
	for(int i = 1; i <= len; i++) sum[i] = sum[i - 1] + a[i];
	printf("%d", dfs(1,len));
}
