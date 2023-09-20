#include <cstdio>

#include <bitset>

const short BASE = 30;

unsigned short n;
int ans;

std::bitset<100> vis[100];

short dx[4] = { +1, -1, 0, 0 };
short dy[4] = { 0, 0, +1, -1 };

inline short check( short x, short y ) {
	for( unsigned short i = 0; i < 4; i ++ ) {
		if( vis[ BASE + x + dx[i] ][ BASE + y + dy[i] ] == false ) 
			return false;
	}
	return true;
}

void dfs( short x, short y, unsigned short dep ) {
	if( dep == 0 ) {
		ans += check( x, y );
		return ;
	}
	for( unsigned short i = 0; i < 4; i ++ ) {
		short tx = x + dx[i];
		short ty = y + dy[i];

		if( vis[ BASE + tx ][ BASE + ty ] == false ) {
			vis[ BASE + tx ][ BASE + ty ] = true;
			dfs( tx, ty, dep - 1 );
			vis[ BASE + tx ][ BASE + ty ] = false;
		}
	}
}

signed main() {
#ifdef woshiluo
	freopen( "avoid.in", "r", stdin );
	freopen( "avoid.out", "w", stdout );
#endif
	scanf( "%hu", &n );
	vis[ BASE + 0][BASE + 0 ] = vis[ BASE + 1 ][BASE + 0] = true;
	n --;
	for( unsigned short i = 1; i <= n; i ++ ) {
		vis[ BASE + i ][ BASE + 0 ] = true;
		vis[ BASE + i ][ BASE + 1 ] = true;
		dfs( i, 1, n - i );
		vis[ BASE + i ][ BASE + 1 ] = false;
	}

	printf( "%d\n", ans );
}
