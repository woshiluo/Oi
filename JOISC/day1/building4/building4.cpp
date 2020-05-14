#include <cstdio>

inline int Max( int a, int b ) { return a > b? a: b; }
inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 1e6 + 1e5;
const int INF = 0x3f3f3f3f;

struct node{ 
	int left, rig; 
	node( int _left = -INF, int _rig = INF ) { left = _left, rig = _rig; }
};
int n;
int a[N], b[N];
node f[N][2];
bool vis[N][2];

inline void chk( node &tmp, node _a ){
	tmp.left = Max( tmp.left, _a.left );
	tmp.rig = Min( tmp.rig, _a.rig );
}

// a +1, b -1
inline void write( int cur, int id, int sum ) {
	if( cur == 1 ) {
		printf( "%c", ( id == 0 )? 'A': 'B' );
		return ;
	}

	sum += ( id == 0 )? -1: 1;
	int val = ( id == 0 )? a[cur]: b[cur];
	if( vis[cur - 1 ][0] && val >= a[ cur - 1 ] && f[ cur - 1 ][0].rig <= sum && sum <= f[ cur - 1 ][0].left )
		write( cur - 1, 0, sum );
	else if( vis[ cur - 1 ][1] && val >= b[ cur - 1 ] && f[ cur - 1 ][1].rig <= sum && sum <= f[ cur - 1 ][1].left )
		write( cur - 1, 1, sum );
	printf( "%c", ( id == 0 )? 'A': 'B' );
}

int main() {
#ifdef woshiluo
	freopen( "building4.in", "r", stdin );
	freopen( "building4.out", "w", stdout );
#endif
	scanf( "%d", &n );
	n <<= 1;

	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &b[i] );
	}

	f[0][0] = f[0][1] = (node){ 0, 0 };
	vis[0][0] = vis[0][1] = 1;
	for( int i = 1; i <= n; i ++ ) {
		node tmp;
		if( a[i] >= a[ i - 1 ] && vis[ i - 1 ][0] ) {
			chk( tmp, f[ i - 1 ][0] );
			vis[i][0] = true;
		}
		if( a[i] >= b[ i - 1 ] && vis[ i - 1 ][1] ) {
			chk( tmp, f[ i - 1 ][1] );
			vis[i][0] = true;
		}
		tmp.left ++, tmp.rig ++;
		f[i][0] = tmp;

		tmp = node();
		if( b[i] >= a[ i - 1 ] && vis[ i - 1 ][0] ) {
			chk( tmp, f[ i - 1 ][0] );
			vis[i][1] = true;
		}
		if( b[i] >= b[ i - 1 ] && vis[ i - 1 ][1] ) {
			chk( tmp, f[ i - 1 ][1] );
			vis[i][1] = true;
		}
		tmp.left --, tmp.rig --;
		f[i][1] = tmp;
	}

	if( vis[n][0] && f[n][0].rig <= 0 && 0 <= f[n][0].left )
		write( n, 0, 0 );
	else if( vis[n][1] && f[n][1].rig <= 0 && 0 <= f[n][1].left )
		write( n, 1, 0 );
	else 
		printf( "-1\n" );
}
