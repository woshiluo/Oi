// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/22 14:19:08 
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

const int N = 4100;

int T;
int n;
int f[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		std::vector<int> val;
		int cnt = 0, max = 0;
		for( int i = 1; i <= ( n << 1 ); i ++ ) { 
			int tmp;
			scanf( "%d", &tmp );
			if( tmp > max ) {
				max = tmp;
				if( cnt != 0 )
					val.push_back( cnt );
				cnt = 1;
			}
			else 
				cnt ++;
		}
		if( cnt != 0 ) 
			val.push_back(cnt);

		std::sort( val.begin(), val.end() );
		
		int size = val.size();
		memset( f, 0, sizeof(int) * ( n + 3 ) );
		f[0] = true;
		int cur = 1, la = 0;
		int len = 0;
		for( int i = 0; i < size; i ++ ) {
			len += val[i];
			if( len > n ) 
				len = n;
			for( int j = len; j - val[i] >= 0; j -- ) {
				f[j] |= f[ j - val[i] ];
			}
		}
		printf( "%s\n", f[n]? "YES": "NO" );
	}
}
