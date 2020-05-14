// Woshiluo<woshiluo@woshiluo.site>
// 2020/05/01 23:07:44 
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

int T;
int n, k;
char str[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &k );
		scanf( "%s", str );
		int cnt[30];
		memset( cnt, 0, sizeof( cnt ) );
		for( int i = 0; i < n; i ++ ) {
			cnt[ str[i] - 'a' ] ++;
		}
		int p1 = 0, len = 0, cur_less = k;
		char ans[N];
		ans[len] = 0;
		while( p1 < 26 ) {
			if( cnt[p1] == 0 ) {
				p1 ++;
				continue;
			}
			if( cnt[p1] >= cur_less ) {
				if( cur_less == k ) {
					ans[len] = p1 + 'a';
					len ++;
					cnt[p1] -= k;
					continue;
				}
				else {
					ans[len] = p1 + 'a';
					len ++;
					break;
				}
			}
			else {
				ans[len] = p1 + 'a';
				cur_less -= cnt[p1];
				cnt[p1] = 0;
			}
		}
		ans[len] = 0;
		printf( "%s\n", ans );
	}
}
