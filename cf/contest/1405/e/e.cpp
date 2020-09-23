// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/09 18:39:12 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 3e5 + 1e4;

struct segment { int left, rig, id; };
bool cmp( segment _a, segment _b ) { return _a.rig < _b.rig; }

int n, q;
int a[N], ans[N];
segment seg[N];

inline int lowbit( int cur ) { return cur & ( - cur ); }
struct BIT {
	int tree[N];
	BIT() {
		memset( tree, 0, sizeof(tree) );
	}
	void add( int cur, int val ) {
		for( ; cur <= n; cur += lowbit(cur) ) {
			tree[cur] += val;
		}
	}
	int ask( int cur ) {
		int res = 0;
		for( ; cur; cur -= lowbit(cur) ) {
			res += tree[cur];
		}
		return res;
	}
	int query( int left, int rig ) {
		return ask(rig) - ask( left - 1 );
	}
} bit;

int query( int cur, int rig ) {
	int left = 0, res = rig;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( bit.ask(mid) >= cur ) {
			res = mid;
			rig = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	while( res > 1 && bit.ask( res - 1 ) >= cur )
		res --;
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &q );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	for( int i = 1; i <= q; i ++ ) {
		int x, y;
		scanf( "%d%d", &x, &y );
		seg[i].left = x + 1;
		seg[i].rig = n - y;
	}
	std::sort( seg + 1, seg + q + 1, cmp );
	int p1 = 1;
	for( int i = 1; i <= n; i ++ ) {
		if( a[i] == i ) 
			bit.add( i, 1 );
		else if( a[i] < i ) 
			bit.add( query( i - a[i], i ), 1 );;

		while( p1 <= q && seg[p1].rig == i ) {
			p1 ++;
			ans[ seg[p1].id ] = bit.query( 1, seg[p1].left );
		}
	}

	for( int i = 1; i <= q; i ++ ) {
		printf( "%d\n", ans[i] );
	}
}
