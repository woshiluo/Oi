// User: woshiluo
// Email: woshiluo@woshiluo.site
// Problem link: https://atcoder.jp/contests/arc103/tasks/arc103_d
// Comment: 
// Why the problem id is 'F', but the link is 'arc103_d'
// Interesting

#include <cstdio>
#include <cstdlib>

#include <map>
#include <algorithm>

const int N = 1e5 + 1e3;

int n;
int size[N], father[N];

struct node{
	int id;
	long long d;
} a[N];

std::map<long long, int> mp;

void wrong() {
	printf( "-1\n" );
	exit(0);
}
bool cmp( node _a, node _b ) { return _a.d < _b.d; }

int main() {
#ifdef woshiluo
	freopen( "F.in", "r", stdin );
	freopen( "F.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i].d );
		a[i].id = i;
		size[i] = 1;
		mp[ a[i].d ] = i;
	}
	std::sort( a + 1, a + n + 1, cmp );
	int rt_d, rt;
	rt = a[1].id; rt_d = a[1].d;
	for( int i = n; i > 1; i -- ) {
		int fa = mp[ a[i].d + 2LL * size[ a[i].id ] - n ];
		if( fa == 0 ) {
			wrong();
			return 0;
		} 
		size[fa] += size[ a[i].id ];
		father[ a[i].id ] = fa;
	}
	for( int i = 1; i <= n; i ++ ) {
		if( i == rt ) 
			continue;
		 rt_d -= size[i];
	}
	if( rt_d != 0 ) 
		wrong();

	for( int i = 1; i <= n; i ++ ) {
		if( i == rt ) 
			continue;
		printf( "%d %d\n", father[i], i );
	}
}
