#include <cstdio>

int n;
int tmp;
long long cnt = 0;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%1d", &tmp);
		if(tmp % 2 == 0) 
			cnt += (long long) i;
	}
	printf("%lld", cnt);
}
