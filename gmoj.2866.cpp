#include <cstdio>

#include <algorithm>

inline int Aabs( int a ) { return a < 0? ( 0 - a ): a; }
inline int Min( int a, int b ) { return a < b? a: b; }
inline int Max( int a, int b ) { return a > b? a: b; }
inline int Max_3( int a, int b, int c ) { return Max( a, Max( b, c ) ); }
inline int Min_3( int a, int b, int c ) { return Min( a, Min( b, c ) ); }

const int N = 110000;
const int INF = 0x3f3f3f3f;

struct node {
	int x, y;
	bool operator< ( const node &b )const {
		if( x == b.x )
			return this -> y < b.y;
		return this -> x < b.x;
	}
} a[N], tmp[N];

bool cmp( node a, node b ) {
	if( a.y == b.y )
		return a.x < b.x;
	return a.y < b.y;
}

int n, ans = INF;
int minx, maxx, miny, maxy, mins, maxs, _mins, _maxs;

void solve( int left, int rig ) {
	if( rig - left <= 12 ) {
		for( int i = left; i <= rig; i++ ) {
			for( int j = i + 1; j <= rig; j++ ) {
				for( int k = j + 1; k <= rig; k++ ) {
					ans = Min( ans, Max_3( a[i].x, a[j].x, a[k].x ) - Min_3( a[i].x, a[j].x, a[k].x ) +
							Max_3( a[i].y, a[j].y, a[k].y ) - Min_3( a[i].y, a[j].y, a[k].y ) );
				}
			}
		}
		return ;
	}
	int mid = ( rig - left <= 100? ( left + rig ) >> 1: left + rand() % ( rig - left + 1 ) );
	std::nth_element( a + left + 1, a + mid + 1, a + rig + 1);

	if( rand() & 1 ) 
		{ solve( left, mid ); solve( mid + 1, rig ); }
	else 
		{ solve( mid + 1, rig ); solve( left, mid ); }

	int mid_x = a[mid].x, pos = 0;

	for( int i = left; i <= rig; i++ ) {
		if( Aabs( a[i].x - mid_x ) < ans ) 
			tmp[ ++ pos ] = a[i];
	}
	std::sort( tmp + 1, tmp + pos + 1, cmp );

	int p = 1;
	for( int i = 3; i <= pos; i++ ) {
		while( Aabs( tmp[p].y - tmp[i].y ) >= ans ) 
			p ++;
		for( int j = p; j < i; j++ ) {
			for( int k = j + 1 ; k < i; k++ ) {
				ans = Min( ans, Max_3( tmp[i].x, tmp[j].x, tmp[k].x ) - Min_3( tmp[i].x, tmp[j].x, tmp[k].x ) +
						Max_3( tmp[i].y, tmp[j].y, tmp[k].y ) - Min_3( tmp[i].y, tmp[j].y, tmp[k].y ) );
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "gmoj.2866.in", "r", stdin );
//	freopen( "gmoj.2866.out", "w", stdout );
#endif
	srand( 125545 );
	scanf( "%d", &n );
	minx = miny = mins = _mins = INF;
	maxx = maxy = maxs = _maxs = -INF;
	for( int i = 1; i <= n; i++ ) {
		int x, y;
		scanf( "%d%d", &x, &y );
		int tp = x; x = y; y = tp;
		minx = Min( minx, x ); maxx = Max( maxx, x );
		miny = Min( miny, y ); maxy = Max( maxy, y );
		mins = Min( mins, x + y ); maxs = Max( maxs, x + y );
		_mins = Min( _mins, x - y ); _maxs = Max( _maxs, x - y );
		a[i] = (node) { x, y };
	}
	int max = 0;
	max = Max( max, maxs - minx - miny );
	max = Max( max, maxx + maxy - mins );
	max = Max( max, _maxs - minx + maxy );
	max = Max( max, maxx - miny - _mins );

	solve( 1, n );

	printf( "%d\n%d\n", max << 1, ans << 1 );
}
