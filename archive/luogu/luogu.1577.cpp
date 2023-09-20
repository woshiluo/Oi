#include <cstdio>

const int N = 1e4 + 1e3;
const double eqs = 1e-4;

int n, k;

double a[N];

bool check( double mid ) {
	int tmp = 0;
	for( int i = 1; i <= n; i ++ ) {
		tmp += (int)(a[i] / mid);
	}
	return tmp >= k;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1577.in", "r", stdin );
	freopen( "luogu.1577.out", "w", stdout );
#endif
	double rig = 0;
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lf", &a[i] );
		rig += a[i];
	}
	double left = 0, res = 0;
	while( rig - left > eqs ) {
		double mid = ( left + rig ) / 2;
		if( check(mid) ) {
			res = mid;
			left = mid;
		}
		else
			rig = mid;
	}

	res = (double)((int)(res * 100.0))/100.0;
	while( check( res + 0.01 ) ) 
		res += 0.01;
	printf( "%.2lf", res );
}
