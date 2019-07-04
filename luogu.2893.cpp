#include <cstdio>
#include <algorithm>

const int N = 2100;

struct road{
	int id, now;
}a[N];

bool cmp(road a, road b){
	return a.now < b.now;
}

int n;
int f[N][N], id[N];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i].now);
		a[i].id = i;
	}
	std::sort( a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++) id[ a[i].id ] = i;

}
