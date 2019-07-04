#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 11000;

int n, st_size;
double ans;

struct node {
	double x, y;
	bool operator< (node b) {
		if( this -> x == b.x )
			return this -> y < b.y;
		return this -> x < b.x;
	}
} a[N], st[N];

inline double sleek(node x, node y) { 
	if( x.x == y.x ) 
		return 1000000000;
	return (x.y - y.y) / (x.x - y.x);	
}
inline double dis(node x, node y) { return std::sqrt( (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y) ); }

int main() {
#ifdef woshiluo
	freopen("luogu.2742.in", "r", stdin);
	freopen("luogu.2742.out", "w", stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lf%lf", &a[i].x, &a[i].y);
	}
	std::sort(a + 1, a + n + 1);

	st_size = 0;
	for(int i = 1; i <= n; i++) {
		st[ ++ st_size ] = a[i];
		while( st_size >= 3 && sleek( st[ st_size - 2 ], st[st_size] ) < sleek( st[ st_size - 2 ], st[ st_size - 1 ] ) ) 
			st[ st_size - 1 ] = st[ st_size ], st_size --;
	}
	for(int i = 2; i <= st_size; i++) 
		ans += dis(st[i], st[i - 1]);
	
	st_size = 0;
	for(int i = n; i >= 1; i--) {
		st[ ++ st_size ] = a[i];
		while( st_size >= 3 && sleek( st[ st_size - 2 ], st[st_size] ) < sleek( st[ st_size - 2 ], st[ st_size - 1 ] ) ) 
			st[ st_size - 1 ] = st[ st_size ], st_size --;
	}
	for(int i = 2; i <= st_size; i++) 
		ans += dis(st[i], st[i - 1]);
	printf("%.2lf", ans);
}
