#include <cstdio>
#include <algorithm>

const int N = 1100;

int n, t, ans, pos, res;
int a[N];

int main(){
	scanf("%d", &n);		
	ans = 0x7fffffff;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	for(int j = 1; j <= 100; j++){
		res = 0;
		for(int i = 1; i <= n; i++){
			if(a[i] < j) res += (j - a[i] - 1);
			else if(j < a[i] ) res += (a[i] - j - 1);
		}
		if(res < ans) ans = res, pos = j;
	}
	printf("%d %d", pos, ans);
}
