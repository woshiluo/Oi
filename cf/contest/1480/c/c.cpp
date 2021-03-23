// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/07 23:51:27 
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

const int N = 1e5 + 1e4;

int n;

struct ask {
	int val[N];
	bool vis[N];
	int query( int pos ) {
		int tmp; 

		printf( "? %d\n", pos ); fflush(stdout);
		scanf( "%d", &tmp );
		return tmp;
	}
	int get( int cur ) {
		if( cur == 0 || cur == n + 1 ) 
			return n + 1;
		if( vis[cur] ) 
			return val[cur];
		vis[cur] = true;
		val[cur] = query(cur);
		return val[cur];
	}
	int operator[] ( int cur ) {
		return get(cur);
	}
	bool re_chk( int cur ) {
		return get(cur) < get( cur + 1 ) && get(cur) < get( cur - 1 );
	}
} a;

void get_ans( int left, int rig ) {
	int cur = left, len = rig - left + 1;
	len = ( len / 2 ) + 1;
	if( left == rig ) {
		if( a.re_chk(cur) ) {
			printf( "! %d\n", cur );
			fflush(stdout);
			exit(0);
		}
		return ;
	}
	int could_rig = n;
	int max_val = Min( a[cur] + len - 1, n );
	if( a[cur] + 1 == a[ cur + 1 ] && a[ cur + max_val - a[cur] ] == max_val ) {
		get_ans( left, left ); get_ans( rig, rig );
	}
	else {
		chk_Min( could_rig, cur + max_val - a[cur] );
	}

	int min_val = Max( a[cur] - len + 1, 1 );
	if( a[cur] - 1 == a[ cur + 1 ] && a[ cur + a[cur] - min_val ] == min_val ) {
		get_ans( left, left ); get_ans( rig, rig );
	}
	else {
		chk_Min( could_rig, cur + a[cur] - min_val );
	}

	get_ans( left, left );
	get_ans( rig, rig );
	get_ans( left + 1, could_rig );
}

int main() {
	scanf( "%d", &n );
	get_ans( 1, n );
}
