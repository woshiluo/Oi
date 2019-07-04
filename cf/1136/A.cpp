#include <cstdio>

const int N =110;

int n, k;
int left[N], rig[N];

int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d", &left[i], &rig[i]);
	}
	scanf("%d", &k);
	for(int i = 1; i <= n; i++){
		if(left[i] <= k && k <= rig[i]){
			printf("%d", n - i + 1);
			return 0;
		}
	}
}
