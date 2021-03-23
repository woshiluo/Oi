// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/29 16:21:50 
// Blog: https://blog.woshiluo.com

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

double pow( double cur ) { return cur * cur; }

const int N = 5100;

struct node {
	int x, y;
	double operator +( const node b ) const {
		return std::sqrt( pow( y - b.y ) + pow( x - b.x ) );
	}
} a[N];
bool vis[N];

int main() {
	int n;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &a[i].x, &a[i].y );
	}

	std::vector<int> ans;
	ans.push_back(1); vis[1] = true;
	for( int i = 1; i < n; i ++ ) {
		node cur = a[ ans.back() ];
		int max_id = ans.back();
		for( int j = 1; j <= n; j ++ ) {
			if( vis[j] ) 
				continue;
			if( cur + a[max_id] < cur + a[j] )
				max_id = j;
		}
		vis[max_id] = true;
		ans.push_back(max_id);
	}

	for( auto x: ans ) 
		printf( "%d ", x );
}
