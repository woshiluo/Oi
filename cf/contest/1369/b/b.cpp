// Woshiluo<woshiluo@woshiluo.site>
// 2020/06/28 11:14:46 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

const int N = 1e5 + 1e4;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

struct node { int num, len; };

int t, n, st_cnt;
int a[N];
node st[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &t );
	while( t -- ) {
		scanf( "%d", &n );
		st_cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%1d", &a[i] );
			if( st_cnt == 0 ) {
				st_cnt ++;
				st[st_cnt] = (node){a[i], 1};
				continue;
			}
			if( a[i] == st[st_cnt].num ) 
				st[st_cnt].len ++;
			else {
				st_cnt ++;
				st[st_cnt] = (node){a[i], 1};
			}
		}
		bool has_comob = false;
		for( int i = 1; i <= st_cnt; i ++ ) {
			if( i < st_cnt && st[i].num == 1 && st[i + 1].num == 0 ) {
				has_comob = true;
				i ++;
			}
			else {
				if( has_comob ) 
					printf( "0" );
				has_comob = false;
				for( int j = 1; j <= st[i].len; j ++ ) 
					printf( "%d", st[i].num );
			}
		}
		if( has_comob ) 
			printf( "0" );
		printf( "\n" );
	}
}
