#include <bits/stdc++.h>

#ifndef LOCAL
#define debug( ... ) 42
#endif
#define rep( i, x, y ) for ( int i = x; i < y; i++ )
#define rp( i, n ) rep( i, 0, n )
#define pb emplace_back
using namespace std;
template <typename T, typename T2>
void cmin( T &x, const T2 &y ) {
	x = x < y ? x : y;
}
template <typename T, typename T2>
void cmax( T &x, const T2 &y ) {
	x = x > y ? x : y;
}
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
template <class T>
using vc = vector<T>;
template <class T>
using pq = priority_queue<T>;
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
mt19937 rng( time( NULL ) );
const int inf = 1000000000;
const ll lnf = 1000000000000000000;
#define sz( x ) int( ( x ).size() )
#define all( x ) begin( x ), end( x )

const int P = 1e9 + 7;
long long power( long long x, long long y ) {
	long long res = 1;
	while ( y ) {
		if ( y % 2 == 1 ) {
			res = res * x % P;
		}
		x = x * x % P;
		y = y / 2;
	}
	return res;
}
long long inverse( long long x ) {
	return power( x % P, P - 2 );
}

vc<vc<ll>> inverse( vc<vc<ll>> &a ) {
	int n = sz( a );
	vc<vc<ll>> b( n );
	rp( i, n ) b[ i ].resize( n ), b[ i ][ i ] = 1;
	rp( i, n ) {
		int r = -1;
		rep( j, i, n ) if ( a[ j ][ i ] ) r = j;
		if ( r == -1 )
			return {};
		swap( a[ r ], a[ i ] ), swap( b[ r ], b[ i ] );
		ll inv = inverse( a[ i ][ i ] );
		rp( j, n ) {
			if ( j == i )
				continue;
			ll p = a[ j ][ i ] * inv % P;
			rp( k, n ) {
				a[ j ][ k ] -= p * a[ i ][ k ] % P;
				if ( a[ j ][ k ] < 0 )
					a[ j ][ k ] += P;
				b[ j ][ k ] -= p * b[ i ][ k ] % P;
				if ( b[ j ][ k ] < 0 )
					b[ j ][ k ] += P;
			}
		}
		rp( j, n ) a[ i ][ j ] = a[ i ][ j ] * inv % P, b[ i ][ j ] = b[ i ][ j ] * inv % P;
	}
	return b;
}

int main() {
	ios::sync_with_stdio( false );
	cin.tie( nullptr );
	int n;
	cin >> n;
	vc<vc<ll>> a( n, vc<ll>( n ) );
	rp( i, n ) rp( j, n ) cin >> a[ i ][ j ];
	auto b = inverse( a );
	if ( sz( b ) == 0 ) {
		cout << "No Solution\n";
		return 0;
	}
	for ( auto v : b ) {
		for ( auto x : v )
			cout << x << " ";
		cout << "\n";
	}
	return 0;
}
