// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/06 23:12:01 
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

const int N = 3e5 + 1e4;

struct node { int one, zero; } need[N];

int T;
int n, k;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &k );
		char str[310000];
		scanf( "%s", str );
		bool flag = true;
		for( int i = 0; i < n; i ++ ) {
			int la = i - k;
			if( la >= 0 ) {
				if( str[i] == '?' ) 
					str[i] = str[la];
				else if( str[la] == '?' ) 
					str[la] = str[i];
				else if( str[i] != str[la] ) {
					flag = false;
					break;
				}
			}
		}
		int one = 0, zero = 0;
		for( int i = 0; i < n; i ++ ) {
			if( str[i] == '1' ) 
				one ++;
			else if( str[i] == '0' ) 
				zero ++;

			int la = i - k;
			if( la >= 0 ) {
				if( str[la] == '1' ) 
					one --;
				else if( str[la] == '0' ) 
					zero --;
			}

			if( i >= k - 1 ) {
				if( one > ( k / 2 ) || zero > ( k / 2 ) ) {
					flag = false;
					break;
				}
			}
		}
		if( flag ) {
			printf( "YES\n" );
		}
		else {
			printf( "NO\n" );
		}
	} 
}
