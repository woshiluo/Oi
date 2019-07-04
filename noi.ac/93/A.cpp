#include <cstdio>

const int N = 5100;

int n, res, ans;
int xor_sum[N], a[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		xor_sum[i] = xor_sum[i - 1] ^ a[i];
	}
	for(int i = 1; i <= n; i++){
		ans = xor_sum[i];	
		for(int j = 1; j <= i; j++){
			res = xor_sum[j] + (xor_sum[i] ^ xor_sum[j]);
			ans = res > ans? res: ans;
		}
		printf("%d ", ans);
	}
}
