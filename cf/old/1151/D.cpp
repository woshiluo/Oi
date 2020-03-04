#include <cstdio>
#include <algorithm>

const int N = 1e5 + 1e4;

struct node{
	int a, b;
}a[N];

int n;
long long ans;

bool cmp(node a, node b){
	return (a.a - a.b) > (b.a - b.b);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].a, &a[i].b);
	
	std::sort(a + 1, a + n + 1, cmp);
	
	for(int i = 1; i <= n; i++){
		ans += 1LL * a[i].a * (i - 1) + 1LL * a[i].b * (n - i);
	}
	printf("%lld", ans);
}
