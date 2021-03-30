#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 1100;
const int INF = 0x3f3f3f3f;

int x, y;
char str[N];
int f[N][2];
// 0 - cur is 'c'
// 1 - cur is 'j'

inline void init() {
	memset( f, INF, sizeof(f) );
}

void readin() {
	scanf( "%d%d", &x, &y );
	scanf( "%s", str + 1 );
}

void work( int _case ) {
	int len = strlen( str + 1 );
	if( str[1] == 'C' ) 
		f[1][0] = 0;
	else if( str[1] == 'J' ) 
		f[1][1] = 0;
	else 
		f[1][0] = f[1][1] = 0;
	for( int i = 2; i <= len; i ++ ) {
		if( str[i] != 'J' )
			f[i][0] = std::min( f[ i - 1 ][0], f[ i - 1 ][1] + y );
		if( str[i] != 'C' )
			f[i][1] = std::min( f[ i - 1 ][1], f[ i - 1 ][0] + x );
	}
	printf( "Case #%d: %d\n", _case, std::min( f[len][0], f[len][1] ) );
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	for( int i = 1; i <= T; i ++ ) {
		init();
		readin();
		work(i);
	}
}
