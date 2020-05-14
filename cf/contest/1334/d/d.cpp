// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020-04-10 23:50
// Blog: https://blog.woshiluo.com
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

int T;
int n;
long long l, r;


int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%lld%lld", &n, &l, &r );
		long long p = 0;
		for( int i = 1; i < n; i ++ ) {
			int will_add = ( n - i ) * 2;
			long long tmp = p + will_add;
			if( ( tmp >= l && p <= l ) || ( l <= p && p <= r ) ) {
				bool flag = true;
				int st = i, nxt = i + 1;
				p ++;
				while( p <= tmp ) {
					if( l <= p && p <= r ) 
						printf( "%d ", flag? st: nxt );
					if( flag == false ) 
						nxt ++;
					flag = ( flag == false );
					p ++;
				}
			}
			p = tmp;
		}
		if( p + 1 == r ) 
			printf( "1" );
		printf( "\n" );
	}
}
