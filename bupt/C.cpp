#include <cstdio>

const int N = 5e5 + 1e4;

int n, k;
int tmp[N << 1], ori[N];

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n + k - 1; i++){
		scanf("%1d", &tmp[i]);
		if(i > n) break;
		if(i > k)
			ori[i] = tmp[i - 1] ^ ori[i - k] ^ tmp[i];
		else 
			ori[i] = tmp[i] ^ tmp[i - 1];
	}
	for(int i = 1; i <= n; i++){
		printf("%d", ori[i]);	
	}
}
