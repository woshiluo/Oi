#include <cmath>
#include <cstdio>

int a, b, c, d;
long long ans =0;

inline int Max( int a, int b ) { return a > b? a: b; }
inline int Min( int a, int b ) { return a < b? a: b; }

int main() {
	freopen( "hall.in", "r", stdin );
	freopen( "hall.out", "w", stdout );

	scanf( "%d%d%d%d", &a, &b, &c, &d );
	int tmp = std::sqrt(b);
	while( tmp * tmp < b ) 
		tmp ++;
	while( tmp * tmp > b ) 
		tmp --;
	for( int i = 1; i <= tmp; i ++ ) {
		if( c == d && ( c / 2 ) % i != 0 ) 
			continue;
		int left_c = ( c / 2 + ( c % 2 != 0 ) ) - i;
		int rig_c = ( d / 2 ) - i;
		int left_s = ( a / i ) + ( a % i != 0 );
		if( left_s / i * i > b )
			continue;
		int rig_s = ( b / i );
		ans += 1LL * Max( 0, ( Min( rig_c, rig_s ) - Max( Max( left_c, left_s ), i ) + 1 ) );
	}
	printf( "%lld\n", ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
