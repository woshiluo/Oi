#include <cstdio>

#include <vector>

const int N = 2e5 + 1e4;

struct node {
	int id;
	int country, score;
};

bool vis[N];
node a[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int n;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		a[i].id = i;
		scanf( "%d%d", &a[i].country, &a[i].score );
	}

	int p1 = 1, ans = 0;
	std::vector<node> coun[N];
	for( int j = 1; j <= n; j ++ ) {
		node cur;
		cur.id = 0;
		scanf( "%d%d", &cur.country, &cur.score );
		while( p1 <= n && a[p1].score <= cur.score ) {
			coun[0].push_back( a[p1] );
			coun[ a[p1].country ].push_back( a[p1] );
			p1 ++;
		}
		while( coun[ cur.country ].size() > 0 && vis[ coun[ cur.country ].back().id ] ) {
			coun[ cur.country ].pop_back();
		}
		if( coun[ cur.country ].size() != 0 ) {
			vis[ coun[ cur.country ].back().id ] = true;
			coun[ cur.country ].pop_back();
		}
		else {
			ans ++;
			// while( vis[ coun[0].back().id ] ) 
			// 	coun[0].pop_back();
			// vis[ coun[0].back().id ] = true;
			// coun[0].pop_back();
		}
	}
	printf( "%d\n", ans );
}
