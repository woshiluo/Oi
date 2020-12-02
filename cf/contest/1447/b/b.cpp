// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/15 22:45:15 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <vector>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

bool cmp( int _a, int _b ) { return _a > _b; }

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n, m, sum = 0, cnt_zero = 0;
		std::vector<int> a, b;
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				int tmp;
				scanf( "%d", &tmp );
				if( tmp < 0 ) a.push_back(tmp);
				else if( tmp > 0 ) b.push_back(tmp);
				else cnt_zero ++;
			}
		}
		if( a.size() % 2 == 0 || cnt_zero )  {
			for( auto x: a ) sum += -x;
			for( auto x: b ) sum += x;
		}
		else {
			std::vector<int> tot;
			for( auto x: a ) tot.push_back(-x);
			for( auto x: b ) tot.push_back(x);
			std::sort( tot.begin(), tot.end(), cmp );
			tot[ tot.size() - 1 ] *= -1;
			for( auto x: tot ) sum += x;
		}
		printf( "%d\n", sum );
	}
}
