#include <cmath>
#include <cstdio>

typedef long long ll;

const long double eqs = 1e-13;

inline long double pow( long double cur ) { return cur * cur; }
inline long double aabs( long double cur ) { return cur < 0? -cur: cur; }
inline bool is_eq( long double a, long double b ) { return ( aabs( a - b ) <= eqs ); }

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	long double x, y, r;
	long long ans = 0;
	scanf( "%Lf%Lf%Lf", &x, &y, &r );
	long double low = y - r, high = y + r;
	for( int i = low; i <= high; i ++ ) {
		if( i < low ) 
			continue;
		long double dx = 0;
		{
			long double left = 0, rig = 1e8, chk_res = pow(r) - pow( i - y ) ;
			while( left + eqs <= rig ) {
				long double mid = ( left + rig ) / 2.0;
				if( pow(mid) <= chk_res ) {
					dx = mid;
					left = mid + eqs;
				}
				else
					rig = mid - eqs;
			}
		}
		long double left = x - dx, rig = x + dx;
		int il, ir;
		if( aabs( left - std::floor(left) ) <= eqs )
			il = std::floor(left);
		else
			il = std::ceil(left);
		if( aabs( rig - std::ceil(rig)) <= eqs )
			ir = std::ceil(rig);
		else
			ir = std::floor(rig);
		if( ir < il )
			continue;
		ans += ir - il + 1;
	}
	printf( "%lld\n", ans );
}
