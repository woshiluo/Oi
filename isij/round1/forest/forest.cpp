#include <cstdio>

#include <iostream>

__int128 a, k, b, m, x;

__int128 readin() {
	__int128 res = 0; char x = getchar();
	while( x < '0' || x > '9' )
		x = getchar();
	while( x >= '0' && x <= '9' ) {
		res = ( res * 10 ) + ( x - '0' );
		x = getchar();
	}
	return res;
}

__int128 check( __int128 val ) {
	__int128 res = ( a + b ) * val;
	res -= ( val / k ) * a;
	res -= ( val / m ) * b;
	return res;
}

int main() {
	freopen( "forest.in", "r", stdin );
	freopen( "forest.out", "w", stdout );

	//scanf( "%lld%lld%lld%lld%lld", &a, &k, &b, &m, &x );
	//std::cin >> a >> k >> b >> m >> x;
	a = readin(); k = readin(); b = readin(); m = readin(); x = readin();
	__int128 left = 1, rig = (__int128)(1e18);
	__int128 res = 0;
	while( left <= rig ) {
		__int128 mid = ( left + rig ) >> 1;
		__int128 tmp = check(mid);
		if( tmp < x ) 
			left = mid + 1;
		else {
			res = rig;
			rig = mid - 1;
		}
	}
	while( check(res) < x ) 
		res ++;
	while( check( res - 1 ) >= x && res > 1 ) 
		res --;
	//printf( "%lld\n", res );
	std::cout << (long long)res;

	fclose( stdin );
	fclose( stdout );
	return 0;
}
