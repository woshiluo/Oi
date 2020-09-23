// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/08 23:11:22 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1e4 + 1e3;

int n, a[N];
bool vis[N];
bool vis2[N];

int get( int a, int b ) {
	int res = 0;
	printf( "? %d %d\n", a, b );
	fflush( stdout );
	scanf( "%d", &res );
	return res;
}

int main() {
	scanf( "%d", &n );
	if( n == 1 ) {
		printf( "! 1\n" );
		return 0;
	}
	int p1 = 1, p2 = 2, cnt = n;
	while( cnt > 1 ) { 
		cnt --;
		while( vis[p1] ) 
			p1 ++;
		while( vis[p2] ) 
			p2 ++;
		while( p1 == p2 ) {
			p1 ++;
			while( vis[p1] ) 
				p1 ++;
			while( vis[p2] ) 
				p2 ++;
		}
		int test1 = get( p1, p2 );
		int test2 = get( p2, p1 );
		if( test1 > test2 ) {
			vis[p1] = true;
			vis2[test1] = true;
			a[p1] = test1;
			p1 ++;
		}
		else {
			vis[p2] = true;
			vis2[test2] = true;
			a[p2] = test2;
			p2 ++;
		}
	}
	int left = 0, rig = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( vis[i] == false )
			left =i;
		if( vis2[i] == false )
			rig = i;
	}
	a[left] = rig;
	printf( "! " );
	for( int i = 1; i <= n; i ++ ) {
		printf( "%d ", a[i] );
	}
	fflush(stdout);
}
