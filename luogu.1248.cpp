#include <cstdio>
#include <algorithm>

inline int Max(int a, int b){return a > b? a: b;}

const int N = 1100;

int n;
struct node{
	int x, y, d, id;
}a[N];

bool cmp(node x, node y){
	if(x.d == y.d){
		if(x.d <= 0) 
			return x.x < y.x;
		else 
			return x.y > y.y;
	}
	else return x.d < y.d;
}

int main(){
#ifdef woshiluo
	freopen("luogu.1248.in", "r", stdin);
	freopen("luogu.1248.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){ scanf("%d", &a[i].x); }
	for(int i = 1; i <= n; i++){ 
		scanf("%d", &a[i].y); 
		a[i].id = i;
		a[i].d = (a[i].x == a[i].y ? 0: (a[i].x > a[i].y ? 1: - 1));
	}

	std::sort(a + 1, a + n + 1, cmp);

	int time_a = a[1].x, time_b = a[1].x + a[1].y;
	for(int i = 2; i <= n; i++){
		time_a += a[i].x;
		time_b = Max(time_a, time_b) + a[i].y;
	}
	printf("%d\n", time_b);
	for(int i = 1; i <= n; i++){ printf("%d ", a[i].id); }
}
