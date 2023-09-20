#include <cmath>
#include <cstdio>

long long a, b, c, d;

inline long long Min( long long a, long long b ) { return a < b? a: b; }
inline long long pow( long long a ) { return 1LL * a * a; }

int main() {
	freopen( "pobeda.in", "r", stdin );
	freopen( "pobeda.out", "w", stdout );

	scanf( "%lld%lld%lld%lld", &a, &b, &c, &d );
	long long cnt = Min( a, b ) + Min( c, d );
	long long tmp = std::sqrt(cnt);
	while( pow(tmp) > cnt )
		tmp --;
	while( pow( tmp + 1 ) <= cnt )
		tmp ++;
	
	printf( "%lld\n", tmp );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
