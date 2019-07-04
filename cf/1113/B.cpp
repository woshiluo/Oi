#include <cstdio>
#include <algorithm>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 5e4 + 1e3;

int n, ans, sum;
int a[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {scanf("%d", &a[i]); sum += a[i];}
	std::sort(a + 1, a + n + 1);		
	
	ans = sum;
	
	for(int j = 1; j <= 100; j++)
		if(a[1] % j == 0)
			ans = Min((a[1] / j - a[1]) + (a[2] * j - a[2]) + sum, ans);

	for(int i = 2; i <= n; i++)
		for(int j = 1; j <= 100; j++)
			if(a[i] % j == 0)
				ans = Min((a[i] / j - a[i]) + (a[1] * j - a[1]) + sum, ans);

	printf("%d\n", ans);
}
