// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/25 19:13:37 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
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

const int N = 510;

int read() {
	int x = 0, w = 1;
	char ch = 0;
	while (ch < '0' || ch > '9') { if (ch == '-') w = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + (ch - '0');  ch = getchar(); }
	return x * w;  
}
inline void write(int x) {
	static int sta[35];
	int top = 0;
	do { sta[top++] = x % 10, x /= 10; } while (x);
	while (top) putchar(sta[--top] + 48);
}



int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int t;
	t = read();
	while( t -- ) {
		int n, m;
		n = read(); m = read();
		std::map<int, int> mp;
		int pos[N];
		std::vector<int> col[N], row[N];
		for( int i = 1, tmp; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				tmp = read(); col[i].push_back(tmp);
			}
		}
		for( int i = 1, tmp; i <= m; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				tmp = read(); row[i].push_back(tmp);
			}
		}

		for( int i = 1; i <= n; i ++ ) {
			mp[ col[i][0] ] = i;
		}
		for( int i = 1; i <= m; i ++ ) {
			if( mp.count(row[i][0]) != 0 ) {
				for( int j = 1; j <= n; j ++ ) {
					pos[j] = mp[ row[i][ j - 1 ] ];
				}
			}
		}

		for( int i = 1; i <= n; i ++ ) {
			for( auto cur: col[ pos[i] ] ) 
				printf( "%d ", cur );
			printf( "\n" );
		}
	}
}
