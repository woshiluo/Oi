// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/24 23:39:50 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
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
int n;
char a[N], b[N];
bool pool[512];

int main() {
#ifdef woshiluo 
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		scanf( "%s", a + 1 );
		scanf( "%s", b + 1 );
		bool flag = false;
		std::vector<int> out[512];
		for( int i = 1; i <= n; i ++ ) {
			if( a[i] < b[i] ) {
				out[a[i]].push_back(b[i]);
			}
			else if( a[i] > b[i] ) {
				flag = true;
				break;
			}
		}
		if( flag ) {
			printf( "-1\n" );
			continue;
		}

		int cnt = 0;
		for( int i = 'a'; i <= 'z'; i ++ ) {
			int size = out[i].size();
			if( size != 0 ) {
				std::sort( out[i].begin(), out[i].end() );
				int nxt = out[i][0];
				cnt ++;
				for( int j = 0; j < size; j ++ ) {
					if( out[i][j] == nxt ) 
						continue;
					out[nxt].push_back(out[i][j]);
				}
			}
		}
		printf( "%d\n", cnt );
	}
}
